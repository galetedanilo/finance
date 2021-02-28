/* finance-pane-row.c
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

#include "finance-pane-row.h"

struct _FinancePaneRow
{
  GtkListBoxRow   parent_class;

  /* The Widgets */
  GtkWidget       *image;
  GtkWidget       *name;
  GtkWidget       *amount;
  GtkWidget       *category;
  GtkWidget       *revealer;
  GtkWidget       *check;

  gchar           *icon;
  gdouble         value;
};

G_DEFINE_TYPE (FinancePaneRow, finance_pane_row, GTK_TYPE_LIST_BOX_ROW)

enum {
  PROP_0,
  PROP_ICON,
}
