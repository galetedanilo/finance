/* finance-object-transaction.c
 *
 * Copyright 2021 Danilo Fernandes Galete <galetedanilo@gmail.com>
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

#include "finance-object-transaction.h"

#include "finance-enums.h"

struct _FinanceObjectTransaction
{
  GObject           parent_instance;

  gint              frequency_number;

  gdouble           amount;

  gchar             *category;
  gchar             *icon;
  gchar             *name;
  gchar             *notes;
  gchar             *payee_name;
  gchar             *payment_information;

  GDateTime         *date;
  GDateTime         *frequency_date;

  GdkRGBA           *color;

  FinanceFrequency  frequency;

  FinancePayment    payment;

  FinanceRepeat     repeat;

  FinanceTransaction  type;
};

G_DEFINE_TYPE (FinanceObjectTransaction, finance_object_transaction, G_TYPE_OBJECT)

enum {
  PROP_0,
  PROP_AMOUNT,
  PROP_CATEGORY,
  PROP_COLOR,
  PROP_DATE,
  PROP_FREQUENCY,
  PROP_FREQUENCY_DATE,
  PROP_FREQUENCY_NUMBER,
  PROP_ICON,
  PROP_NAME,
  PROP_NOTES,
  PROP_PAYEE_NAME,
  PROP_PAYMENT,
  PROP_PAYMENT_INFORMATION,
  PROP_REPEAT,
  PROP_TRANSACTION_TYPE,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

FinanceObjectTransaction *
finance_object_transaction_new (void)
{
  return g_object_new (FINANCE_TYPE_OBJECT_TRANSACTION, NULL);
}

static void
finance_object_transaction_finalize (GObject *object)
{
  FinanceObjectTransaction *self = (FinanceObjectTransaction *)object;

  g_clear_pointer (&self->category, g_free);
  g_clear_pointer (&self->icon, g_free);
  g_clear_pointer (&self->name, g_free);
  g_clear_pointer (&self->notes, g_free);
  g_clear_pointer (&self->payee_name, g_free);
  g_clear_pointer (&self->payment_information, g_free);

  G_OBJECT_CLASS (finance_object_transaction_parent_class)->finalize (object);
}

static void
finance_object_transaction_dispose (GObject *object)
{
  FinanceObjectTransaction *self = (FinanceObjectTransaction *)object;

  g_clear_pointer (&self->date, g_date_time_unref);
  g_clear_pointer (&self->frequecy_date, g_date_time_unref);
  g_clear_pointer (&self->color, gdk_rgba_free);

  G_OBJECT_CLASS (finance_object_transaction_parent_class)->dispose (object);
}

static void
finance_object_transaction_get_property (GObject    *object,
                                         guint       prop_id,
                                         GValue     *value,
                                         GParamSpec *pspec)
{
  FinanceObjectTransaction *self = FINANCE_OBJECT_TRANSACTION (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      g_value_set_double (value, finance_object_transaction_get_amount (self));
      break;

    case PROP_CATEGORY:
      g_value_set_string (value, finance_object_transaction_get_category (self));
      break;

    case PROP_COLOR:
      g_value_set_boxed (value, finance_object_transaction_get_color (self));
      break;

    case PROP_DATE:
      g_value_set_boxed (value, finance_object_transaction_get_date (self));
      break;

    case PROP_FREQUENCY:
      g_value_set_enum (value, finance_object_transaction_get_frequency (self));
      break;

    case PROP_FREQUENCY_DATE:
      g_value_set_boxed (value,finance_object_transaction_get_frequency_date (self));
      break;

    case PROP_FREQUENCY_NUMBER:
      g_value_set_int (value, finance_object_transaction_get_frequency_number (self));
      break;

    case PROP_ICON:
      g_value_set_string (value, finance_object_transaction_get_icon (self));
      break;

    case PROP_NAME:
      g_value_set_string (value, finance_object_transaction_get_name (self));
      break;

    case PROP_NOTES:
      g_value_set_string (value, finance_object_transaction_get_notes (self));
      break;

    case PROP_PAYEE_NAME:
      g_value_set_string (value, finance_object_transaction_get_payee_name (self));
      break;

    case PROP_PAYMENT:
      g_value_set_enum (value, finance_object_transaction_get_payment (self));
      break;

    case PROP_PAYMENT_INFORMATION:
      g_value_set_string (value, finance_object_transaction_get_payment_information (self));
      break;

    case PROP_REPEAT:
      g_value_set_enum (value, finance_object_transaction_get_repeat (self));
      break;

    case PROP_TRANSACTION_TYPE:
      g_value_set_enum (value, finance_object_transaction_get_type (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_object_transaction_set_property (GObject      *object,
                                         guint         prop_id,
                                         const GValue *value,
                                         GParamSpec   *pspec)
{
  FinanceObjectTransaction *self = FINANCE_OBJECT_TRANSACTION (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      finance_object_transaction_set_amount (self, g_value_get_double (value));
      break;

    case PROP_CATEGORY:
      finance_object_transaction_set_category (self, g_value_get_string (value));
      break;

    case PROP_COLOR:
      finance_object_transaction_set_color (self, g_value_get_boxed (value));
      break;

    case PROP_DATE:
      finance_object_transaction_set_date (self, g_value_get_boxed (value));
      break;

    case PROP_FREQUENCY:
      finance_object_transaction_set_frequency (self, g_value_get_enum (value));
      break;

    case PROP_FREQUENCY_DATE:
      finance_object_transaction_set_frequency_date (self, g_value_get_boxed (value));
      break;

    case PROP_FREQUENCY_NUMBER:
      finance_object_transaction_set_frequency_number (self, g_value_get_int (value));
      break;

    case PROP_ICON:
      finance_object_transaction_set_icon (self, g_value_get_string (value));
      break;

    case PROP_NAME:
      finance_object_transaction_set_name (self, g_value_get_string (value));
      break;

    case PROP_NOTES:
      finance_object_transaction_set_notes (self, g_value_get_string (value));
      break;

    case PROP_PAYEE_NAME:
      finance_object_transaction_set_payee_name (self, g_value_get_string (value));
      break;

    case PROP_PAYMENT:
      finance_object_transaction_set_payment (self, g_value_get_enum (value));
      break;

    case PROP_PAYMENT_INFORMATION:
      finance_object_transaction_set_payment_info (self, g_value_get_string (value));
      break;

    case PROP_REPEAT:
      finance_object_transaction_set_repeat (self, g_value_get_enum (value));
      break;

    case PROP_TRANSACTION_TYPE:
      finance_object_transaction_set_transaction_type (self, g_value_get_enum ());
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_object_transaction_class_init (FinanceObjectTransactionClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize      = finance_object_transaction_finalize;
  object_class->dispose       = finance_object_transaction_dispose;
  object_class->get_property  = finance_object_transaction_get_property;
  object_class->set_property  = finance_object_transaction_set_property;

  /**
   * FinanceObjectTransaction::amount:
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
   * FinanceObjectTransaction::color:
   *
   * The background color of the icon
   */
  properties[PROP_COLOR] = g_param_spec_boxed ("color",
                                               "Color",
                                               "The background color of the icon",
                                               GDK_TYPE_RGBA,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceObjectTransaction::date:
   *
   * The transaction date
   */
  properties[PROP_DATE] = g_param_spec_boxed ("date",
                                              "Date",
                                              "The transaction date",
                                              G_TYPE_DATE_TIME,
                                              G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceObjectTransaction::frequency:
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
   * FinanceObjectTransaction::frequency_date:
   *
   * The date of the financial transaction frequency
   */
  properties[PROP_FREQUENCY_DATE] = g_param_spec_boxed ("frequency-date",
                                                        "Fequency date",
                                                        "The date of the financial transaction frequency",
                                                        G_TYPE_DATE_TIME,
                                                        G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceObjectTransaction::frequency_number:
   *
   * The number of frequency of transactions
   */
  properties[PROP_FREQUENCY_NUMBER] = g_param_spec_int ("frequency-number",
                                                        "Frequency Number",
                                                        "The number of frequency of transactions",
                                                        2, 365, 2,
                                                        G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);


  /**
   * FinanceObjectTransaction::icon:
   *
   * The two letters that are part of the icon image
   */
  properties[PROP_ICON] = g_param_spec_string ("icon",
                                               "Icon",
                                               "The two letters that are part of the icon image",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceObjectTransaction::name:
   *
   * The transaction name
   */
  properties[PROP_NAME] = g_param_spec_string ("name",
                                               "Name",
                                               "The transaction name",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceObjectTransaction::notes:
   *
   * The transaction notes information
   */
  properties[PROP_NOTES] = g_param_spec_string ("notes",
                                                "Notes",
                                                "The transaction notes information",
                                                NULL,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceObjectTransaction::payee_name:
   *
   * The transaction payee name
   */
  properties[PROP_PAYEE_NAME] = g_param_spec_string ("payee-name",
                                                     "Payee name",
                                                     "The transaction payee name",
                                                     NULL,
                                                     G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceObjectTransaction::payment:
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
   * FinanceObjectTransaction::payment_information:
   *
   * The transaction payment information
   */
  properties[PROP_PAYMENT_INFORMATION] = g_param_spec_string ("payment-information",
                                                              "Payment information",
                                                              "The transaction payment information",
                                                              NULL,
                                                              G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceObjectTransaction::repeat:
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
   * FinanceObjectTransaction::transaction_type:
   *
   * The transaction type
   */
  properties[PROP_TRANSACTION_TYPE] = g_param_spec_enum ("transaction-type",
                                                         "Transaction type",
                                                         "The transaction type",
                                                         FINANCE_TYPE_TRANSACTION,
                                                         NULL,
                                                         G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
finance_object_transaction_init (FinanceObjectTransaction *self)
{
}

/**
 * finance_object_transaction_get_amount:
 * @self: a #FinanceObjectTransaction
 *
 * Gets the object transaction amount
 *
 * Returns: a #gdouble
 *
 * Since: 1.0
 */
gdouble
finance_object_transaction_get_amount (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), 0.0);

  return self->amount;
}

/**
 * finance_object_transaction_set_amount:
 * @self: a #FinanceObjectTransaction
 * @amount: a #gdouble to set it to
 *
 * Sets object transaction amount
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_amount (FinanceObjectTransaction *self,
                                       gdouble                   amount)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  if (amount < 1)
    return;

  self->amount = amount;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_AMOUNT]);
}

/**
 * finance_object_transaction_get_category:
 * @self: a #FinanceObjectTransaction
 *
 * Returns the transaction category name
 *
 * Returns: The transaction category name as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored
 *
 * Since: 1.0
 */
const gchar *
finance_object_transaction_get_category (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), NULL);

  return self->category;
}

/**
 * finance_object_transaction_set_category:
 * @self: a #FinanceObjectTransaction
 * @category: the category name to set, as a string
 *
 * Sets the transaction category name, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_category (FinanceObjectTransaction *self,
                                         const gchar              *category)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  g_clear_pointer (&self->category, g_free);

  self->category = g_strdup (category);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_CATEGORY]);
}

/**
 * finance_object_transaction_get_color:
 * @self: a #FinanceObjectTransaction
 *
 * Returns the background color of the icon
 *
 * Returns: (transfer none): a #GdkRGBA with the color
 *
 * Since: 1.0
 */
GdkRGBA *
finance_object_transaction_get_color (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), NULL);

  return self->color;
}

/**
 * finance_object_transaction_set_color:
 * @self: a #FinanceObjectTransaction
 * @color: a #GdkRGBA
 *
 * Sets the background color of the icon
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_color (FinanceObjectTransaction *self,
                                      const GdkRGBA            *color)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  g_clear_pointer (&self->color, gdk_rgba_free);

  self->color = gdk_rgba_copy (color);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_COLOR]);
}

/**
 * finance_object_transaction_get_date:
 * @self: a #FinanceObjectTransaction
 *
 * Returns the date of the financial transaction
 *
 * Returns: (transfer none): a #GDateTime
 *
 * Since: 1.0
 */
GDateTime *
finance_object_transaction_get_date (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), NULL);

  return self->date;
}

/**
 * finance_object_transaction_set_date:
 * @self: a #FinanceObjectTransaction
 * @date: a valid date, as a #GDateTime
 *
 * Sets the date of the financial transaction
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_date (FinanceObjectTransaction *self,
                                     GDateTime                *date)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  g_clear_pointer (&self->date, g_date_time_unref);

  self->date = g_date_time_new_local (g_date_time_get_year (date),
                                      g_date_time_get_month (date),
                                      g_date_time_get_day_of_month (date),
                                      0, 0, 0);


  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_DATE]);
}

/**
 * finance_object_transaction_get_frequency:
 * @self: a #FinanceObjectTransaction
 *
 * Returns the transaction frequency
 *
 * Returns: a #FinanceFrequency
 *
 * Since: 1.0
 */
gint
finance_object_transaction_get_frequency (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), -1);

  return self->frequency;
}

