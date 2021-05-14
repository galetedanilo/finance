/* finance-transaction-editor.c
 *
 * Copyright 2020 - 2021 galetedanilo <galetedanilo@gmail.com>
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

#include "finance-transaction-editor.h"

struct _FinanceTransactionEditor
{
  GtkGrid     parent_instance;

  /* The widgets */
  GtkWidget   *buffer_notes;
  GtkWidget   *combo_category;
  GtkWidget   *combo_frequency;
  GtkWidget   *combo_payment;
  GtkWidget   *combo_repeat;
  GtkWidget   *entry_amount;
  GtkWidget   *entry_date;
  GtkWidget   *entry_frequency_date;
  GtkWidget   *entry_name;
  GtkWidget   *entry_payee_name;
  GtkWidget   *entry_payment_info;
  GtkWidget   *image_icon;
  GtkWidget   *label_category;
  GtkWidget   *label_notes;
  GtkWidget   *label_payment;
  GtkWidget   *label_repeat;
  GtkWidget   *spin_frequency_number;

  GdkRGBA     *icon_color;

  gchar       *icon_text;
  gchar       *notes;

  gboolean    mobile;

  GSettings   *settings;

  FinanceTransaction type;
};

G_DEFINE_TYPE (FinanceTransactionEditor, finance_transaction_editor, GTK_TYPE_GRID)

enum {
  PROP_0,
  PROP_AMOUNT,
  PROP_CATEGORY,
  PROP_DATE,
  PROP_FREQUENCY,
  PROP_FREQUENCY_DATE,
  PROP_FREQUENCY_NUMBER,
  PROP_ICON_COLOR,
  PROP_ICON_TEXT,
  PROP_MOBILE,
  PROP_NAME,
  PROP_NOTES,
  PROP_PAYEE_NAME,
  PROP_PAYMENT,
  PROP_PAYMENT_INFORMATION,
  PROP_REPEAT,
  PROP_TYPE,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static void
create_icon (FinanceTransactionEditor *self)
{
  cairo_surface_t *surface;

  surface = finance_utils_create_circle (self->icon_color, 140, self->icon_text);

  gtk_image_set_from_surface (GTK_IMAGE (self->image_icon), surface);

  g_clear_pointer (&surface, cairo_surface_destroy);
}

static void
on_combo_box_frequency_changed (GtkComboBox *widget,
                                gpointer     user_data)
{
  FinanceTransactionEditor *self = FINANCE_TRANSACTION_EDITOR (user_data);

  FinanceFrequency frequency = gtk_combo_box_get_active (GTK_COMBO_BOX (widget));

  gtk_spin_button_set_value (GTK_SPIN_BUTTON (self->spin_frequency_number), 2);

  finance_date_entry_clear (FINANCE_DATE_ENTRY (self->entry_frequency_date));

  switch (frequency)
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
on_combo_box_repeat_changed (GtkComboBox *widget,
                             gpointer     user_data)
{
  FinanceTransactionEditor *self = FINANCE_TRANSACTION_EDITOR (user_data);

  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_frequency), 0);

  gtk_widget_set_visible (self->combo_frequency,
                          gtk_combo_box_get_active (widget));

}

static void
finance_transaction_editor_responsive_layout (FinanceTransactionEditor *self)
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
finance_transaction_editor_new (void)
{
  return g_object_new (FINANCE_TYPE_TRANSACTION_EDITOR, NULL);
}

static void
finance_transaction_editor_finalize (GObject *object)
{
  FinanceTransactionEditor *self = (FinanceTransactionEditor *)object;

  g_clear_pointer (&self->icon_text, g_free);
  g_clear_pointer (&self->notes, g_free);

  G_OBJECT_CLASS (finance_transaction_editor_parent_class)->finalize (object);
}

static void
finance_transaction_editor_dispose (GObject *object)
{
  FinanceTransactionEditor *self = (FinanceTransactionEditor *)object;

  g_clear_pointer (&self->icon_color, gdk_rgba_free);
  g_clear_object (&self->settings);

  G_OBJECT_CLASS (finance_transaction_editor_parent_class)->dispose (object);
}

