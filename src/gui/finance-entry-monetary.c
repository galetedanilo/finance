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

#include "finance-entry-monetary.h"

struct _FinanceEntryMonetary
{
  GtkEntry    parent_class;

  gdouble     amount;

  gboolean    is_formatting;
  gboolean    is_currency_symbol;
};

G_DEFINE_TYPE (FinanceEntryMonetary, finance_entry_monetary, GTK_TYPE_ENTRY)

enum {
  PROP_0,
  PROP_AMOUNT,
  PROP_FORMATTING,
  PROP_CURRENCY_SYMBOL,
  N_PROPS,
};

static GParamSpec *properties[N_PROPS] = { NULL, };

static void
on_automatic_monetary_formatting (GtkEditable *editable,
                                  const gchar *text,
                                  gint        length,
                                  gint        *position,
                                  gpointer    user_data)
{

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

  if (!gtk_entry_get_text_length (GTK_ENTRY (widget)))
    return GTK_WIDGET_CLASS (finance_entry_monetary_parent_class)->focus_out_event (widget, event);

  value = g_strdup_printf ("%.2f", self->amount);

  gtk_entry_set_text (GTK_ENTRY (widget), value);

  g_free (value);

  return GTK_WIDGET_CLASS (finance_entry_monetary_parent_class)->focus_in_event (widget, event);
}

static gboolean
finance_entry_monetary_focus_out_event (GtkWidget     *widget,
                                        GdkEventFocus *event)
{
  FinanceEntryMonetary *self = FINANCE_ENTRY_MONETARY (widget);

  gchar money[20];

  if (!gtk_entry_get_text_length (GTK_ENTRY (widget)))
    return GTK_WIDGET_CLASS (finance_entry_monetary_parent_class)->focus_out_event (widget, event);

  self->amount = g_strtod (gtk_entry_get_text (GTK_ENTRY (widget)), NULL);

  if (self->is_currency_symbol)
    strfmon (money, 20, "%n", self->amount);
  else
    strfmon (money, 20, "%!n", self->amount);

  gtk_entry_set_text (GTK_ENTRY (widget), money);

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

    case PROP_FORMATTING:
      g_value_set_boolean (value, finance_entry_monetary_get_formatting (self));
      break;

    case PROP_CURRENCY_SYMBOL:
      g_value_set_boolean (value, finance_entry_monetary_get_currency_symbol (self));
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

    case PROP_FORMATTING:
      finance_entry_monetary_set_formatting (self, g_value_get_boolean (value));
      break;

    case PROP_CURRENCY_SYMBOL:
      finance_entry_monetary_set_currency_symbol (self, g_value_get_boolean (value));
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
   * FinanceEntryMonetary::formatting:
   *
   * Enable automatic monetary formatting
   */
  properties[PROP_FORMATTING] = g_param_spec_boolean ("formatting",
                                                      "Enable automatic monetary formatting",
                                                      "Enable automatic monetary formatting",
                                                      FALSE,
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

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/gui/finance-entry-monetary.ui");

  /* All Signals */
  gtk_widget_class_bind_template_callback (widget_class, on_automatic_monetary_formatting);
}

static void
finance_entry_monetary_init (FinanceEntryMonetary *self)
{
  self->is_currency_symbol  = FALSE;
  self->is_formatting       = FALSE;
  self->amount              = 0.0;

  gtk_widget_init_template (GTK_WIDGET (self));
}

/**
 * finance_entr_monetary_get_amount:
 * @self: a #FinanceEntryMonetary instance.
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
 * @self: a #FinanceEntryMonetary object.
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

  gchar *format;

  self->amount = amount;

  format = g_strdup_printf ("%f", self->amount);

  gtk_entry_set_text (GTK_ENTRY (self), format);

  g_free (format);
}

/**
 * finance_entry_monetary_get_formatting:
 * @self: a #FinanceEntryMonetary instance.
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

  return self->is_formatting;
}

/**
 * finance_entry_monetary_set_formatting:
 * @self: a #FinanceEntryMonetary object.
 * @is_formatting: %TRUE if formatting should be active, and %FALSE otherwise.
 *
 * Change automatic monetary formatting states. %TRUE if formatting should be active, and %FALSE otherwise.
 *
 * Since: 1.0
 */
void
finance_entry_monetary_set_formatting (FinanceEntryMonetary *self,
                                       gboolean             is_formatting)
{
  g_return_if_fail (FINANCE_IS_ENTRY_MONETARY (self));

  if (self->is_formatting == is_formatting)
    return;

  self->is_formatting = is_formatting;

  if (self->is_formatting)
    g_signal_handlers_unblock_by_func (self, on_automatic_monetary_formatting, self);
  else
    g_signal_handlers_block_by_func (self, on_automatic_monetary_formatting, self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FORMATTING]);
}

/**
 * finance_entry_manetary_get_currency_symbol:
 * @self: a #FinanceEntryMonetary instance.
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

  return self->is_currency_symbol;
}

/**
 * finance_entry_monetary_set_currency_symbol:
 * @self: a #FinanceEntryMonetary object.
 * @is_currency_symbol: %TRUE if currency symbol should be active, and %FALSE otherwise.
 *
 * Change currency symbol states. %TRUE if currency symbol should be active, and %FALSE otherwise.
 *
 * Since: 1.0
 */
void
finance_entry_monetary_set_currency_symbol (FinanceEntryMonetary  *self,
                                            gboolean              is_currency_symbol)
{
  g_return_if_fail (FINANCE_IS_ENTRY_MONETARY (self));

  if (self->is_currency_symbol == is_currency_symbol)
    return;

  self->is_currency_symbol = is_currency_symbol;

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_CURRENCY_SYMBOL]);
}

