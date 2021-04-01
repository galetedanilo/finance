/* finance-view-transactions.h
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

#ifndef __FINANCE_VIEW_TRANSACTIONS_H__
#define __FINANCE_VIEW_TRANSACTIONS_H__

#include <gtk/gtk.h>

#include "finance-view-child.h"

G_BEGIN_DECLS

#define FINANCE_TYPE_VIEW_TRANSACTIONS (finance_view_transactions_get_type())

G_DECLARE_FINAL_TYPE (FinanceViewTransactions, finance_view_transactions, FINANCE, VIEW_TRANSACTIONS, GtkBox)

GtkWidget *   finance_view_transactions_new     (void);

G_END_DECLS

#endif /* __FINANCE_VIEW_TRANSACTIONS_H__ */
