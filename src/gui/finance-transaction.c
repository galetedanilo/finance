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

#include <glib/gi18n.h>
#include "finance-config.h"
#include "finance-enums.h"

#include "finance-transaction.h"

struct _FinanceTransaction
{
  GtkBox    parent_instance;

  GtkWidget *icon;
  GtkWidget *name;
  GtkWidget *amount;
  GtkWidget *date;
  GtkWidget *payee_name;
  GtkWidget *payment;
  GtkWidget *payment_info;
  GtkWidget *category;
  GtkWidget *repeat;
  GtkWidget *frequency;
  GtkWidget *frequency_type;
  GtkWidget *frequency_date;
  GtkWidget *notes;

  GSettings *settings;
};

G_DEFINE_TYPE (FinanceTransaction, finance_transaction, GTK_TYPE_BOX)

enum {
  PROP_0,
  PROP_ICON,
  PROP_NAME,
  PROP_AMOUNT,
  PROP_DATE,
  PROP_PAYEE_NAME,
  PROP_PAYMENT,
  PROP_PAYMENT_INFO,
  PROP_CATEGORY,
  PROP_REPEAT,
  PROP_FREQUENCY,
  PROP_FREQUENCY_TYPE,
  PROP_FREQUENCY_DATE,
  PROP_NOTES,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };


static void
on_frequency_type_changed (GtkComboBox  *widget,
                           gpointer     user_data)
{
  FinanceTransaction *self = FINANCE_TRANSACTION (user_data);

  FinanceFrequency data = gtk_combo_box_get_active (GTK_COMBO_BOX (widget));

  gtk_spin_button_set_value (GTK_SPIN_BUTTON (self->frequency), 2);

  gtk_entry_set_text (GTK_ENTRY (self->frequency_date), "");

  switch (data)
    {
    case FOREVER:
      gtk_widget_set_visible (self->frequency, FALSE);
      gtk_widget_set_visible (self->frequency_date, FALSE);
      break;

    case N_OCCURRENCES:
      gtk_widget_set_visible (self->frequency, TRUE);
      gtk_widget_set_visible (self->frequency_date, FALSE);
      break;

    case UNTIL_DATE:
      gtk_widget_set_visible (self->frequency, FALSE);
      gtk_widget_set_visible (self->frequency_date, TRUE);
      break;

    }
}

static void
on_repeat_changed (GtkComboBox  *widget,
                   gpointer     user_data)
{
  FinanceTransaction *self = FINANCE_TRANSACTION (user_data);

  gtk_combo_box_set_active (GTK_COMBO_BOX (self->frequency_type), 0);

  gtk_widget_set_visible (self->frequency_type,
                          gtk_combo_box_get_active (widget));

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

  g_clear_object (&self->settings);

  G_OBJECT_CLASS (finance_transaction_parent_class)->finalize (object);
}

static void
finance_transaction_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{

}

static void
finance_transaction_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec)
{

}

static void
finance_transaction_class_init (FinanceTransactionClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  g_type_ensure (FINANCE_TYPE_ENTRY_MONETARY);
  g_type_ensure (FINANCE_TYPE_ENTRY_DATE);

  object_class->finalize = finance_transaction_finalize;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/gui/finance-transaction.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, icon);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, name);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, amount);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, date);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, payee_name);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, payment);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, payment_info);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, category);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, repeat);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, frequency);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, frequency_type);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, frequency_date);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransaction, notes);

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_repeat_changed);
  gtk_widget_class_bind_template_callback (widget_class, on_frequency_type_changed);
}

static void
finance_transaction_init (FinanceTransaction *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->settings = g_settings_new ("org.gnome.Finance");

  g_settings_bind (self->settings, "date",
                   self->date, "formatting",
                   G_SETTINGS_BIND_GET);

  g_settings_bind (self->settings, "date",
                   self->frequency_date, "formatting",
                   G_SETTINGS_BIND_GET);

  g_settings_bind (self->settings, "amount",
                   self->amount, "formatting",
                   G_SETTINGS_BIND_GET);

  g_settings_bind (self->settings, "decimal-places",
                   self->amount, "decimal-places",
                   G_SETTINGS_BIND_GET);

  g_settings_bind (self->settings, "currency-symbol",
                   self->amount, "currency-symbol",
                   G_SETTINGS_BIND_GET);

  g_settings_bind (self->settings, "symbol-type",
                   self->amount, "symbol-type",
                   G_SETTINGS_BIND_GET);

}

/**
 * finance_transaction_get_icon:
 * @self: a #FinanceTransaction object.
 *
 * Returns the value from the label icon of the transaction.
 *
 * Returns: The icon in the #FinanceTransaction, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_get_icon (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->icon));
}

/**
 * finance_transaction_set_icon:
 * @self: a #FinanceTransaction instance.
 * @icon: The icon to set, as a string.
 *
 * Sets the icon within the #FinanceTransaction, replacing the current contents.
 *
 * Since:1.0
 */
void
finance_transaction_set_icon (FinanceTransaction *self,
                              const gchar        *icon)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  gtk_label_set_text (GTK_LABEL (self->icon), icon);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON]);
}

/**
 * finance_transaction_get_name:
 * @self: a #FinanceTransaction object.
 *
 * Returns the name
 *
 * Returns: The name in the #FinanceTransaction, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_get_name (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), NULL);

  return gtk_entry_get_text (GTK_ENTRY (self->name));
}

/**
 * finance_transaction_set_name:
 * @self: a #FinanceTransaction instance.
 * @name: The name to set, as a string.
 *
 * Returns: The name in the #FinanceTransaction, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
void
finance_transaction_set_name (FinanceTransaction *self,
                              const gchar        *name)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  gtk_entry_set_text (GTK_ENTRY (self->name), name);
}

/**
 * finance_transaction_get_amount:
 * @self: a #FinanceTransaction instance.
 *
 * Gets the amount value in #FinanceTransaction.
 *
 * Returns: a #gdouble.
 *
 * Since: 1.0
 */
gdouble
finance_transaction_get_amount (FinanceTransaction *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION (self), 0.0);

  return finance_entry_monetary_get_amount (FINANCE_ENTRY_MONETARY (self->amount));
}

/**
 * finance_transaction_set_amount:
 * @self: a #FinanceTransaction object.
 * @amount: a #gdouble to set it to.
 *
 * Sets amount value in #FinanceTransaction.
 *
 * Since: 1.0
 */
void
finance_transaction_set_amount (FinanceTransaction *self,
                                gdouble            amount)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  finance_entry_monetary_set_amount (FINANCE_ENTRY_MONETARY (self->amount), amount);
}
