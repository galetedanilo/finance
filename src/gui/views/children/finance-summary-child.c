/* finance-summary-child.c
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

#include "finance-summary-child.h"

#include "finance-enums.h"

struct _FinanceSummaryChild
{
  GtkButton parent_instance;

  /* The widgets */
  GtkWidget *check_button;
  GtkWidget *image_icon;
  GtkWidget *label_amount;
  GtkWidget *label_category;
  GtkWidget *label_date;
  GtkWidget *label_name;
  GtkWidget *label_payee_name;
  GtkWidget *label_payment;
  GtkWidget *label_repeat;

  gchar     *icon;

  GdkRGBA   *color;
};

G_DEFINE_TYPE (FinanceSummaryChild, finance_summary_child, GTK_TYPE_BUTTON)

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
  PROP_SELECTED,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static void
create_icon (FinanceSummaryChild *self)
{
  cairo_surface_t *surface;

  surface = finance_utils_create_circle (self->color, 100, self->icon);

  gtk_image_set_from_surface (GTK_IMAGE (self->image_icon), surface);

  g_clear_pointer (&surface, cairo_surface_destroy);
}

static void
on_check_button_toggled (GtkToggleButton *button,
                         gpointer         user_data)
{
  FinanceSummaryChild *self = FINANCE_SUMMARY_CHILD (user_data);


}

GtkWidget *
finance_summary_child_new (void)
{
  return g_object_new (FINANCE_TYPE_SUMMARY_CHILD, NULL);
}

static void
finance_summary_child_finalize (GObject *object)
{
  FinanceSummaryChild *self = (FinanceSummaryChild *)object;

  g_clear_pointer (&self->icon, g_free);

  G_OBJECT_CLASS (finance_summary_child_parent_class)->finalize (object);
}

static void
finance_summary_child_dispose (GObject *object)
{
  FinanceSummaryChild *self = (FinanceSummaryChild *)object;

  g_clear_pointer (&self->color, gdk_rgba_free);

  G_OBJECT_CLASS (finance_summary_child_parent_class)->dispose (object);
}