/**
 * finance_object_transaction_set_frequency:
 * @self: a #FinanceObjectTransaction
 * @frequency: a #FinanceFrequency
 *
 * Sets the transaction frequency
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_frequency (FinanceObjectTransaction *self,
                                          gint                      frequency)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  self->frequency = frequency;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FREQUENCY]);
}

/**
 * finance_object_transaction_get_frequency_date:
 * @self: a #FinanceObjectTransaction
 *
 * Returns the date of the financial transaction frequency
 *
 * Returns: (transfer none): a #GDateTime
 *
 * Since: 1.0
 */
GDateTime *
finance_object_transaction_get_frequency_date (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), NULL);

  return self->frequency_date;
}

/**
 * finance_object_transaction_set_frequency_date:
 * @self: a #FinanceObjectTransaction
 * @date: a valid date, as a #GDateTime
 *
 * Sets the date of the financial transaction frequency
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_frequency_date (FinanceObjectTransaction *self,
                                               GDateTime                *date)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  g_clear_pointer (&self->frequency_date, g_date_time_unref);

  self->frequency_date = g_date_time_new_local (g_date_time_get_year (date),
                                                g_date_time_get_month (date),
                                                g_date_time_get_day_of_month (date),
                                                0, 0, 0);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FREQUENCY_DATE]);
}

/**
 * finance_object_transaction_get_frequency_number:
 * @self: a #FinanceObjectTransaction
 *
 * Returns the number of frequency of transactions
 *
 * Returns: a #gint
 *
 * Since: 1.0
 */
