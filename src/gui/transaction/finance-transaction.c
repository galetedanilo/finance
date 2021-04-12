/* finance-transaction.c
 *
 * Copyright 2020 galetedanilo <galetedanilo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "finance-config.h"
#include "finance-enums.h"

#include "finance-transaction.h"

struct _FinanceTransaction
{
  GtkGrid   parent_instance;

  /* The widgets */
  GtkWidget *buffer_notes;
  GtkWidget *combo_category;
  GtkWidget *combo_frequency;
  GtkWidget *combo_payment;
  GtkWidget *combo_repeat;
  GtkWidget *entry_amount;
  GtkWidget *entry_date;
  GtkWidget *entry_frequency_date;
  GtkWidget *entry_name;
  GtkWidget *entry_payee_name;
  GtkWidget *entry_payment_info;
  GtkWidget *image_icon;
  GtkWidget *label_category;
  GtkWidget *label_notes;
  GtkWidget *label_payment;
  GtkWidget *label_repeat;
  GtkWidget *spin_frequency_number;

  GdkRGBA   *color;
  gchar     *icon;
  gchar     *notes;
  gboolean  mobile;

  GSettings *settings;
};

G_DEFINE_TYPE (FinanceTransaction, finance_transaction, GTK_TYPE_GRID)

enum {
  PROP_0,
  PROP_ICON,
  PROP_COLOR,
  PROP_NAME,
  PROP_AMOUNT,
  PROP_DATE,
  PROP_PAYEE_NAME,
  PROP_PAYMENT,
  PROP_PAYMENT_INFO,
  //PROP_CATEGORY,
  PROP_REPEAT,
  PROP_FREQUENCY,
  PROP_FREQUENCY_NUMBER,
  PROP_FREQUENCY_DATE,
  PROP_NOTES,
  PROP_MOBILE,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static void
create_icon (FinanceTransaction *self)
{
  cairo_surface_t *surface;

  surface = finance_utils_create_circle (self->color, 140, self->icon);

  gtk_image_set_from_surface (GTK_IMAGE (self->image_icon), surface);

  g_clear_pointer (&surface, cairo_surface_destroy);
}

static void
on_combo_frequency_changed (GtkComboBox *widget,
                            gpointer     user_data)
{
  FinanceTransaction *self = FINANCE_TRANSACTION (user_data);

  FinanceFrequency data = gtk_combo_box_get_active (GTK_COMBO_BOX (widget));

  gtk_spin_button_set_value (GTK_SPIN_BUTTON (self->spin_frequency_number), 2);

  gtk_entry_set_text (GTK_ENTRY (self->entry_frequency_date), "");

  switch (data)
    {
    case FINANCE_FOREVER:
      gtk_widget_set_visible (self->spin_frequency_number, FALSE);
      gtk_widget_set_visible (self->entry_frequency_date, FALSE);
      break;

    case FINANCE_N_OCCURRENCES:
      gtk_widget_set_visible (self->spin_frequency_number, TRUE);
      gtk_widget_set_visible (self->entry_frequency_date, FALSE);
      break;

    case FINANCE_UNTIL_DATE:
      gtk_widget_set_visible (self->spin_frequency_number, FALSE);
      gtk_widget_set_visible (self->entry_frequency_date, TRUE);
      break;

    }
}

static void
on_combo_repeat_changed (GtkComboBox *widget,
                         gpointer     user_data)
{
  FinanceTransaction *self = FINANCE_TRANSACTION (user_data);

  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_frequency), 0);

  gtk_widget_set_visible (self->combo_frequency,
                          gtk_combo_box_get_active (widget));

}

