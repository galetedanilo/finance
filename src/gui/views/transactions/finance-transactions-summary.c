/* finance-transactions-summary.c
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

#include "finance-transactions-summary.h"

#include "finance-enums.h"

struct _FinanceTransactionsSummary
{
  GtkGrid   parent_instance;

  /* The widgets */
  GtkWidget *check_button;
  GtkWidget *image_icon;
  GtkWidget *label_amount;
  GtkWidget *label_category;
  GtkWidget *label_date;
  GtkWidget *label_payee_name;
  GtkWidget *label_payment;
  GtkWidget *label_repeat;
  GtkWidget *label_title;

  gchar     *icon_name;

  FinanceTransaction transaction;
};

G_DEFINE_TYPE (FinanceTransactionsSummary, finance_transactions_summary, GTK_TYPE_GRID)

enum {
  PROP_0,
  PROP_AMOUNT,
  PROP_CATEGORY,
  PROP_DATE,
  PROP_ICON_NAME,
  PROP_PAYEE_NAME,
  PROP_PAYMENT,
  PROP_REPEAT,
  PROP_SELECTED,
  PROP_TITLE,
  PROP_TRANSACTION,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static void
on_check_button_toggled (GtkToggleButton *togglebutton,
                         gpointer         user_data)
{
  FinanceTransactionsSummary *self = FINANCE_TRANSACTIONS_SUMMARY (user_data);

  (void)togglebutton;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_SELECTED]);
}

GtkWidget *
finance_transactions_summary_new (void)
{
  return g_object_new (FINANCE_TYPE_TRANSACTIONS_SUMMARY, NULL);
}

static void
finance_transactions_summary_finalize (GObject *object)
{
  FinanceTransactionsSummary *self = (FinanceTransactionsSummary *)object;

  g_clear_pointer (&self->icon_name, g_free);

  G_OBJECT_CLASS (finance_transactions_summary_parent_class)->finalize (object);
}

