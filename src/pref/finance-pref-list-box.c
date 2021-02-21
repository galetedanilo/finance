/* finance-pref-list-box.c
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

#include "finance-config.h"

#include "finance-pref-list-box.h"

struct _FinancePrefListBox
{
  GtkListBox parent_instance;
};

G_DEFINE_TYPE (FinancePrefListBox, finance_pref_list_box, GTK_TYPE_LIST_BOX)

static void
on_list_box_row_activated (GtkListBox    *list,
                           GtkListBoxRow *row,
                           gpointer       user_data)
{
  (void)list;
  (void)user_data;

  finance_pref_row_change_preference (FINANCE_PREF_ROW (row));
}

FinancePrefListBox *
finance_pref_list_box_new (void)
{
  return g_object_new (FINANCE_TYPE_PREF_LIST_BOX, NULL);
}

static void
finance_pref_list_box_class_init (FinancePrefListBoxClass *klass)
{
  (void)klass;
}

static void
finance_pref_list_box_init (FinancePrefListBox *self)
{
  g_signal_connect (self,
                    "row-activated",
                    G_CALLBACK (on_list_box_row_activated),
                    self);
}
