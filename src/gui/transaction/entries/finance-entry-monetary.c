/* finance-entry-monetary.c
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

#include "finance-entry-monetary.h"

struct _FinanceEntryMonetary
{
  GtkEntry    parent_class;

  gdouble     amount;
  gint        decimal_value;

  gboolean    formatting;
  gboolean    currency_symbol;

  FinanceSymbol symbol;
};

G_DEFINE_TYPE (FinanceEntryMonetary, finance_entry_monetary, GTK_TYPE_ENTRY)

enum {
  PROP_0,
  PROP_AMOUNT,
  PROP_CURRENCY_SYMBOL,
  PROP_DECIMAL_PLACES,
  PROP_FORMATTING,
  PROP_SYMBOL,
  N_PROPS,
};

static GParamSpec *properties[N_PROPS] = { NULL, };

static void
filter_string (FinanceEntryMonetary *self)
{
  GString     *aux;
  const gchar *p;

  aux = g_string_new (NULL);

  p = g_strdup (gtk_entry_get_text (GTK_ENTRY (self)));

  for (; *p != 0x00; p = g_utf8_next_char (p))
      if (g_unichar_isdigit (g_utf8_get_char (p)))
        g_string_append_unichar (aux, g_utf8_get_char (p));

  aux = g_string_insert_c (aux, (aux->len - self->decimal_value), '.');

  aux = g_string_append_c (aux, 0x00);

  self->amount = g_strtod (aux->str, NULL);

  g_string_free (aux, TRUE);
}

static void
on_monetary_automatic_formatting (GtkEditable *editable,
                                  const gchar *text,
                                  gint        length,
                                  gint        *position,
                                  gpointer    user_data)
{
  FinanceEntryMonetary *self = FINANCE_ENTRY_MONETARY (user_data);

  gunichar aux_num = g_utf8_get_char (text);

  if (g_unichar_type (aux_num) == G_UNICODE_DECIMAL_NUMBER)
    {
      g_signal_handlers_block_by_func (editable,
                                       (gpointer) on_monetary_automatic_formatting,
                                       user_data);

      gtk_editable_insert_text (editable,
                                text,
                                length,
                                position);

      if (gtk_entry_get_text_length (GTK_ENTRY (user_data)) > self->decimal_value)
        {
          gchar       format[7];
          gchar       money[40];

          filter_string (self);

          g_snprintf (format, 7, "%%!.%dn", self->decimal_value);
          strfmon (money, 40, format, self->amount);

          gtk_entry_set_text (GTK_ENTRY (user_data), "");

          gtk_editable_insert_text (editable,
                                    money,
                                    strlen (money),
                                    position);
        }

      g_signal_handlers_unblock_by_func (editable,
                                         (gpointer) on_monetary_automatic_formatting,
                                         user_data);
    }

  g_signal_stop_emission_by_name (editable, "insert_text");

}

static void
on_monetary_formatting (FinanceEntryMonetary *self)
{
  gchar money[40];
  gchar format[7];

  if (!gtk_entry_get_text_length (GTK_ENTRY (self)))
    return;

  if (self->currency_symbol)
    {
      if (self->symbol == FINANCE_LOCAL)
        {
          g_snprintf (format, 7, "%%.%dn", self->decimal_value);
          strfmon (money, 40, format, self->amount);
        }
      else
        {
          g_snprintf (format, 7, "%%.%di", self->decimal_value);
          strfmon (money, 40, format, self->amount);
        }
    }
  else
    {
      g_snprintf (format, 7, "%%!.%dn", self->decimal_value);
      strfmon (money, 40, format, self->amount);
    }

  g_signal_handlers_block_by_func (self,
                                   (gpointer) on_monetary_automatic_formatting,
                                   self);

  gtk_entry_set_text (GTK_ENTRY (self), money);

  g_signal_handlers_unblock_by_func (self,
                                     (gpointer) on_monetary_automatic_formatting,
                                     self);
}

GtkWidget *
finance_entry_monetary_new (void)
{
  return g_object_new (FINANCE_TYPE_ENTRY_MONETARY, NULL);
}

static gboolean
finance_entry_monetary_focus_in_event (GtkWidget      *widget,
                                       GdkEventFocus  *event)
{
  FinanceEntryMonetary *self = FINANCE_ENTRY_MONETARY (widget);

  gchar *value;

  gtk_entry_set_alignment (GTK_ENTRY (self), 1);

  if (self->formatting && self->amount == 0.0)
    {

      switch (self->decimal_value)
        {
        case 3:
          gtk_entry_set_text (GTK_ENTRY (self), "0.000");
          break;

        case 2:
          gtk_entry_set_text (GTK_ENTRY (self), "0.00");
          break;

        case 1:
          gtk_entry_set_text (GTK_ENTRY (self), "0.0");
          break;

        default:
          gtk_entry_set_text (GTK_ENTRY (self), "");
          break;
        }

    }
  else
    {
      if (self->amount != 0.0)
        {
          value = g_strdup_printf ("%.*f",
                                   self->decimal_value,
                                   self->amount);

          gtk_entry_set_text (GTK_ENTRY (self), value);

          g_free (value);
        }
    }

  return GTK_WIDGET_CLASS (finance_entry_monetary_parent_class)->focus_in_event (widget, event);
}

static gboolean
finance_entry_monetary_focus_out_event (GtkWidget     *widget,
                                        GdkEventFocus *event)
{
  FinanceEntryMonetary *self = FINANCE_ENTRY_MONETARY (widget);

  gtk_entry_set_alignment (GTK_ENTRY (self), 0);

  if (gtk_entry_get_text_length (GTK_ENTRY (self)))
    {
      if (!self->formatting)
        self->amount = g_strtod (gtk_entry_get_text (GTK_ENTRY (self)), NULL);
      else
        filter_string (self);

      if (self->amount != 0.0)
        on_monetary_formatting (self);
      else
        gtk_entry_set_text (GTK_ENTRY (self), "");

    }
  else
    {
      self->amount = 0.0;
    }

  return GTK_WIDGET_CLASS (finance_entry_monetary_parent_class)->focus_out_event (widget, event);
}

static void
finance_entry_monetary_get_property (GObject    *object,
                                     guint      prop_id,
                                     GValue     *value,
                                     GParamSpec *pspec)
{
  FinanceEntryMonetary *self = FINANCE_ENTRY_MONETARY (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      g_value_set_double (value, finance_entry_monetary_get_amount (self));
      break;

    case PROP_CURRENCY_SYMBOL:
      g_value_set_boolean (value, finance_entry_monetary_get_currency_symbol (self));
      break;

    case PROP_DECIMAL_PLACES:
      g_value_set_int (value, finance_entry_monetary_get_decimal_places (self));
      break;

    case PROP_FORMATTING:
      g_value_set_boolean (value, finance_entry_monetary_get_formatting (self));
      break;

    case PROP_SYMBOL:
      g_value_set_enum (value, finance_entry_monetary_get_symbol (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_entry_monetary_set_property (GObject      *object,
                                     guint        prop_id,
                                     const GValue *value,
                                     GParamSpec   *pspec)
{
  FinanceEntryMonetary *self = FINANCE_ENTRY_MONETARY (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      finance_entry_monetary_set_amount (self, g_value_get_double (value));
      break;

    case PROP_CURRENCY_SYMBOL:
      finance_entry_monetary_set_currency_symbol (self, g_value_get_boolean (value));
      break;

    case PROP_DECIMAL_PLACES:
      finance_entry_monetary_set_decimal_places (self, g_value_get_int (value));
      break;

    case PROP_FORMATTING:
      finance_entry_monetary_set_formatting (self, g_value_get_boolean (value));
      break;

    case PROP_SYMBOL:
      finance_entry_monetary_set_symbol (self, g_value_get_enum (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_entry_monetary_class_init (FinanceEntryMonetaryClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->get_property = finance_entry_monetary_get_property;
  object_class->set_property = finance_entry_monetary_set_property;

  widget_class->focus_in_event  = finance_entry_monetary_focus_in_event;
  widget_class->focus_out_event = finance_entry_monetary_focus_out_event;

  /**
   * FinanceEntryMonetary::amount:
   *
   * The amount value
   */
  properties[PROP_AMOUNT] = g_param_spec_double ("amount",
                                                 "The amount value",
                                                 "The amount value",
                                                 -G_MINDOUBLE,
                                                 G_MAXDOUBLE,
                                                 0.0,
                                                 G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceEntryMonetary::currency-symbol:
   *
   * Enable automatic currency symbol
   */
  properties[PROP_CURRENCY_SYMBOL] = g_param_spec_boolean ("currency-symbol",
                                                           "Enable automatic currency symbol",
                                                           "Enable automatic currency symbol",
                                                           FALSE,
                                                           G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceEntryMonetary::decimal-places:
   *
   * The number of digits to the right of a decimal point
   */
  properties[PROP_DECIMAL_PLACES] = g_param_spec_int ("decimal-places",
                                                      "Decimal places",
                                                      "The number of digits to the right of a decimal point",
                                                      G_MININT,
                                                      G_MAXINT,
                                                      1,
                                                      G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceEntryMonetary::formatting:
   *
   * Enable automatic monetary formatting
   */
  properties[PROP_FORMATTING] = g_param_spec_boolean ("formatting",
                                                      "Enable automatic monetary formatting",
                                                      "Enable automatic monetary formatting",
                                                      TRUE,
                                                      G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);


  /**
   * FinanceEntryMonetary::symbol-type:
   *
   * Sets currency symbol is local or international
   */
  properties[PROP_SYMBOL] = g_param_spec_enum ("symbol",
                                               "Sets currency symbol is local or international",
                                               "Sets currency symbol is local or international",
                                               FINANCE_TYPE_SYMBOL,
                                               FINANCE_LOCAL,
                                               G_PARAM_WRITABLE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/transaction/entries/finance-entry-monetary.ui");

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_monetary_automatic_formatting);
}

static void
finance_entry_monetary_init (FinanceEntryMonetary *self)
{
  self->currency_symbol = FALSE;
  self->formatting      = TRUE;
  self->amount          = 0.0;
  self->decimal_value   = 1;
  self->symbol          = FINANCE_LOCAL;

  gtk_widget_init_template (GTK_WIDGET (self));
}

/**
 * finance_entr_monetary_get_amount:
 * @self: a #FinanceEntryMonetary
 *
 * Gets the amount value in #FinanceEntryMonetary.
 *
 * Returns: a #gdouble.
 *
 * Since: 1.0
 */
gdouble
finance_entry_monetary_get_amount (FinanceEntryMonetary *self)
{
  g_return_val_if_fail (FINANCE_IS_ENTRY_MONETARY (self), 0.0);

  return self->amount;
}

/**
 * finance_entry_monetary_set_amount:
 * @self: a #FinanceEntryMonetary
 * @amount: a #gdouble to set it to.
 *
 * Sets amount value in #FinanceEntryMonetary.
 *
 * Since: 1.0
 */
void
finance_entry_monetary_set_amount (FinanceEntryMonetary *self,
                                   gdouble              amount)
{
  g_return_if_fail (FINANCE_IS_ENTRY_MONETARY (self));

  self->amount = amount;

  on_monetary_formatting (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_AMOUNT]);
}

/**
 * finance_entry_manetary_get_currency_symbol:
 * @self: a #FinanceEntryMonetary
 *
 * Gets whether the currency symbol is in its “on” or “off” state.
 *
 * Returns: %TRUE if the currency symbol is active, and %FALSE otherwise.
 *
 * Since: 1.0
 */
gboolean
finance_entry_monetary_get_currency_symbol (FinanceEntryMonetary *self)
{
  g_return_val_if_fail (FINANCE_IS_ENTRY_MONETARY (self), FALSE);

  return self->currency_symbol;
}

/**
 * finance_entry_monetary_set_currency_symbol:
 * @self: a #FinanceEntryMonetary
 * @currency_symbol: %TRUE if currency symbol should be active, and %FALSE otherwise.
 *
 * Change currency symbol states. %TRUE if currency symbol should be active, and %FALSE otherwise.
 *
 * Since: 1.0
 */
void
finance_entry_monetary_set_currency_symbol (FinanceEntryMonetary  *self,
                                            gboolean              currency_symbol)
{
  g_return_if_fail (FINANCE_IS_ENTRY_MONETARY (self));

  self->currency_symbol = currency_symbol;

  on_monetary_formatting (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_CURRENCY_SYMBOL]);
}

