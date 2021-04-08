/* finance-controller-transactions.h
 *
 * Copyright 2021 Danilo Fernandes Galete <galetedanilo@gmail.com>
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

#ifndef __FINANCE_CONTROLLER_TRANSACTIONS_H__
#define __FINANCE_CONTROLLER_TRANSACTIONS_H__

#include <glib-object.h>

#include "finance-pane.h"
#include "finance-pane-row.h"
#include "finance-view.h"
#include "finance-view-child.h"

G_BEGIN_DECLS

#define FINANCE_TYPE_CONTROLLER_TRANSACTIONS (finance_controller_transactions_get_type ())

G_DECLARE_FINAL_TYPE (FinanceControllerTransactions, finance_controller_transactions, FINANCE, CONTROLLER_TRANSACTIONS, GObject)

void        finance_controller_transactions_startup     (FinanceControllerTransactions *self);

G_END_DECLS

#endif /* ___FINANCE_CONTROLLER_TRANSACTIONS_H__ */