gint
finance_object_transaction_get_frequency_number (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), 0);

  return self->frequency_number;
}

/**
 * finance_object_transaction_set_frequency_number:
 * @self: a #FinanceObjectTransaction
 * @frequency_number: a #gint
 *
 * Sets the number of frequency of transactions
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_frequency_number (FinanceObjectTransaction *self,
                                                 gint                      frequency_number)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  if (frequency_number < 2)
    return;

  self->frequency_number = frequency_number;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FREQUENCY_NUMBER]);
}

/**
 * finance_object_transaction_get_icon:
 * @self: a #FinanceObjectTransaction
 *
 * Returns the two letters that are part of the icon image
 *
 * Returns: A two-letter string , or %NULL
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored
 *
 * Since: 1.0
 */
const gchar *
finance_object_transaction_get_icon (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), NULL);

  return self->icon;
}

/**
 * finance_object_transaction_set_icon:
 * @self: a #FinanceObjectTransaction
 * @icon: the icon to set, as a two-letter string
 *
 * Sets the two letters that are part of the icon image,
 * replacing the current contents
 *
 * Since:1.0
 */
void
finance_object_transaction_set_icon (FinanceObjectTransaction *self,
                                     const gchar              *icon)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  if (strlen (icon) > 2)
    return;

  g_clear_pointer (&self->icon, g_free);

  self->icon = g_strdup (icon);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON]);
}

