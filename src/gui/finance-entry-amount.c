/* finance-entry-amount.c
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

#include "finance-entry-amount.h"

struct _FinanceEntryAmount
{
  GtkEntry    parent_class;
};

G_DEFINE_TYPE (FinanceEntryAmount, finance_entry_amount, GTK_TYPE_ENTRY)

static void
on_entry_state_flags_changed (GtkWidget     *widget,
                              GtkStateFlags flags,
                              gpointer      user_data)
{
  (void)user_data;

  gchar   money[20];
  double  value;

  if (flags & (GTK_STATE_FLAG_DIR_LTR | GTK_STATE_FLAG_FOCUSED))
    {
      value = g_strtod (gtk_entry_get_text (GTK_ENTRY (widget)), NULL);

      strfmon (money, 20, "%!n", value);

      gtk_entry_set_text (GTK_ENTRY (widget), money);
    }
}

GtkWidget *
finance_entry_amount_new (void)
{
  return g_object_new (FINANCE_TYPE_ENTRY_AMOUNT, NULL);
}

static void
finance_entry_amount_class_init (FinanceEntryAmountClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Finance/gui/finance-entry-amount.ui");

  /* All Signals */
  gtk_widget_class_bind_template_callback (widget_class, on_entry_state_flags_changed);
}

static void
finance_entry_amount_init (FinanceEntryAmount *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}