static void
finance_transaction_editor_get_property (GObject    *object,
                                         guint       prop_id,
                                         GValue     *value,
                                         GParamSpec *pspec)
{
  FinanceTransactionEditor *self = FINANCE_TRANSACTION_EDITOR (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      g_value_set_double (value, finance_transaction_editor_get_amount (self));
      break;

    case PROP_CATEGORY:
      g_value_set_int (value, finance_transaction_editor_get_category (self));
      break;

    case PROP_DATE:
      g_value_set_boxed (value, finance_transaction_editor_get_date (self));
      break;

    case PROP_FREQUENCY:
      g_value_set_enum (value, finance_transaction_editor_get_frequency (self));
      break;

    case PROP_FREQUENCY_DATE:
      g_value_set_boxed (value,finance_transaction_editor_get_frequency_date (self));
      break;

    case PROP_FREQUENCY_NUMBER:
      g_value_set_int (value, finance_transaction_editor_get_frequency_number (self));
      break;


    case PROP_ICON_COLOR:
      g_value_set_boxed (value, finance_transaction_editor_get_icon_color (self));
      break;

    case PROP_ICON_TEXT:
      g_value_set_string (value, finance_transaction_editor_get_icon_text (self));
      break;

    case PROP_MOBILE:
      g_value_set_boolean (value, finance_transaction_editor_get_mobile (self));
      break;

    case PROP_NAME:
      g_value_set_string (value, finance_transaction_editor_get_name (self));
      break;

    case PROP_NOTES:
      g_value_set_string (value, finance_transaction_editor_get_notes (self));
      break;

    case PROP_PAYEE_NAME:
      g_value_set_string (value, finance_transaction_editor_get_payee_name (self));
      break;

    case PROP_PAYMENT:
      g_value_set_enum (value, finance_transaction_editor_get_payment (self));
      break;

    case PROP_PAYMENT_INFORMATION:
      g_value_set_string (value, finance_transaction_editor_get_payment_information (self));
      break;

    case PROP_REPEAT:
      g_value_set_enum (value, finance_transaction_editor_get_repeat (self));
      break;

    case PROP_TYPE:
      g_value_set_enum (value, finance_transaction_editor_get_type (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_transaction_editor_set_property (GObject      *object,
                                         guint         prop_id,
                                         const GValue *value,
                                         GParamSpec   *pspec)
{
  FinanceTransactionEditor *self = FINANCE_TRANSACTION_EDITOR (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      finance_transaction_editor_set_amount (self, g_value_get_double (value));
      break;

    case PROP_CATEGORY:
      finance_transaction_editor_set_category (self, g_value_get_int (value));
      break;

    case PROP_DATE:
      finance_transaction_editor_set_date (self, g_value_get_boxed (value));
      break;

    case PROP_FREQUENCY:
      finance_transaction_editor_set_frequency (self, g_value_get_enum (value));
      break;

    case PROP_FREQUENCY_DATE:
      finance_transaction_editor_set_frequency_date (self, g_value_get_boxed (value));
      break;

    case PROP_FREQUENCY_NUMBER:
      finance_transaction_editor_set_frequency_number (self, g_value_get_int (value));
      break;

    case PROP_ICON_COLOR:
      finance_transaction_editor_set_icon_color (self, g_value_get_boxed (value));
      break;

    case PROP_ICON_TEXT:
      finance_transaction_editor_set_icon_text (self, g_value_get_string (value));
      break;

    case PROP_MOBILE:
      finance_transaction_editor_set_mobile (self, g_value_get_boolean (value));
      break;

    case PROP_NAME:
      finance_transaction_editor_set_name (self, g_value_get_string (value));
      break;

    case PROP_NOTES:
      finance_transaction_editor_set_notes (self, g_value_get_string (value));
      break;

    case PROP_PAYEE_NAME:
      finance_transaction_editor_set_payee_name (self, g_value_get_string (value));
      break;

    case PROP_PAYMENT:
      finance_transaction_editor_set_payment (self, g_value_get_enum (value));
      break;

    case PROP_PAYMENT_INFORMATION:
      finance_transaction_editor_set_payment_information (self, g_value_get_string (value));
      break;

    case PROP_REPEAT:
      finance_transaction_editor_set_repeat (self, g_value_get_enum (value));
      break;

    case PROP_TYPE:
      finance_transaction_editor_set_type (self, g_value_get_enum (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_transaction_editor_class_init (FinanceTransactionEditorClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  g_type_ensure (FINANCE_TYPE_DATE_ENTRY);
  g_type_ensure (FINANCE_TYPE_MONETARY_ENTRY);

  object_class->finalize     = finance_transaction_editor_finalize;
  object_class->dispose      = finance_transaction_editor_dispose;
  object_class->get_property = finance_transaction_editor_get_property;
  object_class->set_property = finance_transaction_editor_set_property;

  /**
   * FinanceTransactionEditor::amount:
   *
   * The transaction amount
   */
  properties[PROP_AMOUNT] =  g_param_spec_double ("amount",
                                                  "Amount",
                                                  "The transaction amount",
                                                  0.0,
                                                  G_MAXDOUBLE,
                                                  0.0,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionEditor::date:
   *
   * The transaction date
   */
  properties[PROP_DATE] = g_param_spec_boxed ("date",
                                              "Date",
                                              "The transaction date",
                                              G_TYPE_DATE_TIME,
                                              G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionEditor::frequency:
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
   * FinanceTransactionEditor::frequency_date:
   *
   * The date of the financial transaction frequency
   */
  properties[PROP_FREQUENCY_DATE] = g_param_spec_boxed ("frequency-date",
                                                        "Fequency date",
                                                        "The date of the financial transaction frequency",
                                                        NULL,
                                                        G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionEditor::frequency_number:
   *
   * The number of frequency of transactions
   */
  properties[PROP_FREQUENCY_NUMBER] = g_param_spec_int ("frequency-number",
                                                        "Frequency Number",
                                                        "The number of frequency of transactions",
                                                        2, 365, 2,
                                                        G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionEditor::icon-color:
   *
   * The background color of the icon
   */
  properties[PROP_ICON_COLOR] = g_param_spec_boxed ("icon-color",
                                                    "Icon color",
                                                    "The background color of the icon",
                                                    GDK_TYPE_RGBA,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionEditor::icon-text:
   *
   * The two letters that are part of the icon image
   */
  properties[PROP_ICON_TEXT] = g_param_spec_string ("icon-text",
                                                    "Icon text",
                                                    "The two letters that are part of the icon image",
                                                    NULL,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionEditor::mobile:
   *
   * The transaction mobile
   */
  properties[PROP_MOBILE] = g_param_spec_boolean ("mobile",
                                                  "Mobile",
                                                  "The transaction mobile",
                                                  FALSE,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionEditor::name:
   *
   * The transaction name
   */
  properties[PROP_NAME] = g_param_spec_string ("name",
                                               "Name",
                                               "The transaction name",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionEditor::notes:
   *
   * The transaction notes information
   */
  properties[PROP_NOTES] = g_param_spec_string ("notes",
                                                "Notes",
                                                "The transaction notes information",
                                                NULL,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);


  /**
   * FinanceTransactionEditor::payee_name:
   *
   * The transaction payee name
   */
  properties[PROP_PAYEE_NAME] = g_param_spec_string ("payee-name",
                                                     "Payee name",
                                                     "The transaction payee name",
                                                     NULL,
                                                     G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionEditor::payment:
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
   * FinanceTransactionEditor::payment_information:
   *
   * The transaction payment information
   */
  properties[PROP_PAYMENT_INFORMATION] = g_param_spec_string ("payment-information",
                                                              "Payment information",
                                                              "The transaction payment information",
                                                              NULL,
                                                              G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionEditor::repeat:
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
   * FinanceTransactionEditor::type:
   *
   * The transaction type
   */
  properties[PROP_TYPE] = g_param_spec_enum ("type",
                                             "The type",
                                             "The transaction type",
                                             FINANCE_TYPE_TRANSACTION,
                                             FINANCE_CREDIT,
                                             G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/editor/finance-transaction-editor.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, buffer_notes);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, combo_category);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, combo_frequency);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, combo_payment);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, combo_repeat);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, entry_amount);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, entry_date);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, entry_frequency_date);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, entry_name);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, entry_payee_name);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, entry_payment_info);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, image_icon);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, label_category);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, label_notes);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, label_payment);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, label_repeat);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionEditor, spin_frequency_number);

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_combo_box_repeat_changed);
  gtk_widget_class_bind_template_callback (widget_class, on_combo_box_frequency_changed);

}

static void
finance_transaction_editor_init (FinanceTransactionEditor *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->icon_text = g_strdup ("NW");

  self->icon_color = finance_utils_random_rgba_color ();

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
 * finance_transaction_editor_get_amount:
 * @self: a #FinanceTransactionEditor
 *
 * Gets the transaction amount
 *
 * Returns: a #gdouble
 *
 * Since: 1.0
 */
gdouble
finance_transaction_editor_get_amount (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), 0.0);

  return finance_monetary_entry_get_amount (FINANCE_MONETARY_ENTRY (self->entry_amount));
}