/**
 * finance_object_transaction_get_name:
 * @self: a #FinanceObjectTransaction
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
finance_object_transaction_get_name (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), NULL);

  return self->name;
}

/**
 * finance_object_transaction_set_name:
 * @self: a #FinanceTransaction
 * @name: the name to set, as a string
 *
 * Sets the transaction name, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_name (FinanceObjectTransaction *self,
                                     const gchar              *name)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  g_clear_pointer (&self->name, g_free);

  self->name = name;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_NAME]);
}

/**
 * finance_object_transaction_get_notes:
 * @self: a #FinanceObjectTransaction
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
finance_object_transaction_get_notes (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), NULL);

  return self->notes;
}

/**
 * finance_object_transaction_set_notes:
 * @self: a #FinanceObjectTransaction
 * @notes: the notes to set, as a string
 *
 * Sets the transaction notes information, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_notes (FinanceObjectTransaction *self,
                                      const gchar              *notes)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  g_clear_pointer (&self->notes, g_free);

  self->notes = g_strdup (notes);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_NOTES]);
}

/**
 * finance_object_transaction_get_payee_name:
 * @self: a #FinanceObjectTransaction
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
finance_object_transaction_get_payee_name (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), NULL);

  return self->payee_name;
}

/**
 * finance_object_transaction_set_payee_name:
 * @self: a #FinanceObjectTransaction
 * @payee_name: the payee name to set, as a string
 *
 * Sets the transaction payee name, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_payee_name (FinanceObjectTransaction *self,
                                           const gchar              *payee_name)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  g_clear_pointer (&self->payee_name, g_free);

  self->payee_name = g_strdup (payee_name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYEE_NAME]);
}

/**
 * finance_object_transaction_get_payment:
 * @self: a #FinanceObjectTransaction
 *
 * Returns the payment method of the transaction
 *
 * Returns: a #FinancePayment
 *
 * Since: 1.0
 */
