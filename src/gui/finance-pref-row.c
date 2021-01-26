/* finance-pref-row.c
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

#include "finance-pref-row.h"

G_DEFINE_INTERFACE (FinancePrefRow, finance_pref_row, GTK_TYPE_LIST_BOX_ROW)

static void
finance_pref_row_default_init (FinancePrefRowInterface *iface)
{

}

/**
 * finance_pref_row_change_preference:
 * @row: a #FinancePrefRow.
 *
 * When a new preference is selected in #FinancePrefListBox this method is
 * responsible for changing the preferences.
 *
 * Since: 1.0
 */
void
finance_pref_row_change_preference (FinancePrefRow *row)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW (row));
  g_return_if_fail (FINANCE_PREF_ROW_GET_IFACE (row)->change_preference);

  FINANCE_PREF_ROW_GET_IFACE (row)->change_preference (row);
}