/**
 * finance_transaction_editor_set_amount:
 * @self: a #FinanceTransactionEditor
 * @amount: a #gdouble to set it to
 *
 * Sets transaction amount
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_amount (FinanceTransactionEditor *self,
                                       gdouble                   amount)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));
  g_return_if_fail (amount < 0);

  finance_monetary_entry_set_amount (FINANCE_MONETARY_ENTRY (self->entry_amount), amount);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_AMOUNT]);
}

/**
 * finance_transaction_editor_get_date:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the transaction date
 *
 * Returns: (transfer none): a #GDateTime with the date
 *
 * Since: 1.0
 */
GDateTime *
finance_transaction_editor_get_date (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), NULL);

  return finance_date_entry_get_date (FINANCE_DATE_ENTRY (self->entry_date));
}

/**
 * finance_transaction_editor_set_date:
 * @self: a #FinanceTransactionEditor
 * @date: a valid #GDateTime
 *
 * Sets the date of the financial transaction
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_date (FinanceTransactionEditor *self,
                                     GDateTime                *date)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  finance_date_entry_set_date (FINANCE_DATE_ENTRY (self->entry_date), date);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_DATE]);
}

/**
 * finance_transaction_editor_get_frequency:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the transaction frequency
 *
 * Returns: a #FinanceFrequency.
 *
 * Since: 1.0
 */