static void
finance_summary_child_get_property (GObject    *object,
                                    guint       prop_id,
                                    GValue     *value,
                                    GParamSpec *pspec)
{
  FinanceSummaryChild *self = FINANCE_SUMMARY_CHILD (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      g_value_set_string (value, finance_summary_child_get_amount (self));
      break;

    case PROP_CATEGORY:
      g_value_set_string (value, finance_summary_child_get_category (self));
      break;

    case PROP_COLOR:
      g_value_set_boxed (value, finance_summary_child_get_color (self));
      break;

    case PROP_DATE:
      g_value_set_string (value, finance_summary_child_get_date (self));
      break;

    case PROP_ICON:
      g_value_set_string (value, finance_summary_child_get_icon (self));
      break;

    case PROP_NAME:
      g_value_set_string (value, finance_summary_child_get_name (self));
      break;

    case PROP_PAYEE_NAME:
      g_value_set_string (value, finance_summary_child_get_payee_name (self));
      break;

    case PROP_PAYMENT:
      g_value_set_string (value, finance_summary_child_get_payment (self));
      break;

    case PROP_REPEAT:
      g_value_set_string (value, finance_summary_child_get_repeat (self));
      break;

    case PROP_SELECTED:
      g_value_set_boolean (value, finance_summary_child_get_selected (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_summary_child_set_property (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec)
{
  FinanceSummaryChild *self = FINANCE_SUMMARY_CHILD (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      finance_summary_child_set_amount (self, g_value_get_string (value));
      break;

    case PROP_CATEGORY:
      finance_summary_child_set_category (self, g_value_get_string (value));
      break;

    case PROP_COLOR:
      finance_summary_child_set_color (self, g_value_get_boxed (value));
      break;

    case PROP_DATE:
      finance_summary_child_set_date (self, g_value_get_string (value));
      break;

    case PROP_ICON:
      finance_summary_child_set_icon (self, g_value_get_string (value));
      break;

    case PROP_NAME:
      finance_summary_child_set_name (self, g_value_get_string (value));
      break;

    case PROP_PAYEE_NAME:
      finance_summary_child_set_payee_name (self, g_value_get_string (value));
      break;

    case PROP_PAYMENT:
      finance_summary_child_set_payment (self, g_value_get_string (value));
      break;

    case PROP_REPEAT:
      finance_summary_child_set_repeat (self, g_value_get_string (value));
      break;

    case PROP_SELECTED:
      finance_summary_child_set_selected (self, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_summary_child_class_init (FinanceSummaryChildClass *klass)
{
  GObjectClass   *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize      = finance_summary_child_finalize;
  object_class->dispose       = finance_summary_child_dispose;
  object_class->get_property  = finance_summary_child_get_property;
  object_class->set_property  = finance_summary_child_set_property;

  /**
   * FinanceSummaryChild::amount:
   *
   * The transaction amount as a string
   */
  properties[PROP_AMOUNT] =  g_param_spec_string ("amount",
                                                  "Amount",
                                                  "The transaction amount",
                                                  NULL,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceSummaryChild::category:
   *
   * The transaction category
   */
  properties[PROP_CATEGORY] = g_param_spec_string ("category",
                                                   "Category",
                                                   "The transaction category",
                                                   NULL,
                                                   G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceSummaryChild::color:
   *
   * The background color of the icon
   */
  properties[PROP_COLOR] = g_param_spec_boxed ("color",
                                               "Color",
                                               "The background color of the icon",
                                               GDK_TYPE_RGBA,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceSummaryChild::date:
   *
   * The transaction date
   */
  properties[PROP_DATE] = g_param_spec_string ("date",
                                               "Date",
                                               "The transaction date",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceSummaryChild::icon:
   *
   * The two letters that are part of the icon image
   */
  properties[PROP_ICON] = g_param_spec_string ("icon",
                                               "Icon",
                                               "The two letters that are part of the icon image",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceSummaryChild::name:
   *
   * The transaction name
   */
  properties[PROP_NAME] = g_param_spec_string ("name",
                                               "Name",
                                               "The transaction name",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceSummaryChild::payee_name:
   *
   * The transaction payee name
   */
  properties[PROP_PAYEE_NAME] = g_param_spec_string ("payee-name",
                                                     "Payee name",
                                                     "The transaction payee name",
                                                     NULL,
                                                     G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceSummaryChild::payment:
   *
   * The payment method of the transaction
   */
  properties[PROP_PAYMENT] = g_param_spec_string ("payment",
                                                  "Payment",
                                                  "The payment method of the transaction",
                                                  NULL,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceSummaryChild::repeat:
   *
   * The transaction repeat type
   */
  properties[PROP_REPEAT] = g_param_spec_string ("repeat",
                                                 "Repeat",
                                                 "The transaction repeat type",
                                                 NULL,
                                                 G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

    /**
   * FinanceSummaryChild::selected:
   *
   * The summary child is selected
   */
  properties[PROP_SELECTED] = g_param_spec_boolean ("selected",
                                                    "Select",
                                                    "The summary child is selected",
                                                    FALSE,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/views/children/finance-summary-child.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceSummaryChild, check_button);
  gtk_widget_class_bind_template_child (widget_class, FinanceSummaryChild, image_icon);
  gtk_widget_class_bind_template_child (widget_class, FinanceSummaryChild, label_amount);
  gtk_widget_class_bind_template_child (widget_class, FinanceSummaryChild, label_category);
  gtk_widget_class_bind_template_child (widget_class, FinanceSummaryChild, label_date);
  gtk_widget_class_bind_template_child (widget_class, FinanceSummaryChild, label_name);
  gtk_widget_class_bind_template_child (widget_class, FinanceSummaryChild, label_payee_name);
  gtk_widget_class_bind_template_child (widget_class, FinanceSummaryChild, label_payment);
  gtk_widget_class_bind_template_child (widget_class, FinanceSummaryChild, label_repeat);

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_check_button_toggled);
}

static void
finance_summary_child_init (FinanceSummaryChild *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->color = finance_utils_random_rgba_color ();

  create_icon (self);
}

/**
 * finance_summary_child_get_amount:
 * @self: a #FinanceSummaryChild
 *
 * Returns the transaction amount as a string
 *
 * Returns: The transaction amount as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_summary_child_get_amount (FinanceSummaryChild *self)
{
  g_return_val_if_fail (FINANCE_IS_SUMMARY_CHILD (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_amount));
}

/**
 * finance_summary_child_set_amount_string:
 * @self: a #FinanceSummaryChild
 * @amount: a amount to set, as a string
 *
 * Sets transaction amount
 *
 * Since: 1.0
 */
void
finance_summary_child_set_amount (FinanceSummaryChild *self,
                                  const gchar         *amount)
{
  g_return_if_fail (FINANCE_IS_SUMMARY_CHILD (self));

  gtk_label_set_text (GTK_LABEL (self->label_amount), amount);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_AMOUNT]);
}

/**
 * finance_summary_child_get_category:
 * @self: a #FinanceSummaryChild
 *
 * Returns the transaction category
 *
 * Returns: The transaction category as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_summary_child_get_category (FinanceSummaryChild *self)
{
  g_return_val_if_fail (FINANCE_IS_SUMMARY_CHILD (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_category));
}

/**
 * finance_summary_child_set_category:
 * @self: a #FinanceSummaryChild
 * @category: a category to set, as a string
 *
 * Sets the category method of the transaction
 *
 * Since: 1.0
 */
void
finance_summary_child_set_category (FinanceSummaryChild *self,
                                    const gchar         *category)
{
  g_return_if_fail (FINANCE_IS_SUMMARY_CHILD (self));

  gtk_label_set_text (GTK_LABEL (self->label_category), category);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_CATEGORY]);
}

/**
 * finance_summary_child_get_color:
 * @self: a #FinanceSummaryChild
 *
 * Returns the background color of the icon
 *
 * Returns: (transfer none): a #GdkRGBA with the color.
 *
 * Since: 1.0
 */
GdkRGBA *
finance_summary_child_get_color (FinanceSummaryChild *self)
{
  g_return_val_if_fail (FINANCE_IS_SUMMARY_CHILD (self), NULL);

  return self->color;
}

/**
 * finance_summary_child_set_color:
 * @self: a #FinanceSummaryChild
 * @color: a #GdkRGBA
 *
 * Sets the background color of the icon
 *
 * Since: 1.0
 */
void
finance_summary_child_set_color (FinanceSummaryChild *self,
                                 const GdkRGBA       *color)
{
  g_return_if_fail (FINANCE_IS_SUMMARY_CHILD (self));

  g_clear_pointer (&self->color, gdk_rgba_free);

  self->color = gdk_rgba_copy (color);

  create_icon (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_COLOR]);
}

/**
 * finance_summary_child_get_date:
 * @self: a #FinanceSummaryChild
 *
 * Returns the transaction date
 *
 * Returns: The transaction date as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_summary_child_get_date (FinanceSummaryChild *self)
{
  g_return_val_if_fail (FINANCE_IS_SUMMARY_CHILD (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_date));
}

/**
 * finance_summary_child_set_date:
 * @self: a #FinanceSummaryChild
 * @date: a valid date, as a string
 *
 * Sets the date of the financial transaction
 *
 * Since: 1.0
 */
void
finance_summary_child_set_date (FinanceSummaryChild *self,
                                const gchar         *date)
{
  g_return_if_fail (FINANCE_IS_SUMMARY_CHILD (self));

  gtk_label_set_text (GTK_LABEL (self->label_date), date);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_DATE]);
}

/**
 * finance_summary_child_get_icon:
 * @self: a #FinanceSummaryChild
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
finance_summary_child_get_icon (FinanceSummaryChild *self)
{
  g_return_val_if_fail (FINANCE_IS_SUMMARY_CHILD (self), NULL);

  return self->icon;
}

/**
 * finance_summary_child_set_icon:
 * @self: a #FinanceSummaryChild
 * @icon: the icon to set, as a two-letter string
 *
 * Sets the two letters that are part of the icon image,
 * replacing the current contents.
 *
 * Since:1.0
 */
void
finance_summary_child_set_icon (FinanceSummaryChild *self,
                                const gchar         *icon)
{
  g_return_if_fail (FINANCE_IS_SUMMARY_CHILD (self));

  g_clear_pointer (&self->icon, g_free);

  self->icon = g_strdup (icon);

  create_icon (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON]);
}

/**
 * finance_summary_child_get_name:
 * @self: a #FinanceSummaryChild
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
finance_summary_child_get_name (FinanceSummaryChild *self)
{
  g_return_val_if_fail (FINANCE_IS_SUMMARY_CHILD (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_name));
}

/**
 * finance_summary_child_set_name:
 * @self: a #FinanceSummaryChild
 * @name: the name to set, as a string
 *
 * Sets the transaction name, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_summary_child_set_name (FinanceSummaryChild *self,
                                const gchar         *name)
{
  g_return_if_fail (FINANCE_IS_SUMMARY_CHILD (self));

  gtk_label_set_text (GTK_LABEL (self->label_name), name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_NAME]);
}

/**
 * finance_summary_child_get_payee_name:
 * @self: a #FinanceSummaryChild
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
finance_summary_child_get_payee_name (FinanceSummaryChild *self)
{
  g_return_val_if_fail (FINANCE_IS_SUMMARY_CHILD (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_payee_name));
}

/**
 * finance_summary_child_set_payee_name:
 * @self: a #FinanceSummaryChild
 * @payee_name: a payee name to set, as a string
 *
 * Sets the transaction payee name, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_summary_child_set_payee_name (FinanceSummaryChild *self,
                                      const gchar         *payee_name)
{
  g_return_if_fail (FINANCE_IS_SUMMARY_CHILD (self));

  gtk_label_set_text (GTK_LABEL (self->label_payee_name), payee_name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYEE_NAME]);
}

/**
 * finance_summary_child_get_payment:
 * @self: a #FinanceSummaryChild
 *
 * Returns the transaction payment
 *
 * Returns: The transaction payment as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_summary_child_get_payment (FinanceSummaryChild *self)
{
  g_return_val_if_fail (FINANCE_IS_SUMMARY_CHILD (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_payment));
}

/**
 * finance_summary_child_set_payment:
 * @self: a #FinanceSummaryChild
 * @payment: a #FinancePayment
 *
 * Sets the payment method of the transaction
 *
 * Since: 1.0
 */
void
finance_summary_child_set_payment (FinanceSummaryChild *self,
                                   const gchar         *payment)
{
  g_return_if_fail (FINANCE_IS_SUMMARY_CHILD (self));

  gtk_label_set_text (GTK_LABEL (self->label_payment), payment);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYMENT]);
}

/**
 * finance_summary_child_get_repeat:
 * @self: a #FinanceSummaryChild
 *
 * Returns the transaction repeat type
 *
 * Returns: The transaction repeat type as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_summary_child_get_repeat (FinanceSummaryChild *self)
{
  g_return_val_if_fail (FINANCE_IS_SUMMARY_CHILD (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_repeat));
}

/**
 * finance_summary_child_set_repeat:
 * @self: a #FinanceSummaryChild
 * @repeat: a repeat type to set, as a string
 *
 * Sets the transaction repeat type, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_summary_child_set_repeat (FinanceSummaryChild *self,
                                  const gchar         *repeat)
{
  g_return_if_fail (FINANCE_IS_SUMMARY_CHILD (self));

  gtk_label_set_text (GTK_LABEL (self->label_repeat), repeat);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_REPEAT]);
}

/**
 * finance_summary_child_get_selected:
 * @self: a #FinanceSummaryChild
 *
 * Returns whether the child is in its “selected” or “unselected” state
 *
 * Returns: #TRUE if the child is selected, and #FALSE otherwise
 *
 * Since: 1.0
 */
gboolean
finance_summary_child_get_selected (FinanceSummaryChild *self)
{
  g_return_val_if_fail (FINANCE_IS_SUMMARY_CHILD (self), FALSE);

  return gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self->check_button));
}

/**
 * finance_summary_child_set_selected:
 * @self: a #FinanceSummaryChild
 * @selected: #TRUE if row is to be selected, and #FALSE otherwise
 *
 * Sets whether the child is in its “selected” or “unselected” state
 *
 * Since: 1.0
 */
void
finance_summary_child_set_selected (FinanceSummaryChild *self,
                                    gboolean             selected)
{
  g_return_if_fail (FINANCE_IS_SUMMARY_CHILD (self));

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->check_button), selected);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_SELECTED]);
}
