/* finance-pref-row.h
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

#ifndef __FINANCE_PREF_ROW_H__
#define __FINANCE_PREF_ROW_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FINANCE_TYPE_PREF_ROW (finance_pref_row_get_type ())

G_DECLARE_INTERFACE (FinancePrefRow, finance_pref_row, FINANCE, PREF_ROW, GObject)

struct _FinancePrefRowInterface
{
  GTypeInterface  parent_iface;

  const gchar *   (*get_title)                      (FinancePrefRow *row);

  void            (*set_title)                      (FinancePrefRow *row,
                                                     const gchar    *title);

  const gchar *   (*get_text)                       (FinancePrefRow *row);

  void            (*set_text)                       (FinancePrefRow *row,
                                                     const gchar    *text);

  const gchar *   (*get_key)                        (FinancePrefRow *row);

  void            (*set_key)                        (FinancePrefRow *row,
                                                     const gchar    *key);

  void            (*change_preference)              (FinancePrefRow *row);

  void            (*add_settings)                   (FinancePrefRow *row,
                                                     GSettings      *settings);
};




const gchar *     finance_pref_row_get_title          (FinancePrefRow *row);

void              finance_pref_row_set_title          (FinancePrefRow *row,
                                                       const gchar    *title);

const gchar *     finance_pref_row_get_text           (FinancePrefRow *row);

void              finance_pref_row_set_text           (FinancePrefRow *row,
                                                       const gchar    *text);

const gchar *     finance_pref_row_get_key            (FinancePrefRow *row);

void              finance_pref_row_set_key            (FinancePrefRow *row,
                                                       const gchar    *key);

void              finance_pref_row_change_preference  (FinancePrefRow *row);

void              finance_pref_row_add_settings       (FinancePrefRow *row,
                                                       GSettings      *settings);

G_END_DECLS

#endif /* __FINANCE_PREF_ROW_H__ */
