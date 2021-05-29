/* finance-transactions-summary.h
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

#ifndef __FINANCE_TRANSACTIONS_SUMMARY_H__
#define __FINANCE_TRANSACTIONS_SUMMARY_H__

#include <gtk/gtk.h>

#include "finance-utils.h"

G_BEGIN_DECLS

#define FINANCE_TYPE_TRANSACTIONS_SUMMARY (finance_transactions_summary_get_type ())

G_DECLARE_FINAL_TYPE (FinanceTransactionsSummary, finance_transactions_summary, FINANCE, TRANSACTIONS_SUMMARY, GtkGrid)

GtkWidget *     finance_transactions_summary_new                 (void);

const gchar *   finance_transactions_summary_get_amount          (FinanceTransactionsSummary *self);

void            finance_transactions_summary_set_amount          (FinanceTransactionsSummary *self,
                                                                  const gchar                *amount);

const gchar *   finance_transactions_summary_get_category        (FinanceTransactionsSummary *self);

void            finance_transactions_summary_set_category        (FinanceTransactionsSummary *self,
                                                                  const gchar                *category);

const gchar *   finance_transactions_summary_get_date            (FinanceTransactionsSummary *self);

void            finance_transactions_summary_set_date            (FinanceTransactionsSummary *self,
                                                                  const gchar                *date);

const gchar *   finance_transactions_summary_get_icon_name       (FinanceTransactionsSummary *self);

void            finance_transactions_summary_set_icon_name       (FinanceTransactionsSummary *self,
                                                                  const gchar                *icon_name);

const gchar *   finance_transactions_summary_get_payee_name      (FinanceTransactionsSummary *self);

void            finance_transactions_summary_set_payee_name      (FinanceTransactionsSummary *self,
                                                                  const gchar                *payee_name);

const gchar *   finance_transactions_summary_get_payment         (FinanceTransactionsSummary *self);

void            finance_transactions_summary_set_payment         (FinanceTransactionsSummary *self,
                                                                  const gchar                *payment);

const gchar *   finance_transactions_summary_get_repeat          (FinanceTransactionsSummary *self);

void            finance_transactions_summary_set_repeat          (FinanceTransactionsSummary *self,
                                                                  const gchar                *repeat);

gboolean        finance_transactions_summary_get_selected        (FinanceTransactionsSummary *self);

void            finance_transactions_summary_set_selected        (FinanceTransactionsSummary *self,
                                                                  gboolean                    selected);

const gchar *   finance_transactions_summary_get_title           (FinanceTransactionsSummary *self);

void            finance_transactions_summary_set_title           (FinanceTransactionsSummary *self,
                                                                  const gchar                *title);

gint            finance_transactions_summary_get_transaction     (FinanceTransactionsSummary *self);

void            finance_transactions_summary_set_transaction     (FinanceTransactionsSummary *self,
                                                                  gint                        transaction);

G_END_DECLS

#endif /* __FINANCE_TRANSACTIONS_SUMMARY_H__ */