/**
 * finance_entry_monetary_get_decimal_places:
 * @self: a #FinanceEntryMonetary
 *
 * Returns the current precision of monetary value.
 *
 * Returns: The current precision.
 *
 * Since: 1.0
 */
gint
finance_entry_monetary_get_decimal_places (FinanceEntryMonetary *self)
{
  g_return_val_if_fail (FINANCE_IS_ENTRY_MONETARY (self), FALSE);

  return self->decimal_value;
}

/**
 * finance_entry_monetary_set_decimal_places:
 * @self: a #FinanceEntryMonetary
 * @value: a #gint.
 *
 * Sets the number of digits to the right of a decimal point.
 *
 * Since: 1.0
 */
void
finance_entry_monetary_set_decimal_places (FinanceEntryMonetary *self,
                                           gint                  value)
{
  g_return_if_fail (FINANCE_IS_ENTRY_MONETARY (self));

  self->decimal_value = value;

  on_monetary_formatting (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_DECIMAL_PLACES]);
}

/**
 * finance_entry_monetary_get_formatting:
 * @self: a #FinanceEntryMonetary
 *
 * Gets whether the formatting is in its “on” or “off” state.
 *
 * Returns: %TRUE if the automatic date formatting is active, and %FALSE otherwise.
 *
 * Since: 1.0
 */