gint
finance_object_transaction_get_payment (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), -1);

  return self->payment;
}

/**
 * finance_object_transaction_set_payment:
 * @self: a #FinanceObjectTransaction
 * @payment: a #FinancePayment
 *
 * Sets the payment method of the transaction
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_payment (FinanceObjectTransaction *self,
                                        gint                      payment)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  self->payment = payment;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYMENT]);
}

/**
 * finance_object_transaction_get_payment_information:
 * @self: a #FinanceObjectTransaciton
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
finance_object_transaction_get_payment_information (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), NULL);

  return self->payment_information;
}

/**
 * finance_object_transaction_set_payment_information:
 * @self: a #FinanceObjectTransaction
 * @information: the payment information to set, as a string
 *
 * Sets the transaction payment information, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_payment_information (FinanceObjectTransaction *self,
                                                    const gchar              *information)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  g_clear_pointer (&self->payment_information, g_free);

  self->payment_information = g_strdup (information);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_PAYMENT_INFORMATION]);
}

/**
 * finance_object_transaction_get_repeat:
 * @self: a #FinanceObjectTransaction
 *
 * Returns the transaction repeat type
 *
 * Returns: a #FinanceRepeat
 *
 * Since: 1.0
 */
gint
finance_object_transaction_get_repeat (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), -1);

  return self->repeat;
}

/**
 * finance_object_transaction_set_repeat:
 * @self: a #FinanceObjectTransaction
 * @repeat: a #FinanceRepeat
 *
 * Sets the transaction repeat type
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_repeat (FinanceObjectTransaction *self,
                                       gint                      repeat)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  self->repeat = repeat;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_REPEAT]);
}

/**
 * finance_object_transaction_get_type:
 * @self: a #FinanceObjectTransaction
 *
 * Returns the transaction type
 *
 * Returns: a #FinanceTransaction
 *
 * Since: 1.0
 */
gint
finance_object_transaction_get_type (FinanceObjectTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self), -1);

  return self->type;
}

/**
 * finance_object_transaction_set_type:
 * @self: a #FinanceObjectTransaction
 * @type: a #FinanceTransaction
 *
 * Sets the transaction type
 *
 * Since: 1.0
 */
void
finance_object_transaction_set_type (FinanceObjectTransaction *self,
                                     gint                      type)
{
  g_return_if_fail (FINANCE_IS_OBJECT_TRANSACTION (self));

  self->type = type;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TRANSACTION_TYPE]);
}