static void
finance_transaction_responsive_layout (FinanceTransaction *self)
{
  gtk_widget_set_visible (self->image_icon, !self->mobile);
  gtk_widget_set_visible (self->label_category, !self->mobile);
  gtk_widget_set_visible (self->label_notes, !self->mobile);
  gtk_widget_set_visible (self->label_payment, !self->mobile);
  gtk_widget_set_visible (self->label_repeat, !self->mobile);

  if (self->mobile)
    {
      gtk_widget_set_size_request (self->combo_category, -1, 40);
      gtk_widget_set_size_request (self->combo_frequency, -1, 40);
      gtk_widget_set_size_request (self->combo_payment, -1, 40);
      gtk_widget_set_size_request (self->combo_repeat, -1, 40);
      gtk_widget_set_size_request (self->entry_amount, -1, 40);
      gtk_widget_set_size_request (self->entry_date, -1, 40);
      gtk_widget_set_size_request (self->entry_frequency_date, -1, 40);
      gtk_widget_set_size_request (self->entry_name, 300, 40);
      gtk_widget_set_size_request (self->entry_payee_name, -1, 40);
      gtk_widget_set_size_request (self->entry_payment_info, -1, 40);
      gtk_widget_set_size_request (self->entry_date, -1, 40);
      gtk_widget_set_size_request (self->spin_frequency_number, -1, 40);

      return;
    }

    gtk_widget_set_size_request (self->combo_category, -1, 50);
    gtk_widget_set_size_request (self->combo_frequency, -1, 50);
    gtk_widget_set_size_request (self->combo_payment, -1, 50);
    gtk_widget_set_size_request (self->combo_repeat, -1, 50);
    gtk_widget_set_size_request (self->entry_amount, -1, 50);
    gtk_widget_set_size_request (self->entry_date, -1, 50);
    gtk_widget_set_size_request (self->entry_frequency_date, -1, 50);
    gtk_widget_set_size_request (self->entry_name, 400, 50);
    gtk_widget_set_size_request (self->entry_payee_name, -1, 50);
    gtk_widget_set_size_request (self->entry_payment_info, -1, 50);
    gtk_widget_set_size_request (self->entry_date, -1, 50);
    gtk_widget_set_size_request (self->spin_frequency_number, -1, 50);
}

GtkWidget *
finance_transaction_new (void)
{
  return g_object_new (FINANCE_TYPE_TRANSACTION, NULL);
}

static void
finance_transaction_finalize (GObject *object)
{
  FinanceTransaction *self = (FinanceTransaction *)object;

  g_clear_pointer (&self->icon, g_free);
  g_clear_pointer (&self->notes, g_free);

  G_OBJECT_CLASS (finance_transaction_parent_class)->finalize (object);
}

static void
finance_transaction_dispose (GObject *object)
{
  FinanceTransaction *self = (FinanceTransaction *)object;

  g_clear_pointer (&self->color, gdk_rgba_free);
  g_clear_object (&self->settings);

  G_OBJECT_CLASS (finance_transaction_parent_class)->dispose (object);
}

