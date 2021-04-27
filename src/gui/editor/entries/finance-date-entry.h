/* finance-date-entry.h
 *
 * Copyright 2020 - 2021 galetedanilo <galetedanilo@gmail.com>
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

#ifndef __FINANCE_DATE_ENTRY_H__
#define __FINANCE_DATE_ENTRY_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FINANCE_TYPE_DATE_ENTRY (finance_date_entry_get_type ())

G_DECLARE_FINAL_TYPE (FinanceDateEntry, finance_date_entry, FINANCE, DATE_ENTRY, GtkEntry)

GtkWidget *       finance_date_entry_new              (void);

GDateTime *       finance_date_entry_get_date         (FinanceDateEntry *self);

void              finance_date_entry_set_date         (FinanceDateEntry *self,
                                                       GDateTime        *date);

gboolean          finance_date_entry_get_formatting   (FinanceDateEntry *self);

void              finance_date_entry_set_formatting   (FinanceDateEntry *self,
                                                       gboolean          formatting);

G_END_DECLS

#endif /* __FINANCE_DATE_ENTRY_H__ */
