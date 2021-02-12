/* finance-transaction.h
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

#ifndef __FINANCE_TRANSACTION_H__
#define __FINANCE_TRANSACTION_H__

#include <gtk/gtk.h>

#include "finance-entry-date.h"
#include "finance-entry-monetary.h"

G_BEGIN_DECLS

#define FINANCE_TYPE_TRANSACTION (finance_transaction_get_type())

G_DECLARE_FINAL_TYPE (FinanceTransaction, finance_transaction, FINANCE, TRANSACTION, GtkBox)

GtkWidget *     finance_transaction_new                 (void);

const gchar *   finance_transaction_get_icon            (FinanceTransaction *self);

void            finance_transaction_set_icon            (FinanceTransaction *self,
                                                         const gchar        *icon);

const gchar *   finance_transaction_get_name            (FinanceTransaction *self);

void            finance_transaction_set_name            (FinanceTransaction *self,
                                                         const gchar        *name);

gdouble         finance_transaction_get_amount          (FinanceTransaction *self);

void            finance_transaction_set_amount          (FinanceTransaction *self,
                                                         gdouble            amount);

GDateTime *     finance_transaction_get_date            (FinanceTransaction *self);

void            finance_transaction_set_date            (FinanceTransaction *self,
                                                         GDateTime          *date);

const gchar *   finance_transaction_get_payee_name      (FinanceTransaction *self);

void            finance_transaction_set_payee_name      (FinanceTransaction *self,
                                                         const gchar        *payee_name);

const gchar *   finance_transaction_get_payment_info    (FinanceTransaction *self);

void            finance_transaction_set_payment_info    (FinanceTransaction *self,
                                                         const gchar        *payment_info);

GDateTime *     finance_transaction_get_frequency_date  (FinanceTransaction *self);

void            finance_transaction_set_frequency_date  (FinanceTransaction *self,
                                                         GDateTime          *date);

G_END_DECLS

#endif /* __FINANCE_TRANSACTION_H__ */