static void
finance_transactions_summary_get_property (GObject    *object,
                                           guint       prop_id,
                                           GValue     *value,
                                           GParamSpec *pspec)
{
  FinanceTransactionsSummary *self = FINANCE_TRANSACTIONS_SUMMARY (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      g_value_set_string (value, finance_transactions_summary_get_amount (self));
      break;

    case PROP_CATEGORY:
      g_value_set_string (value, finance_transactions_summary_get_category (self));
      break;

    case PROP_DATE:
      g_value_set_string (value, finance_transactions_summary_get_date (self));
      break;

    case PROP_ICON_NAME:
      g_value_set_string (value, finance_transactions_summary_get_icon_name (self));
      break;

    case PROP_PAYEE_NAME:
      g_value_set_string (value, finance_transactions_summary_get_payee_name (self));
      break;

    case PROP_PAYMENT:
      g_value_set_string (value, finance_transactions_summary_get_payment (self));
      break;

    case PROP_REPEAT:
      g_value_set_string (value, finance_transactions_summary_get_repeat (self));
      break;

    case PROP_SELECTED:
      g_value_set_boolean (value, finance_transactions_summary_get_selected (self));
      break;

    case PROP_TITLE:
      g_value_set_string (value, finance_transactions_summary_get_title (self));
      break;

    case PROP_TRANSACTION:
      g_value_set_enum (value, finance_transactions_summary_get_transaction (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_transactions_summary_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec)
{
  FinanceTransactionsSummary *self = FINANCE_TRANSACTIONS_SUMMARY (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      finance_transactions_summary_set_amount (self, g_value_get_string (value));
      break;

    case PROP_CATEGORY:
      finance_transactions_summary_set_category (self, g_value_get_string (value));
      break;

    case PROP_DATE:
      finance_transactions_summary_set_date (self, g_value_get_string (value));
      break;

    case PROP_ICON_NAME:
      finance_transactions_summary_set_icon_name (self, g_value_get_string (value));
      break;

    case PROP_PAYEE_NAME:
      finance_transactions_summary_set_payee_name (self, g_value_get_string (value));
      break;

    case PROP_PAYMENT:
      finance_transactions_summary_set_payment (self, g_value_get_string (value));
      break;

    case PROP_REPEAT:
      finance_transactions_summary_set_repeat (self, g_value_get_string (value));
      break;

    case PROP_SELECTED:
      finance_transactions_summary_set_selected (self, g_value_get_boolean (value));
      break;

    case PROP_TITLE:
      finance_transactions_summary_set_title (self, g_value_get_string (value));
      break;

    case PROP_TRANSACTION:
      finance_transactions_summary_set_transaction (self, g_value_get_enum (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_transactions_summary_class_init (FinanceTransactionsSummaryClass *klass)
{
  GObjectClass   *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize      = finance_transactions_summary_finalize;
  object_class->get_property  = finance_transactions_summary_get_property;
  object_class->set_property  = finance_transactions_summary_set_property;

  /**
   * FinanceTransactionsSummary::amount:
   *
   * The transaction amount as a string
   */
  properties[PROP_AMOUNT] =  g_param_spec_string ("amount",
                                                  "Amount",
                                                  "The transaction amount",
                                                  NULL,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionsSummary::category:
   *
   * The transaction category
   */
  properties[PROP_CATEGORY] = g_param_spec_string ("category",
                                                   "Category",
                                                   "The transaction category",
                                                   NULL,
                                                   G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionsSummary::date:
   *
   * The transaction date
   */
  properties[PROP_DATE] = g_param_spec_string ("date",
                                               "Date",
                                               "The transaction date",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionsSummary::icon-name:
   *
   * The name of the icon in the image
   */
  properties[PROP_ICON_NAME] = g_param_spec_string ("icon-name",
                                                    "Icon name",
                                                    "The name of the icon in the image",
                                                    NULL,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionsSummary::payee_name:
   *
   * The transaction payee name
   */
  properties[PROP_PAYEE_NAME] = g_param_spec_string ("payee-name",
                                                     "Payee name",
                                                     "The transaction payee name",
                                                     NULL,
                                                     G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionsSummary::payment:
   *
   * The payment method of the transaction
   */
  properties[PROP_PAYMENT] = g_param_spec_string ("payment",
                                                  "Payment",
                                                  "The payment method of the transaction",
                                                  NULL,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionsSummary::repeat:
   *
   * The transaction repeat type
   */
  properties[PROP_REPEAT] = g_param_spec_string ("repeat",
                                                 "Repeat",
                                                 "The transaction repeat type",
                                                 NULL,
                                                 G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

    /**
   * FinanceTransactionsSummary::selected:
   *
   * The summary child is selected
   */
  properties[PROP_SELECTED] = g_param_spec_boolean ("selected",
                                                    "Select",
                                                    "The summary child is selected",
                                                    FALSE,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionsSummary::title:
   *
   * The transaction title
   */
  properties[PROP_TITLE] = g_param_spec_string ("title",
                                                "title",
                                                "The transaction title",
                                                NULL,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionsSummary::transaction:
   *
   * The transaction transaction
   */
  properties[PROP_TRANSACTION] = g_param_spec_enum ("transaction",
                                                    "The transaction",
                                                    "The transaction type",
                                                    FINANCE_TYPE_TRANSACTION,
                                                    FINANCE_CREDIT,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/views/transactions/finance-transactions-summary.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionsSummary, check_button);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionsSummary, image_icon);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionsSummary, label_amount);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionsSummary, label_category);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionsSummary, label_date);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionsSummary, label_payee_name);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionsSummary, label_payment);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionsSummary, label_repeat);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionsSummary, label_title);

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_check_button_toggled);
}

static void
finance_transactions_summary_init (FinanceTransactionsSummary *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

/**
 * finance_transactions_summary_get_amount:
 * @self: a #FinanceTransactionsSummary
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
finance_transactions_summary_get_amount (FinanceTransactionsSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_amount));
}

/**
 * finance_transactions_summary_set_amount_string:
 * @self: a #FinanceTransactionsSummary
 * @amount: a amount to set, as a string
 *
 * Sets transaction amount
 *
 * Since: 1.0
 */
void
finance_transactions_summary_set_amount (FinanceTransactionsSummary *self,
                                         const gchar                *amount)
{
  g_return_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self));
  g_return_if_fail (amount == NULL);

  gtk_label_set_text (GTK_LABEL (self->label_amount), amount);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_AMOUNT]);
}

/**
 * finance_transactions_summary_get_category:
 * @self: a #FinanceTransactionsSummary
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
finance_transactions_summary_get_category (FinanceTransactionsSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_category));
}

/**
 * finance_transactions_summary_set_category:
 * @self: a #FinanceTransactionsSummary
 * @category: a category to set, as a string
 *
 * Sets the category method of the transaction
 *
 * Since: 1.0
 */
void
finance_transactions_summary_set_category (FinanceTransactionsSummary *self,
                                           const gchar                *category)
{
  g_return_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self));
  g_return_if_fail (category == NULL);

  gtk_label_set_text (GTK_LABEL (self->label_category), category);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_CATEGORY]);
}

/**
 * finance_transactions_summary_get_date:
 * @self: a #FinanceTransactionsSummary
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
finance_transactions_summary_get_date (FinanceTransactionsSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_date));
}

/**
 * finance_transactions_summary_set_date:
 * @self: a #FinanceTransactionsSummary
 * @date: a valid date, as a string
 *
 * Sets the date of the financial transaction
 *
 * Since: 1.0
 */
void
finance_transactions_summary_set_date (FinanceTransactionsSummary *self,
                                       const gchar                *date)
{
  g_return_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self));
  g_return_if_fail (date == NULL);

  gtk_label_set_text (GTK_LABEL (self->label_date), date);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_DATE]);
}

/**
 * finance_transactions_summary_get_icon_name:
 * @self: a #FinanceTransactionsSummary
 *
 * Returns the name of the icon in the image
 *
 * Returns: The name of the icon in the image as a string , or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transactions_summary_get_icon_name (FinanceTransactionsSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self), NULL);

  return self->icon_name;
}

/**
 * finance_transactions_summary_set_icon_name:
 * @self: a #FinanceTransactionsSummary
 * @icon_name: the name of the icon in the image
 *
 * Sets the name of the icon in the image,
 * replacing the current contents.
 *
 * Since:1.0
 */