static void
finance_transaction_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  FinanceTransaction *self = FINANCE_TRANSACTION (object);

  switch (prop_id)
    {
    case PROP_ICON:
      g_value_set_string (value, finance_transaction_get_icon (self));
      break;

    case PROP_COLOR:
      g_value_set_boxed (value, finance_transaction_get_color (self));
      break;

    case PROP_NAME:
      g_value_set_string (value, finance_transaction_get_name (self));
      break;

    case PROP_AMOUNT:
      g_value_set_double (value, finance_transaction_get_amount (self));
      break;

    case PROP_DATE:
      g_value_set_boxed (value, finance_transaction_get_date (self));
      break;

    case PROP_PAYEE_NAME:
      g_value_set_string (value, finance_transaction_get_payee_name (self));
      break;
      
    case PROP_PAYMENT:
      g_value_set_enum (value, finance_transaction_get_payment (self));
      break;

    case PROP_PAYMENT_INFO:
      g_value_set_string (value, finance_transaction_get_payment_info (self));
      break;
      
    case PROP_REPEAT:
      g_value_set_enum (value, finance_transaction_get_repeat (self));
      break;

    case PROP_FREQUENCY:
      g_value_set_enum (value, finance_transaction_get_frequency (self));
      break;

    case PROP_FREQUENCY_NUMBER:
      g_value_set_int (value, finance_transaction_get_frequency_number (self));
      break;

    case PROP_FREQUENCY_DATE:
      g_value_set_boxed (value,finance_transaction_get_frequency_date (self));
      break;

    case PROP_NOTES:
      g_value_set_string (value, finance_transaction_get_notes (self));
      break;

    case PROP_MOBILE:
      g_value_set_boolean (value, finance_transaction_get_mobile (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_transaction_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec)
{
  FinanceTransaction *self = FINANCE_TRANSACTION (object);

  switch (prop_id)
    {
    case PROP_ICON:
      finance_transaction_set_icon (self, g_value_get_string (value));
      break;

    case PROP_COLOR:
      finance_transaction_set_color (self, g_value_get_boxed (value));
      break;

    case PROP_NAME:
      finance_transaction_set_name (self, g_value_get_string (value));
      break;

    case PROP_AMOUNT:
      finance_transaction_set_amount (self, g_value_get_double (value));
      break;

    case PROP_DATE:
      finance_transaction_set_date (self, g_value_get_boxed (value));
      break;

    case PROP_PAYEE_NAME:
      finance_transaction_set_payee_name (self, g_value_get_string (value));
      break;
      
    case PROP_PAYMENT:
      finance_transaction_set_payment (self, g_value_get_enum (value));
      break;

    case PROP_PAYMENT_INFO:
      finance_transaction_set_payment_info (self, g_value_get_string (value));
      break;
      
    case PROP_REPEAT:
      finance_transaction_set_repeat (self, g_value_get_enum (value));
      break;

    case PROP_FREQUENCY:
      finance_transaction_set_frequency (self, g_value_get_enum (value));
      break;

    case PROP_FREQUENCY_NUMBER:
      finance_transaction_set_frequency_number (self, g_value_get_int (value));
      break;

    case PROP_FREQUENCY_DATE:
      finance_transaction_set_frequency_date (self, g_value_get_boxed (value));
      break;

    case PROP_NOTES:
      finance_transaction_set_notes (self, g_value_get_string (value));
      break;

    case PROP_MOBILE:
      finance_transaction_set_mobile (self, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_transaction_class_init (FinanceTransactionClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  g_type_ensure (FINANCE_TYPE_ENTRY_MONETARY);
  g_type_ensure (FINANCE_TYPE_ENTRY_DATE);

  object_class->finalize     = finance_transaction_finalize;
  object_class->dispose      = finance_transaction_dispose;
  object_class->get_property = finance_transaction_get_property;
  object_class->set_property = finance_transaction_set_property;

  /**
   * FinanceTransaction::icon:
   *
   * The two letters that are part of the icon image
   */
  properties[PROP_ICON] = g_param_spec_string ("icon",
                                               "Icon",
                                               "The two letters that are part of the icon image",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::color:
   *
   * The background color of the icon
   */
  properties[PROP_COLOR] = g_param_spec_boxed ("color",
                                               "Color",
                                               "The background color of the icon",
                                               GDK_TYPE_RGBA,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::name:
   *
   * The transaction name
   */
  properties[PROP_NAME] = g_param_spec_string ("name",
                                               "Name",
                                               "The transaction name",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::amount:
   *
   * The transaction amount
   */
  properties[PROP_AMOUNT] =  g_param_spec_double ("amount",
                                                  "Amount",
                                                  "The transaction amount",
                                                  -G_MINDOUBLE,
                                                  G_MAXDOUBLE,
                                                  0.0,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::date:
   *
   * The transaction date
   */
  properties[PROP_DATE] = g_param_spec_boxed ("date",
                                              "Date",
                                              "The transaction date",
                                              G_TYPE_DATE_TIME,
                                              G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::payee_name:
   *
   * The transaction payee name
   */
  properties[PROP_PAYEE_NAME] = g_param_spec_string ("payee-name",
                                                     "Payee name",
                                                     "The transaction payee name",
                                                     NULL,
                                                     G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::payment:
   *
   * The payment method of the transaction
   */
  properties[PROP_PAYMENT] = g_param_spec_enum ("payment",
                                                "Payment",
                                                "The payment method of the transaction",
                                                FINANCE_TYPE_PAYMENT,
                                                FINANCE_CASH,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::payment_info:
   *
   * The transaction payment information
   */
  properties[PROP_PAYMENT_INFO] = g_param_spec_string ("payment-info",
                                                       "Payment information",
                                                       "The transaction payment information",
                                                       NULL,
                                                       G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::repeat:
   *
   * The transaction repeat type
   */
  properties[PROP_REPEAT] = g_param_spec_enum ("repeat",
                                               "Repeat",
                                               "The transaction repeat type",
                                               FINANCE_TYPE_REPEAT,
                                               FINANCE_NO_REPEAT,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::frequency:
   *
   * The transaction frequency
   */
  properties[PROP_FREQUENCY] = g_param_spec_enum ("frequency",
                                                  "Frequency",
                                                  "The transaction frequency",
                                                  FINANCE_TYPE_FREQUENCY,
                                                  FINANCE_FOREVER,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::frequency_number:
   *
   * The number of frequency of transactions
   */
  properties[PROP_FREQUENCY_NUMBER] = g_param_spec_int ("frequency-number",
                                                        "Frequency Number",
                                                        "The number of frequency of transactions",
                                                        2, 365, 2,
                                                        G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::frequency_date:
   *
   * The date of the financial transaction frequency
   */
  properties[PROP_FREQUENCY_DATE] = g_param_spec_boxed ("frequency-date",
                                                        "Fequency date",
                                                        "The date of the financial transaction frequency",
                                                        G_TYPE_DATE_TIME,
                                                        G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::notes:
   *
   * The transaction notes information
   */
  properties[PROP_NOTES] = g_param_spec_string ("notes",
                                                "Notes",
                                                "The transaction notes information",
                                                NULL,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransaction::mobile:
   *
   * The transaction mobile
   */
  properties[PROP_MOBILE] = g_param_spec_boolean ("mobile",
                                                  "Mobile",
                                                  "The transaction mobile",
                                                  FALSE,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/transaction/finance-transaction.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, buffer_notes);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, combo_category);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, combo_frequency);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, combo_payment);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, combo_repeat);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, entry_amount);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, entry_date);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, entry_frequency_date);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, entry_name);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, entry_payee_name);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, entry_payment_info);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, image_icon);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, label_category);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, label_notes);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, label_payment);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, label_repeat);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, spin_frequency_number);

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_combo_repeat_changed);
  gtk_widget_class_bind_template_callback (widget_class, on_combo_frequency_changed);

}

static void
finance_transaction_init (FinanceTransaction *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->icon = g_strdup ("NW");

  self->color = finance_utils_random_rgba_color ();

  create_icon (self);

  self->settings = g_settings_new ("org.gnome.finance");

  g_settings_bind (self->settings, "date",
                   self->entry_date, "formatting",
                   G_SETTINGS_BIND_GET);

  g_settings_bind (self->settings, "date",
                   self->entry_frequency_date, "formatting",
                   G_SETTINGS_BIND_GET);

  g_settings_bind (self->settings, "amount",
                   self->entry_amount, "formatting",
                   G_SETTINGS_BIND_GET);

  g_settings_bind (self->settings, "decimal-places",
                   self->entry_amount, "decimal-places",
                   G_SETTINGS_BIND_GET);

  g_settings_bind (self->settings, "currency-symbol",
                   self->entry_amount, "currency-symbol",
                   G_SETTINGS_BIND_GET);

  g_settings_bind (self->settings, "symbol-type",
                   self->entry_amount, "symbol",
                   G_SETTINGS_BIND_GET);
}

/**
 * finance_transaction_get_icon:
 * @self: a #FinanceTransaction object.
 *
 * Returns the two letters that are part of the icon image.
 *
 * Returns: A two-letter string , or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_get_icon (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), NULL);

  return self->icon;
}

/**
 * finance_transaction_set_icon:
 * @self: a #FinanceTransaction instance.
 * @icon: the icon to set, as a two-letter string.
 *
 * Sets the two letters that are part of the icon image,
 * replacing the current contents.
 *
 * Since:1.0
 */
void
finance_transaction_set_icon (FinanceTransaction *self,
                              const gchar        *icon)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  g_free (self->icon);

  self->icon = g_strdup (icon);

  create_icon (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON]);
}

