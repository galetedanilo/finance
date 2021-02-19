/* finance-entry-monetary.h
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

#ifndef __FINANCE_ENTRY_MONETARY_H__
#define __FINANCE_ENTRY_MONETARY_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FINANCE_TYPE_ENTRY_MONETARY (finance_entry_monetary_get_type())

G_DECLARE_FINAL_TYPE (FinanceEntryMonetary, finance_entry_monetary, FINANCE, ENTRY_MONETARY, GtkEntry)

GtkWidget*    finance_entry_monetary_new                  (void);

gdouble       finance_entry_monetary_get_amount           (FinanceEntryMonetary *self);

void          finance_entry_monetary_set_amount           (FinanceEntryMonetary *self,
                                                           gdouble              amount);

gint          finance_entry_monetary_get_decimal_places   (FinanceEntryMonetary *self);

void          finance_entry_monetary_set_decimal_places   (FinanceEntryMonetary *self,
                                                           gint                 value);

gboolean      finance_entry_monetary_get_formatting       (FinanceEntryMonetary *self);

void          finance_entry_monetary_set_formatting       (FinanceEntryMonetary *self,
                                                           gboolean             is_formatting);

gboolean      finance_entry_monetary_get_currency_symbol  (FinanceEntryMonetary *self);

void          finance_entry_monetary_set_currency_symbol  (FinanceEntryMonetary *self,
                                                           gboolean             is_currency_symbol);

gint          finance_entry_monetary_get_symbol_type      (FinanceEntryMonetary *self);

void          finance_entry_monetary_set_symbol_type      (FinanceEntryMonetary *self,
                                                           gint                 symbol_type);

G_END_DECLS

#endif /* __FINANCE_ENTRY_MONETARY_H__ */