void
finance_transactions_summary_set_icon_name (FinanceTransactionsSummary *self,
                                            const gchar                *icon_name)
{
  g_return_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self));
  g_return_if_fail (icon_name == NULL);

  g_clear_pointer (&self->icon_name, g_free);

  self->icon_name = g_strdup (icon_name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON_NAME]);
}

/**
 * finance_transactions_summary_get_payee_name:
 * @self: a #FinanceTransactionsSummary
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
finance_transactions_summary_get_payee_name (FinanceTransactionsSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_payee_name));
}

/**
 * finance_transactions_summary_set_payee_name:
 * @self: a #FinanceTransactionsSummary
 * @payee_name: a payee name to set, as a string
 *
 * Sets the transaction payee name, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_transactions_summary_set_payee_name (FinanceTransactionsSummary *self,
                                             const gchar                *payee_name)
{
  g_return_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self));
  g_return_if_fail (payee_name == NULL);

  gtk_label_set_text (GTK_LABEL (self->label_payee_name), payee_name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYEE_NAME]);
}

/**
 * finance_transactions_summary_get_payment:
 * @self: a #FinanceTransactionsSummary
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
finance_transactions_summary_get_payment (FinanceTransactionsSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_payment));
}

/**
 * finance_transactions_summary_set_payment:
 * @self: a #FinanceTransactionsSummary
 * @payment: a #FinancePayment
 *
 * Sets the payment method of the transaction
 *
 * Since: 1.0
 */
void
finance_transactions_summary_set_payment (FinanceTransactionsSummary *self,
                                   const gchar         *payment)
{
  g_return_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self));
  g_return_if_fail (payment == NULL);

  gtk_label_set_text (GTK_LABEL (self->label_payment), payment);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYMENT]);
}

/**
 * finance_transactions_summary_get_repeat:
 * @self: a #FinanceTransactionsSummary
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
finance_transactions_summary_get_repeat (FinanceTransactionsSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_repeat));
}

/**
 * finance_transactions_summary_set_repeat:
 * @self: a #FinanceTransactionsSummary
 * @repeat: a repeat type to set, as a string
 *
 * Sets the transaction repeat type, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_transactions_summary_set_repeat (FinanceTransactionsSummary *self,
                                  const gchar         *repeat)
{
  g_return_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self));
  g_return_if_fail (repeat == NULL);

  gtk_label_set_text (GTK_LABEL (self->label_repeat), repeat);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_REPEAT]);
}

/**
 * finance_transactions_summary_get_selected:
 * @self: a #FinanceTransactionsSummary
 *
 * Returns whether the child is in its “selected” or “unselected” state
 *
 * Returns: #TRUE if the child is selected, and #FALSE otherwise
 *
 * Since: 1.0
 */
gboolean
finance_transactions_summary_get_selected (FinanceTransactionsSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self), FALSE);

  return gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self->check_button));
}

/**
 * finance_transactions_summary_set_selected:
 * @self: a #FinanceTransactionsSummary
 * @selected: #TRUE if row is to be selected, and #FALSE otherwise
 *
 * Sets whether the child is in its “selected” or “unselected” state
 *
 * Since: 1.0
 */
void
finance_transactions_summary_set_selected (FinanceTransactionsSummary *self,
                                    gboolean             selected)
{
  g_return_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self));

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->check_button), selected);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_SELECTED]);
}

/**
 * finance_transactions_summary_get_title:
 * @self: a #FinanceTransactionsSummary
 *
 * Returns the transaction title
 *
 * Returns: The transaction title as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transactions_summary_get_title (FinanceTransactionsSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->label_title));
}

/**
 * finance_transactions_summary_set_title:
 * @self: a #FinanceTransactionsSummary
 * @title: the title to set, as a string
 *
 * Sets the transaction title, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_transactions_summary_set_title (FinanceTransactionsSummary *self,
                                        const gchar                *title)
{
  g_return_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self));
  g_return_if_fail (title == NULL);

  gtk_label_set_text (GTK_LABEL (self->label_title), title);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TITLE]);
}

/**
 * finance_transactions_summary_get_transaction:
 * @self: a #FinanceTransactionsSummary
 *
 * Returns the transaction type
 *
 * Returns: a #FinanceTransaction
 *
 * Since: 1.0
 */
gint
finance_transactions_summary_get_transaction (FinanceTransactionsSummary *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self), -1);

  return self->transaction;
}

/**
 * finance_transactions_summary_set_transaction:
 * @self: a #FinanceTransactionsSummary
 * @transaction: a #FinanceTransaction
 *
 * Sets the transaction type
 *
 * Since: 1.0
 */
void
finance_transactions_summary_set_transaction (FinanceTransactionsSummary *self,
                                       gint                 transaction)
{
  g_return_if_fail (FINANCE_IS_TRANSACTIONS_SUMMARY (self));

  self->transaction = transaction;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TRANSACTION]);
}