/**
 * finance_transaction_get_color:
 * @self: a #FinanceTransaction object.
 *
 * Returns the background color of the icon.
 *
 * Returns: (transfer none): a #GdkRGBA with the color.
 *
 * Since: 1.0
 */
GdkRGBA *
finance_transaction_get_color (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), NULL);

  return self->color;
}

/**
 * finance_transaction_set_color:
 * @self: a #FinanceTransaction instance.
 * @color: a #GdkRGBA.
 *
 * Sets the background color of the icon.
 *
 * Since: 1.0
 */
void
finance_transaction_set_color (FinanceTransaction *self,
                               const GdkRGBA      *color)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  gdk_rgba_free (self->color);

  self->color = gdk_rgba_copy (color);

  create_icon (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_COLOR]);
}

/**
 * finance_transaction_get_name:
 * @self: a #FinanceTransaction object.
 *
 * Returns the transaction name.
 *
 * Returns: The transaction name as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_get_name (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), NULL);

  return gtk_entry_get_text (GTK_ENTRY (self->entry_name));
}

/**
 * finance_transaction_set_name:
 * @self: a #FinanceTransaction instance.
 * @name: the name to set, as a string.
 *
 * Sets the transaction name, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_transaction_set_name (FinanceTransaction *self,
                              const gchar        *name)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  gtk_entry_set_text (GTK_ENTRY (self->entry_name), name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_NAME]);
}

/**
 * finance_transaction_get_amount:
 * @self: a #FinanceTransaction instance.
 *
 * Gets the transaction amount.
 *
 * Returns: a #gdouble.
 *
 * Since: 1.0
 */
