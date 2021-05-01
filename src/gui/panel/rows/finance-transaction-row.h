/* finance-transaction-row.h
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

#ifndef __FINANCE_TRANSACTION_ROW_H__
#define __FINANCE_TRANSACTION_ROW_H__

#include <gtk/gtk.h>

#include "finance-utils.h"

G_BEGIN_DECLS

#define FINANCE_TYPE_TRANSACTION_ROW (finance_transaction_row_get_type ())

G_DECLARE_FINAL_TYPE (FinanceTransactionRow, finance_transaction_row, FINANCE, TRANSACTION_ROW, GtkListBoxRow)

GtkWidget *     finance_transaction_row_new               (void);

const gchar *   finance_transaction_row_get_amount        (FinanceTransactionRow *self);

void            finance_transaction_row_set_amount        (FinanceTransactionRow *self,
                                                           const gchar           *amount);

GdkRGBA *       finance_transaction_row_get_icon_color    (FinanceTransactionRow *self);

void            finance_transaction_row_set_icon_color    (FinanceTransactionRow *self,
                                                           const GdkRGBA         *color);

const gchar *   finance_transaction_row_get_icon_text     (FinanceTransactionRow *self);

void            finance_transaction_row_set_icon_text     (FinanceTransactionRow *self,
                                                           const gchar           *text);

gboolean        finance_transaction_row_get_selected      (FinanceTransactionRow *self);

void            finance_transaction_row_set_selected      (FinanceTransactionRow *self,
                                                           gboolean               selected);

const gchar *   finance_transaction_row_get_title         (FinanceTransactionRow *self);

void            finance_transaction_row_set_title         (FinanceTransactionRow *self,
                                                           const gchar           *title);

G_END_DECLS

#endif /* __FINANCE_TRANSACTION_ROW_H__ */
