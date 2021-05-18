/* finance-transaction-data.h
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

#ifndef __FINANCE_TRANSACTION_DATA_H__
#define __FINANCE_TRANSACTION_DATA_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define FINANCE_TYPE_TRANSACTION_DATA (finance_transaction_data_get_type ())

G_DECLARE_FINAL_TYPE (FinanceTransactionData, finance_transaction_data, FINANCE, TRANSACTION_DATA, G_TYPE_OBJECT)

FinanceTransactionData *  finance_transaction_data_new                          (void);

const gchar *             finance_transaction_data_get_amount                   (FinanceTransactionData *self);

void                      finance_transaction_data_set_amount                   (FinanceTransactionData *self,
                                                                                 const gchar            *amount);

gint                      finance_transaction_data_get_category                 (FinanceTransactionData *self);

void                      finance_transaction_data_set_category                 (FinanceTransactionData *self,
                                                                                 gint                    category);

const gchar *             finance_transaction_data_get_date                     (FinanceTransactionData *self);

void                      finance_transaction_data_set_date                     (FinanceTransactionData *self,
                                                                                 const gchar            *date);

gint                      finance_transaction_data_get_frequency                (FinanceTransactionData *self);

void                      finance_transaction_data_set_frequency                (FinanceTransactionData *self,
                                                                                 gint                    frequency);

const gchar *             finance_transaction_data_get_frequency_date           (FinanceTransactionData *self);

void                      finance_transaction_data_set_frequency_date           (FinanceTransactionData *self,
                                                                                 const gchar            *date);

gint                      finance_transaction_data_get_frequency_number         (FinanceTransactionData *self);

void                      finance_transaction_data_set_frequency_number         (FinanceTransactionData *self,
                                                                                 gint                    frequency_number);

GdkRGBA *                 finance_transaction_data_get_icon_color               (FinanceTransactionData *self);

void                      finance_transaction_data_set_icon_color               (FinanceTransactionData *self,
                                                                                 const GdkRGBA          *color);

const gchar *             finance_transaction_data_get_icon_name                (FinanceTransactionData *self);

void                      finance_transaction_data_set_icon_name                (FinanceTransactionData *self,
                                                                                 const gchar            *name);

const gchar *             finance_transaction_data_get_icon_text                (FinanceTransactionData *self);

void                      finance_transaction_data_set_icon_text                (FinanceTransactionData *self,
                                                                                 const gchar            *text);

const gchar *             finance_transaction_data_get_name                     (FinanceTransactionData *self);

void                      finance_transaction_data_set_name                     (FinanceTransactionData *self,
                                                                                 const gchar            *name);

const gchar *             finance_transaction_data_get_notes                    (FinanceTransactionData *self);

void                      finance_transaction_data_set_notes                    (FinanceTransactionData *self,
                                                                                 const gchar            *notes);

const gchar *             finance_transaction_data_get_payee_name               (FinanceTransactionData *self);

void                      finance_transaction_data_set_payee_name               (FinanceTransactionData *self,
                                                                                 const gchar            *payee_name);

gint                      finance_transaction_data_get_payment                  (FinanceTransactionData *self);

void                      finance_transaction_data_set_payment                  (FinanceTransactionData *self,
                                                                                 gint                    payment);

const gchar *             finance_transaction_data_get_payment_information      (FinanceTransactionData *self);

void                      finance_transaction_data_set_payment_information      (FinanceTransactionData *self,
                                                                                 const gchar            *information);

gint                      finance_transaction_data_get_repeat                   (FinanceTransactionData *self);

void                      finance_transaction_data_set_repeat                   (FinanceTransactionData *self,
                                                                                 gint                    repeat);

gint                      finance_transaction_data_get_type                     (FinanceTransactionData *self);

void                      finance_transaction_data_set_type                     (FinanceTransactionData *self,
                                                                                 gint                    type);

G_END_DECLS

#endif /* __FINANCE_TRANSACTION_DATA_H__ */
