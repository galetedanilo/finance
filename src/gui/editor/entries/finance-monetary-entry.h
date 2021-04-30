/* finance-monetary-entry.h
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

#ifndef __FINANCE_MONETARY_ENTRY_H__
#define __FINANCE_MONETARY_ENTRY_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FINANCE_TYPE_MONETARY_ENTRY (finance_monetary_entry_get_type())

G_DECLARE_FINAL_TYPE (FinanceMonetaryEntry, finance_monetary_entry, FINANCE, MONETARY_ENTRY, GtkEntry)

GtkWidget*    finance_monetary_entry_new                  (void);

gdouble       finance_monetary_entry_get_amount           (FinanceMonetaryEntry *self);

void          finance_monetary_entry_set_amount           (FinanceMonetaryEntry *self,
                                                           gdouble               amount);

gboolean      finance_monetary_entry_get_currency_symbol  (FinanceMonetaryEntry *self);

void          finance_monetary_entry_set_currency_symbol  (FinanceMonetaryEntry *self,
                                                           gboolean              currency_symbol);

gint          finance_monetary_entry_get_decimal_places   (FinanceMonetaryEntry *self);

void          finance_monetary_entry_set_decimal_places   (FinanceMonetaryEntry *self,
                                                           gint                  value);

gboolean      finance_monetary_entry_get_formatting       (FinanceMonetaryEntry *self);

void          finance_monetary_entry_set_formatting       (FinanceMonetaryEntry *self,
                                                           gboolean              formatting);

gint          finance_monetary_entry_get_symbol           (FinanceMonetaryEntry *self);

void          finance_monetary_entry_set_symbol           (FinanceMonetaryEntry *self,
                                                           gint                  symbol);

void          finance_monetary_entry_clear                (FinanceMonetaryEntry *self);

G_END_DECLS

#endif /* __FINANCE_MONETARY_ENTRY_H__ */