gdouble
finance_transaction_get_amount (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), 0.0);

  return finance_entry_monetary_get_amount (FINANCE_ENTRY_MONETARY (self->entry_amount));
}

/**
 * finance_transaction_set_amount:
 * @self: a #FinanceTransaction object.
 * @amount: a #gdouble to set it to.
 *
 * Sets transaction amount.
 *
 * Since: 1.0
 */
void
finance_transaction_set_amount (FinanceTransaction *self,
                                gdouble            amount)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  finance_entry_monetary_set_amount (FINANCE_ENTRY_MONETARY (self->entry_amount), amount);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_AMOUNT]);
}

/**
 * finance_transaction_get_date:
 * @self: a #FinanceTransaction instance.
 *
 * Returns the date of the financial transaction.
 *
 * Returns: a #GDateTime.
 *
 * Since: 1.0
 */
GDateTime *
finance_transaction_get_date (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), NULL);

  return finance_entry_date_get_date (FINANCE_ENTRY_DATE (self->entry_date));
}

/**
 * finance_transaction_set_date:
 * @self: a #FinanceTransaction object.
 * @date: a valid date, as a #GDateTime.
 *
 * Sets the date of the financial transaction.
 *
 * Since: 1.0
 */
void
finance_transaction_set_date (FinanceTransaction *self,
                              GDateTime          *date)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  finance_entry_date_set_date (FINANCE_ENTRY_DATE (self->entry_date), date);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_DATE]);
}

/**
 * finance_transaction_get_payee_name:
 * @self: a #FinanceTransaction instance.
 *
 * Returns the transaction payee name.
 *
 * Returns: The transaction payee name as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_get_payee_name (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), NULL);

  return gtk_entry_get_text (GTK_ENTRY (self->entry_payee_name));
}

/**
 * finance_transaction_set_payee_name:
 * @self: a #FinanceTransaction object.
 * @payee_name: the payee name to set, as a string.
 *
 * Sets the transaction payee name, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_transaction_set_payee_name (FinanceTransaction *self,
                                    const gchar        *payee_name)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  gtk_entry_set_text (GTK_ENTRY (self->entry_payee_name), payee_name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYEE_NAME]);
}

/**
 * finance_transaction_get_payment:
 * @self: a #FinanceTransaction instance.
 *
 * Returns the payment method of the transaction.
 *
 * Returns: a #FinancePayment.
 *
 * Since: 1.0
 */
