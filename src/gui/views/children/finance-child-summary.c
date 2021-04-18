/* finance-child-summary.c
 *
 * Copyright 2021 galetedanilo <galetedanilo@gmail.com>
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

#include "finance-child-summary.h"

struct _FinanceChildSummary
{
  GtkButton parent_instance;

  /* The widgets */
  GtkWidget *image_icon;
  GtkWidget *label_amount;
  GtkWidget *label_category;
  GtkWidget *label_date;
  GtkWidget *label_name;
  GtkWidget *label_payee_name;
  GtkWidget *label_payment;
  GtkWidget *label_repeat;

  GdkRGBA   *color;
  gchar     *icon;
};

G_DEFINE_TYPE (FinanceChildSummary, finance_child_summary, GTK_TYPE_BUTTON)

enum {
  PROP_0,
  PROP_AMOUNT,
  PROP_CATEGORY,
  PROP_COLOR,
  PROP_DATE,
  PROP_ICON,
  PROP_NAME,
  PROP_PAYEE_NAME,
  PROP_PAYMENT,
  PROP_REPEAT,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static void
create_icon (FinanceChildSummary *self)
{
  cairo_surface_t *surface;

  surface = finance_utils_create_circle (self->color, 100, self->icon);

  gtk_image_set_from_surface (GTK_IMAGE (self->image_icon), surface);

  g_clear_pointer (&surface, cairo_surface_destroy);
}

GtkWidget *
finance_child_summary_new (void)
{
  return g_object_new (FINANCE_TYPE_CHILD_SUMMARY, NULL);
}

static void
finance_child_summary_finalize (GObject *object)
{
  FinanceChildSummary *self = (FinanceChildSummary *)object;

  g_clear_pointer (&self->icon, g_free);

  G_OBJECT_CLASS (finance_child_summary_parent_class)->finalize (object);
}

static void
finance_child_summary_dispose (GObject *object)
{
  FinanceChildSummary *self = (FinanceChildSummary *)object;

  g_clear_pointer (&self->color, gdk_rgba_free);

  G_OBJECT_CLASS (finance_child_summary_parent_class)->dispose (object);
}

static void
finance_child_summary_get_property (GObject    *object,
                                    guint       prop_id,
                                    GValue     *value,
                                    GParamSpec *pspec)
{
  FinanceChildSummary *self = FINANCE_CHILD_SUMMARY (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      g_value_set_string (value, finance_child_summary_get_amount (self));
      break;

    case PROP_CATEGORY:
      g_value_set_string (value, finance_child_summary_get_category (self));
      break;

    case PROP_COLOR:
      g_value_set_boxed (value, finance_child_summary_get_color (self));
      break;

    case PROP_DATE:
      g_value_set_string (value, finance_child_summary_get_date (self));
      break;

    case PROP_ICON:
      g_value_set_string (value, finance_child_summary_get_icon (self));
      break;

    case PROP_NAME:
      g_value_set_string (value, finance_child_summary_get_name (self));
      break;

    case PROP_PAYEE_NAME:
      g_value_set_string (value, finance_child_summary_get_payee_name (self));
      break;

    case PROP_PAYMENT:
      g_value_set_string (value, finance_child_summary_get_payment (self));
      break;

    case PROP_REPEAT:
      g_value_set_string (value, finance_child_summary_get_repeat (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_child_summary_set_property (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec)
{
  FinanceChildSummary *self = FINANCE_CHILD_SUMMARY (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      finance_child_summary_set_amount (self, g_value_get_string (value));
      break;

    case PROP_CATEGORY:
      finance_child_summary_set_category (self, g_value_get_string (value));
      break;

    case PROP_COLOR:
      finance_child_summary_set_color (self, g_value_get_boxed (value));
      break;

    case PROP_DATE:
      finance_child_summary_set_date (self, g_value_get_string (value));
      break;

    case PROP_ICON:
      finance_child_summary_set_icon (self, g_value_get_string (value));
      break;

    case PROP_NAME:
      finance_child_summary_set_name (self, g_value_get_string (value));
      break;

    case PROP_PAYEE_NAME:
      finance_child_summary_set_payee_name (self, g_value_get_string (value));
      break;

    case PROP_PAYMENT:
      finance_child_summary_set_payment (self, g_value_get_string (value));
      break;

    case PROP_REPEAT:
      finance_child_summary_set_repeat (self, g_value_get_string (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_child_summary_class_init (FinanceChildSummaryClass *klass)
{
  GObjectClass   *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize      = finance_child_summary_finalize;
  object_class->dispose       = finance_child_summary_dispose;
  object_class->get_property  = finance_child_summary_get_property;
  object_class->set_property  = finance_child_summary_set_property;

  /**
   * FinanceChildSummary::amount:
   *
   * The transaction amount
   */
  properties[PROP_AMOUNT] =  g_param_spec_string ("amount",
                                                  "Amount",
                                                  "The transaction amount",
                                                  NULL,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceChildSummary::category:
   *
   * The transaction category
   */
  properties[PROP_CATEGORY] = g_param_spec_string ("category",
                                                   "Category",
                                                   "The transaction category",
                                                   NULL,
                                                   G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceChildSummary::color:
   *
   * The background color of the icon
   */
  properties[PROP_COLOR] = g_param_spec_boxed ("color",
                                               "Color",
                                               "The background color of the icon",
                                               GDK_TYPE_RGBA,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceChildSummary::date:
   *
   * The transaction date
   */
  properties[PROP_DATE] = g_param_spec_string ("date",
                                               "Date",
                                               "The transaction date",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceChildSummary::icon:
   *
   * The two letters that are part of the icon image
   */
  properties[PROP_ICON] = g_param_spec_string ("icon",
                                               "Icon",
                                               "The two letters that are part of the icon image",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceChildSummary::name:
   *
   * The transaction name
   */
  properties[PROP_NAME] = g_param_spec_string ("name",
                                               "Name",
                                               "The transaction name",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceChildSummary::payee_name:
   *
   * The transaction payee name
   */
  properties[PROP_PAYEE_NAME] = g_param_spec_string ("payee-name",
                                                     "Payee name",
                                                     "The transaction payee name",
                                                     NULL,
                                                     G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceChildSummary::payment:
   *
   * The payment method of the transaction
   */
  properties[PROP_PAYMENT] = g_param_spec_string ("payment",
                                                  "Payment",
                                                  "The payment method of the transaction",
                                                  NULL,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);


  /**
   * FinanceChildSummary::repeat:
   *
   * The transaction repeat type
   */
  properties[PROP_REPEAT] = g_param_spec_string ("repeat",
                                                 "Repeat",
                                                 "The transaction repeat type",
                                                 NULL,
                                                 G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/views/children/finance-child-summary.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceChildSummary, image_icon);
  gtk_widget_class_bind_template_child (widget_class, FinanceChildSummary, label_amount);
  gtk_widget_class_bind_template_child (widget_class, FinanceChildSummary, label_category);
  gtk_widget_class_bind_template_child (widget_class, FinanceChildSummary, label_date);
  gtk_widget_class_bind_template_child (widget_class, FinanceChildSummary, label_name);
  gtk_widget_class_bind_template_child (widget_class, FinanceChildSummary, label_payee_name);
  gtk_widget_class_bind_template_child (widget_class, FinanceChildSummary, label_payment);
  gtk_widget_class_bind_template_child (widget_class, FinanceChildSummary, label_repeat);
}

static void
finance_child_summary_init (FinanceChildSummary *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->color = finance_utils_random_rgba_color ();

  create_icon (self);
}

/**
 * finance_child_summary_get_icon:
 * @self: a #FinanceChildSummary object.
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
finance_child_summary_get_icon (FinanceChildSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_CHILD_SUMMARY (self), NULL);

  return self->icon;
}

/**
 * finance_child_summary_set_icon:
 * @self: a #FinanceChildSummary instance.
 * @icon: the icon to set, as a two-letter string.
 *
 * Sets the two letters that are part of the icon image,
 * replacing the current contents.
 *
 * Since:1.0
 */
void
finance_child_summary_set_icon (FinanceChildSummary *self,
                                const gchar         *icon)
{
  g_return_if_fail (FINANCE_IS_CHILD_SUMMARY (self));

  g_free (self->icon);

  self->icon = g_strdup (icon);

  create_icon (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON]);
}

/**
 * finance_child_summary_get_color:
 * @self: a #FinanceChildSummary object.
 *
 * Returns the background color of the icon.
 *
 * Returns: (transfer none): a #GdkRGBA with the color.
 *
 * Since: 1.0
 */
GdkRGBA *
finance_child_summary_get_color (FinanceChildSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_CHILD_SUMMARY (self), NULL);

  return self->color;
}

/**
 * finance_child_summary_set_color:
 * @self: a #FinanceChildSummary instance.
 * @color: a #GdkRGBA.
 *
 * Sets the background color of the icon.
 *
 * Since: 1.0
 */
void
finance_child_summary_set_color (FinanceChildSummary *self,
                                 const GdkRGBA       *color)
{
  g_return_if_fail (FINANCE_IS_CHILD_SUMMARY (self));

  gdk_rgba_free (self->color);

  self->color = gdk_rgba_copy (color);

  create_icon (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_COLOR]);
}

/**
 * finance_child_summary_get_name:
 * @self: a #FinanceChildSummary object.
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
finance_child_summary_get_name (FinanceChildSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_CHILD_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_name));
}

/**
 * finance_child_summary_set_name:
 * @self: a #FinanceChildSummary instance.
 * @name: the name to set, as a string.
 *
 * Sets the transaction name, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_child_summary_set_name (FinanceChildSummary *self,
                                const gchar         *name)
{
  g_return_if_fail (FINANCE_IS_CHILD_SUMMARY (self));

  gtk_label_set_text (GTK_LABEL (self->label_name), name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_NAME]);
}

/**
 * finance_child_summary_get_amount:
 * @self: a #FinanceChildSummary instance.
 *
 * Gets the transaction amount.
 *
 * Returns: The transaction amount as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_child_summary_get_amount (FinanceChildSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_CHILD_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_amount));
}

/**
 * finance_child_summary_set_amount:
 * @self: a #FinanceChildSummary object.
 * @amount: a amount as a string.
 *
 * Sets transaction amount.
 *
 * Since: 1.0
 */
void
finance_child_summary_set_amount (FinanceChildSummary *self,
                                  const gchar         *amount)
{
  g_return_if_fail (FINANCE_IS_CHILD_SUMMARY (self));

  gtk_label_set_text (GTK_LABEL (self->label_amount), amount);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_AMOUNT]);
}

/**
 * finance_child_summary_get_date:
 * @self: a #FinanceChildSummary instance.
 *
 * Returns the date of the financial transaction.
 *
 * Returns: The transaction date as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_child_summary_get_date (FinanceChildSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_CHILD_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_date));
}

/**
 * finance_child_summary_set_date:
 * @self: a #FinanceChildSummary object.
 * @date: a date as a string.
 *
 * Sets the date of the financial transaction.
 *
 * Since: 1.0
 */
void
finance_child_summary_set_date (FinanceChildSummary *self,
                                const gchar         *date)
{
  g_return_if_fail (FINANCE_IS_CHILD_SUMMARY (self));

  gtk_label_set_text (GTK_LABEL (self->label_date), date);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_DATE]);
}

/**
 * finance_child_summary_get_payee_name:
 * @self: a #FinanceChildSummary instance.
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
finance_child_summary_get_payee_name (FinanceChildSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_CHILD_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_payee_name));
}

/**
 * finance_child_summary_set_payee_name:
 * @self: a #FinanceChildSummary object.
 * @payee_name: a payee name to set, as a string.
 *
 * Sets the transaction payee name, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_child_summary_set_payee_name (FinanceChildSummary *self,
                                      const gchar         *payee_name)
{
  g_return_if_fail (FINANCE_IS_CHILD_SUMMARY (self));

  gtk_label_set_text (GTK_LABEL (self->label_payee_name), payee_name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYEE_NAME]);
}

/**
 * finance_child_summary_get_payment:
 * @self: a #FinanceChildSummary instance.
 *
 * Returns the payment method of the transaction.
 *
 * Returns: The transaction payment as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_child_summary_get_payment (FinanceChildSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_CHILD_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_payment));
}

/**
 * finance_child_summary_set_payment:
 * @self: a #FinanceChildSummary object.
 * @payment: a payment to set, as a string.
 *
 * Sets the payment method of the transaction.
 *
 * Since: 1.0
 */
void
finance_child_summary_set_payment (FinanceChildSummary *self,
                                   const gchar         *payment)
{
  g_return_if_fail (FINANCE_IS_CHILD_SUMMARY (self));

  gtk_label_set_text (GTK_LABEL (self->label_payment), payment);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYMENT]);
}

/**
 * finance_child_summary_get_category:
 * @self: a #FinanceChildSummary instance.
 *
 * Returns the category of the transaction.
 *
 * Returns: The transaction category as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_child_summary_get_category (FinanceChildSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_CHILD_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_category));
}

/**
 * finance_child_summary_set_category:
 * @self: a #FinanceChildSummary object.
 * @category: a category to set, as a string.
 *
 * Sets the category method of the transaction.
 *
 * Since: 1.0
 */
void
finance_child_summary_set_category (FinanceChildSummary *self,
                                    const gchar         *category)
{
  g_return_if_fail (FINANCE_IS_CHILD_SUMMARY (self));

  gtk_label_set_text (GTK_LABEL (self->label_category), category);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_CATEGORY]);
}
/**
 * finance_child_summary_get_repeat:
 * @self: a #FinanceChildSummary instance.
 *
 * Returns the repeat method of the transaction.
 *
 * Returns: The transaction repeat as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_child_summary_get_repeat (FinanceChildSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_CHILD_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_repeat));
}

/**
 * finance_child_summary_set_repeat:
 * @self: a #FinanceChildSummary object.
 * @repeat: a repeat to set, as a string.
 *
 * Sets the repeat transaction.
 *
 * Since: 1.0
 */
void
finance_child_summary_set_repeat (FinanceChildSummary *self,
                                  const gchar         *repeat)
{
  g_return_if_fail (FINANCE_IS_CHILD_SUMMARY (self));

  gtk_label_set_text (GTK_LABEL (self->label_repeat), repeat);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_REPEAT]);
}