gboolean
finance_entry_monetary_get_formatting (FinanceEntryMonetary *self)
{
  g_return_val_if_fail (FINANCE_IS_ENTRY_MONETARY (self), FALSE);

  return self->formatting;
}

/**
 * finance_entry_monetary_set_formatting:
 * @self: a #FinanceEntryMonetary
 * @formatting: %TRUE if formatting should be active, and %FALSE otherwise.
 *
 * Change automatic monetary formatting states. %TRUE if formatting should be active, and %FALSE otherwise.
 *
 * Since: 1.0
 */
void
finance_entry_monetary_set_formatting (FinanceEntryMonetary *self,
                                       gboolean             formatting)
{
  g_return_if_fail (FINANCE_IS_ENTRY_MONETARY (self));

  if (self->formatting == formatting)
    return;

  self->formatting = formatting;

  if (self->formatting)
    g_signal_handlers_unblock_by_func (self, on_monetary_automatic_formatting, self);
  else
    g_signal_handlers_block_by_func (self, on_monetary_automatic_formatting, self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FORMATTING]);
}

/**
 * finance_entry_monetary_get_symbol:
 * @self: a #FinanceEntryMonetary
 *
 * Returns the type of currency symbol in use.
 *
 * Returns: a #FinanceSymbol.
 *
 * Since: 1.0
 */
gint
finance_entry_monetary_get_symbol (FinanceEntryMonetary *self)
{
  g_return_val_if_fail (FINANCE_IS_ENTRY_MONETARY (self), -1);

  return self->symbol;
}

/**
 * finance_entry_monetary_set_symbol:
 * @self: a #FinanceEntryMonetary
 * @symbol: a #FinanceSymbol.
 *
 * Sets currency symbol is local or international.
 *
 * Since: 1.0
 */
void
finance_entry_monetary_set_symbol (FinanceEntryMonetary *self,
                                   gint         symbol)
{
  g_return_if_fail (FINANCE_IS_ENTRY_MONETARY (self));

  self->symbol = symbol;

  on_monetary_formatting (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_SYMBOL]);
}
