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
 * finance_pref_row_get_title:
 * @row: a #FinancePrefRow.
 *
 * Returns the title from the label of the row.
 *
 * Returns: The title in the #FinancePrefRow, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pref_row_get_title (FinancePrefRow *row)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW (row), NULL);
  g_return_val_if_fail (FINANCE_PREF_ROW_GET_IFACE (row)->get_title, NULL);

  return FINANCE_PREF_ROW_GET_IFACE (row)->get_title (row);
}

/**
 * finance_pref_row_set_title:
 * @row: a #FinancePrefRow.
 * @title: The title to set.
 *
 * Sets the title within the #FinancePrefRow, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pref_row_set_title (FinancePrefRow  *row,
                            const gchar     *title)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW (row));
  g_return_if_fail (FINANCE_PREF_ROW_GET_IFACE (row)->set_title);

  FINANCE_PREF_ROW_GET_IFACE (row)->set_title (row, title);
}

/**
 * finance_pref_row_get_text:
 * @row: a #FinancePrefRow.
 *
 * Returns the tex from the label of the row.
 *
 * Returns: The text in the #FinancePrefRow, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pref_row_get_text (FinancePrefRow *row)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW (row), NULL);
  g_return_val_if_fail (FINANCE_PREF_ROW_GET_IFACE (row)->get_text, NULL);

  return FINANCE_PREF_ROW_GET_IFACE (row)->get_text (row);
}

/**
 * finance_pref_row_set_text:
 * @row: a #FinancePrefRow.
 * @title: The text to set.
 *
 * Sets the text within the #FinancePrefRow, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pref_row_set_text (FinancePrefRow *row,
                           const gchar    *text)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW (row));
  g_return_if_fail (FINANCE_PREF_ROW_GET_IFACE (row)->set_text);

  FINANCE_PREF_ROW_GET_IFACE (row)->set_text (row, text);
}

/**
 * finance_pref_row_get_key:
 * @row: a #FinancePrefRow.
 *
 * Returns the key of the row.
 *
 * Returns: The key in the #FinancePrefRow, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pref_row_get_key (FinancePrefRow *row)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW (row), NULL);
  g_return_val_if_fail (FINANCE_PREF_ROW_GET_IFACE (row)->get_key, NULL);

  return FINANCE_PREF_ROW_GET_IFACE (row)->get_key (row);
}

/**
 * finance_pref_row_set_key:
 * @row: a #FinancePrefRow.
 * @key: The key to set.
 *
 * Sets the key within the #FinancePrefRow, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pref_row_set_key (FinancePrefRow  *row,
                           const gchar    *key)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW (row));
  g_return_if_fail (FINANCE_PREF_ROW_GET_IFACE (row)->set_key);

  FINANCE_PREF_ROW_GET_IFACE (row)->set_key (row, key);
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

/**
 * finance_pref_row_add_settings:
 * @row: a #FinancePrefRow.
 * @settings: a #GSettings
 *
 * Sets a #GSetting references in #FinancePrefRow.
 *
 * Since: 1.0
 */
void
finance_pref_row_add_settings (FinancePrefRow *row,
                               GSettings      *settings)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW (row));
  g_return_if_fail (FINANCE_PREF_ROW_GET_IFACE (row)->add_settings);

  FINANCE_PREF_ROW_GET_IFACE (row)->add_settings (row, settings);
}