gint
finance_transaction_editor_get_frequency (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), -1);

  return gtk_combo_box_get_active (GTK_COMBO_BOX (self->combo_frequency));
}

/**
 * finance_transaction_editor_set_frequency:
 * @self: a #FinanceTransaction
 * @frequency: a #FinanceFrequency
 *
 * Sets the transaction frequency
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_frequency (FinanceTransactionEditor *self,
                                          gint                      frequency)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_frequency), frequency);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FREQUENCY]);
}

/**
 * finance_transaction_editor_get_frequency_date:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the transaction frequency date
 *
 * Returns: (transfer none): a #GDateTime with the date
 *
 * Since: 1.0
 */
GDateTime *
finance_transaction_editor_get_frequency_date (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), NULL);

  return finance_date_entry_get_date (FINANCE_DATE_ENTRY (self->entry_frequency_date));
}

/**
 * finance_transaction_editor_set_frequency_date:
 * @self: a #FinanceTransactionEditor
 * @date: a valid #GDateTime
 *
 * Sets the date of the financial transaction frequency.
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_frequency_date (FinanceTransactionEditor *self,
                                               GDateTime                *date)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  finance_date_entry_set_date (FINANCE_DATE_ENTRY (self->entry_frequency_date), date);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FREQUENCY_DATE]);
}

/**
 * finance_transaction_editor_get_frequency_number:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the number of frequency of transactions
 *
 * Returns: a #gint
 *
 * Since: 1.0
 */
gint
finance_transaction_editor_get_frequency_number (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), -1);

  return (gint)gtk_spin_button_get_value (GTK_SPIN_BUTTON (self->spin_frequency_number));
}

/**
 * finance_transaction_editor_set_frequency_number:
 * @self: a #FinanceTransactionEditor
 * @frequency_number: a #gint
 *
 * Sets the number of frequency of transactions
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_frequency_number (FinanceTransactionEditor *self,
                                                 gint                      frequency_number)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));
  g_return_if_fail (frequency_number < 2);

  gtk_spin_button_set_value (GTK_SPIN_BUTTON (self->spin_frequency_number),
                             (gdouble)frequency_number);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FREQUENCY_NUMBER]);
}

/**
 * finance_transaction_editor_get_icon_color:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the background color of the icon
 *
 * Returns: (transfer none): a #GdkRGBA with the color
 *
 * Since: 1.0
 */