gint
finance_transaction_get_payment (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), -1);

  return gtk_combo_box_get_active (GTK_COMBO_BOX (self->combo_payment));
}

/**
 * finance_transaction_set_payment:
 * @self: a #FinanceTransaction object.
 * @payment: a #FinancePayment.
 *
 * Sets the payment method of the transaction.
 *
 * Since: 1.0
 */
void
finance_transaction_set_payment (FinanceTransaction *self,
                                 gint               payment)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_payment), payment);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYMENT]);
}

/**
 * finance_transaction_get_payment_info:
 * @self: a #FinanceTransaciton instance.
 *
 * Returns the transaction payment information.
 *
 * Returns: The transaction payment information as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_get_payment_info (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), NULL);

  return gtk_entry_get_text (GTK_ENTRY (self->entry_payment_info));
}

/**
 * finance_transaction_set_payment_info:
 * @self: a #FinanceTransaction object.
 * @payment_info: the payment information to set, as a string.
 *
 * Sets the transaction payment information, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_transaction_set_payment_info (FinanceTransaction *self,
                                      const gchar        *payment_info)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  gtk_entry_set_text (GTK_ENTRY (self->entry_payment_info), payment_info);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYMENT_INFO]);
}

/**
 * finance_transaction_get_repeat:
 * @self: a #FinanceTransaction instance.
 *
 * Returns the transaction repeat type.
 *
 * Returns: a #FinanceRepeat.
 *
 * Since: 1.0
 */
gint
finance_transaction_get_repeat (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), -1);

  return gtk_combo_box_get_active (GTK_COMBO_BOX (self->combo_repeat));
}

/**
 * finance_transaction_set_repeat:
 * @self: a #FinanceTransaction object.
 * @repeat: a #FinanceRepeat.
 *
 * Sets the transaction repeat type.
 *
 * Since: 1.0
 */
void
finance_transaction_set_repeat (FinanceTransaction *self,
                                gint               repeat)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_repeat), repeat);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_REPEAT]);
}

/**
 * finance_transaction_get_frequency:
 * @self: a #FinanceTransaction instance.
 * 
 * Returns the transaction frequency.
 * 
 * Returns: a #FinanceFrequency.
 * 
 * Since: 1.0
 */
gint
finance_transaction_get_frequency (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), -1);
  
  return gtk_combo_box_get_active (GTK_COMBO_BOX (self->combo_frequency));
}

/**
 * finance_transaction_set_frequency:
 * @self: a #FinanceTransaction object.
 * @frequency: a #FinanceFrequency.
 * 
 * Sets the transaction frequency.
 * 
 * Since: 1.0
 */
void
finance_transaction_set_frequency (FinanceTransaction *self,
                                   gint               frequency)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));
  
  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_frequency), frequency);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FREQUENCY]);
}

/**
 * finance_transaction_get_frequency_number:
 * @self: a #FinanceTransaction instance.
 *
 * Returns the number of frequency of transactions.
 *
 * Returns: a #gint.
 *
 * Since: 1.0
 */
gint
finance_transaction_get_frequency_number (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), 0);

  return (gint)gtk_spin_button_get_value (GTK_SPIN_BUTTON (self->spin_frequency_number));
}

/**
 * finance_transaction_set_frequency_number:
 * @self: a #FinanceTransaction object.
 * @frequency_number: a #gint.
 *
 * Sets the number of frequency of transactions.
 *
 * Since: 1.0
 */
void
finance_transaction_set_frequency_number (FinanceTransaction *self,
                                          gint               frequency_number)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));
  
  if (frequency_number < 2)
    return;

  gtk_spin_button_set_value (GTK_SPIN_BUTTON (self->spin_frequency_number),
                             (gdouble)frequency_number);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FREQUENCY_NUMBER]);
}

