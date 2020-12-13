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

};

G_DEFINE_TYPE (FinanceTransaction, finance_transaction, GTK_TYPE_BOX)

enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];


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

  if (gtk_combo_box_get_active (widget) != 0)
    gtk_widget_set_visible (self->frequency_type, TRUE);
  else
    gtk_widget_set_visible (self->frequency, FALSE);
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

  G_OBJECT_CLASS (finance_transaction_parent_class)->finalize (object);
}

static void
finance_transaction_class_init (FinanceTransactionClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  g_type_ensure (FINANCE_TYPE_ENTRY_MONETARY);
  g_type_ensure (FINANCE_TYPE_ENTRY_DATE);

  object_class->finalize = finance_transaction_finalize;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Finance/gui/finance-transaction.ui");

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
}

void
finance_transaction_preferences_update (FinanceTransaction  *self)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION (self));

  GSettings *settings;

  settings = g_settings_new ("org.gnome.Finance");

  finance_entry_date_set_format_date (FINANCE_ENTRY_DATE (self->date),
                                      g_settings_get_boolean (settings, "date-formatting"));

  finance_entry_date_set_format_date (FINANCE_ENTRY_DATE (self->frequency_date),
                                      g_settings_get_boolean (settings, "date-formatting"));
}