GdkRGBA *
finance_transaction_editor_get_icon_color (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), NULL);

  return self->icon_color;
}

/**
 * finance_transaction_editor_set_icon_color:
 * @self: a #FinanceTransactionEditor
 * @color: a #GdkRGBA
 *
 * Sets the background color of the icon
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_icon_color (FinanceTransactionEditor *self,
                                           const GdkRGBA            *color)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  gdk_rgba_free (self->icon_color);

  self->icon_color = gdk_rgba_copy (color);

  create_icon (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON_COLOR]);
}

/**
 * finance_transaction_editor_get_icon_text:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the two letters that are part of the icon image
 *
 * Returns: A two-letter string , or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_editor_get_icon (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), NULL);

  return self->icon_text;
}

/**
 * finance_transaction_editor_set_icon_text:
 * @self: a #FinanceTransactionEditor
 * @icon: the text to set, as a two-letter string
 *
 * Sets the two letters that are part of the icon image,
 * replacing the current contents.
 *
 * Since:1.0
 */
void
finance_transaction_editor_set_icon_text (FinanceTransactionEditor *self,
                                          const gchar              *text)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  g_free (self->icon_text);

  self->icon_text = g_strdup (text);

  create_icon (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON_TEXT]);
}

/**
 * finance_transaction_editor_get_mobile:
 * @self: a #FinanceTransactionEditor
 *
 * Gets whether the mobile layout is in its “on” or “off” state
 *
 * Returns: %TRUE if the mobile layout is active, and %FALSE otherwise
 *
 * Since: 1.0
 */
gboolean
finance_transaction_editor_get_mobile (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), FALSE);

  return self->mobile;
}

/**
 * finance_transaction_editor_set_mobile:
 * @self: a #FinanceTransactionEditor
 * @mobile: a #gboolean to set it to
 *
 * Change mobile layout states. %TRUE if the mobile layout is active, and %FALSE otherwise
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_mobile (FinanceTransactionEditor *self,
                                       gboolean                  mobile)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  self->mobile = mobile;

  finance_transaction_editor_responsive_layout (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_MOBILE]);
}


/**
 * finance_transaction_editor_get_name:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the transaction name
 *
 * Returns: The transaction name as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_editor_get_name (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), NULL);

  return gtk_entry_get_text (GTK_ENTRY (self->entry_name));
}

/**
 * finance_transaction_editor_set_name:
 * @self: a #FinanceTransactionEditor
 * @name: the name to set, as a string
 *
 * Sets the transaction name, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_name (FinanceTransactionEditor *self,
                                     const gchar              *name)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  gtk_entry_set_text (GTK_ENTRY (self->entry_name), name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_NAME]);
}

/**
 * finance_transaction_editor_get_notes:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the transaction notes information
 *
 * Returns: The transaction notes as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_editor_get_notes (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), NULL);

  return self->notes;
}

/**
 * finance_transaction_editor_set_notes:
 * @self: a #FinanceTransactionEditor
 * @notes: the notes to set, as a UTF-8 text
 *
 * Sets the transaction notes information, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_notes (FinanceTransactionEditor *self,
                                      const gchar              *notes)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));
  g_return_if_fail (g_utf8_validate (notes, -1, NULL) == FALSE);

  g_free (self->notes);

  self->notes = g_strdup (notes);

  gtk_text_buffer_set_text (GTK_TEXT_BUFFER (self->buffer_notes),
                            self->notes, -1);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_NOTES]);
}

/**
 * finance_transaction_editor_get_payee_name:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the transaction payee name
 *
 * Returns: The transaction payee name as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_editor_get_payee_name (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), NULL);

  return gtk_entry_get_text (GTK_ENTRY (self->entry_payee_name));
}

/**
 * finance_transaction_editor_set_payee_name:
 * @self: a #FinanceTransactionEditor
 * @payee_name: the payee name to set, as a string
 *
 * Sets the transaction payee name, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_payee_name (FinanceTransactionEditor *self,
                                           const gchar              *payee_name)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  gtk_entry_set_text (GTK_ENTRY (self->entry_payee_name), payee_name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYEE_NAME]);
}

/**
 * finance_transaction_editor_get_payment:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the payment method of the transaction
 *
 * Returns: a #FinancePayment
 *
 * Since: 1.0
 */