/**
 * finance_transaction_get_frequency_date:
 * @self: a #FinanceTransaction instance.
 *
 * Returns the date of the financial transaction frequency.
 *
 * Returns: a #GDateTime.
 *
 * Since: 1.0
 */
GDateTime *
finance_transaction_get_frequency_date (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), NULL);

  return finance_entry_date_get_date (FINANCE_ENTRY_DATE (self->entry_frequency_date));
}

/**
 * finance_transaction_set_frequency_date:
 * @self: a #FinanceTransaction object.
 * @date: a valid date, as a #GDateTime.
 *
 * Sets the date of the financial transaction frequency.
 *
 * Since: 1.0
 */
void
finance_transaction_set_frequency_date (FinanceTransaction *self,
                                        GDateTime          *date)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  finance_entry_date_set_date (FINANCE_ENTRY_DATE (self->entry_frequency_date), date);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FREQUENCY_DATE]);
}

/**
 * finance_transaction_get_notes:
 * @self: a #FinanceTransaction instance.
 *
 * Returns the transaction notes information.
 *
 * Returns: The transaction notes as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_get_notes (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), NULL);

  return self->notes;
}

/**
 * finance_transaction_set_notes:
 * @self: a #FinanceTransaction object.
 * @notes: UTF-8 text to insert.
 *
 * Sets the transaction notes information, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_transaction_set_notes (FinanceTransaction *self,
                               const gchar        *notes)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  g_free (self->notes);

  if (!g_utf8_validate (notes, -1, NULL))
    return;

  self->notes = g_strdup (notes);

  gtk_text_buffer_set_text (GTK_TEXT_BUFFER (self->buffer_notes),
                            self->notes, -1);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_NOTES]);
}

/**
 * finance_transaction_get_mobile:
 * @self: a #FinanceTransaction instance.
 *
 * Gets whether the mobile layout is in its “on” or “off” state.
 *
 * Returns: %TRUE if the mobile layout is active, and %FALSE otherwise.
 *
 * Since: 1.0
 */
gboolean
finance_transaction_get_mobile (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), FALSE);

  return self->mobile;
}

/**
 * finance_transaction_set_mobile:
 * @self: a #FinanceTransaction object.
 * @mobile: a #gboolean to set it to.
 *
 * Change mobile layout states. %TRUE if the mobile layout is active, and %FALSE otherwise.
 *
 * Since: 1.0
 */
void
finance_transaction_set_mobile (FinanceTransaction  *self,
                                gboolean            mobile)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  self->mobile = mobile;

  finance_transaction_responsive_layout (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_MOBILE]);
}

/**
 * finance_transaction_create_new:
 * @self: a #FinanceTransaction object.
 *
 * Clears all data entry fields to create a new transaction.
 *
 * Since: 1.0
 */
void
finance_transaction_create_new (FinanceTransaction *self)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  g_free (self->icon);
  g_free (self->notes);

  gdk_rgba_free (self->color);

  self->icon = g_strdup ("NW");
  self->notes = g_strdup ("");

  self->color = finance_utils_random_rgba_color ();

  create_icon (self);

  //Do not forget
  finance_entry_monetary_set_amount (FINANCE_ENTRY_MONETARY (self->entry_amount), 0.0);

  gtk_text_buffer_set_text (GTK_TEXT_BUFFER (self->buffer_notes),
                            self->notes, -1);

  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_payment), 0);
  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_repeat), 0);

  gtk_entry_set_text (GTK_ENTRY (self->entry_amount), "");
  gtk_entry_set_text (GTK_ENTRY (self->entry_date), "");
  gtk_entry_set_text (GTK_ENTRY (self->entry_name), "");
  gtk_entry_set_text (GTK_ENTRY (self->entry_payee_name), "");
  gtk_entry_set_text (GTK_ENTRY (self->entry_payment_info), "");
}