gint
finance_transaction_editor_get_payment (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), -1);

  return gtk_combo_box_get_active (GTK_COMBO_BOX (self->combo_payment));
}

/**
 * finance_transaction_editor_set_payment:
 * @self: a #FinanceTransactionEditor
 * @payment: a #FinancePayment
 *
 * Sets the payment method of the transaction
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_payment (FinanceTransactionEditor *self,
                                        gint                      payment)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_payment), payment);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYMENT]);
}

/**
 * finance_transaction_editor_get_payment_information:
 * @self: a #FinanceTransacitonEditor
 *
 * Returns the transaction payment information
 *
 * Returns: The transaction payment information as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_editor_get_payment_information (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), NULL);

  return gtk_entry_get_text (GTK_ENTRY (self->entry_payment_info));
}

/**
 * finance_transaction_editor_set_payment_information:
 * @self: a #FinanceTransactionEditor
 * @information: the payment information to set, as a string
 *
 * Sets the transaction payment information, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_payment_information (FinanceTransactionEditor *self,
                                                    const gchar              *information)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  gtk_entry_set_text (GTK_ENTRY (self->entry_payment_info), information);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYMENT_INFORMATION]);
}

/**
 * finance_transaction_editor_get_repeat:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the transaction repeat type
 *
 * Returns: a #FinanceRepeat
 *
 * Since: 1.0
 */
gint
finance_transaction_editor_get_repeat (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), -1);

  return gtk_combo_box_get_active (GTK_COMBO_BOX (self->combo_repeat));
}

/**
 * finance_transaction_editor_set_repeat:
 * @self: a #FinanceTransactionEditor
 * @repeat: a #FinanceRepeat
 *
 * Sets the transaction repeat type
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_repeat (FinanceTransactionEditor *self,
                                       gint                      repeat)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_repeat), repeat);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_REPEAT]);
}

/**
 * finance_transaction_editor_get_type:
 * @self: a #FinanceTransactionEditor
 *
 * Returns the transaction type
 *
 * Returns: a #FinanceTransaction
 *
 * Since: 1.0
 */
gint
finance_transaction_editor_get_type (FinanceTransactionEditor *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self), -1);

  return self->type;
}

/**
 * finance_transaction_editor_set_type:
 * @self: a #FinanceTransactionEditor
 * @type: a #FinanceTransaction
 *
 * Sets the transaction type
 *
 * Since: 1.0
 */
void
finance_transaction_editor_set_type (FinanceTransactionEditor *self,
                                     gint                      type)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  self->type = type;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TYPE]);
}

/**
 * finance_transaction_editor_clear:
 * @self: a #FinanceTransactionEditor
 *
 * Clears all data entry fields to create a new transaction
 *
 * Since: 1.0
 */
void
finance_transaction_editor_clear (FinanceTransactionEditor *self)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_EDITOR (self));

  g_clear_pointer (&self->icon_text, g_free);
  g_clear_pointer (&self->notes, g_free);

  gdk_rgba_free (self->icon_color);

  self->icon_text = g_strdup ("NW");
  self->notes = g_strdup ("");

  self->icon_color = finance_utils_random_rgba_color ();

  create_icon (self);

  finance_date_entry_clear (FINANCE_DATE_ENTRY (self->entry_date));
  finance_monetary_entry_clear (FINANCE_MONETARY_ENTRY (self->entry_amount));

  gtk_text_buffer_set_text (GTK_TEXT_BUFFER (self->buffer_notes),
                            self->notes, -1);

  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_payment), 0);
  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_repeat), 0);

  gtk_entry_set_text (GTK_ENTRY (self->entry_name), "");
  gtk_entry_set_text (GTK_ENTRY (self->entry_payee_name), "");
  gtk_entry_set_text (GTK_ENTRY (self->entry_payment_info), "");
}
