/* finance-object-transaction.h
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

#ifndef __FINANCE_OBJECT_TRANSACTION_H__
#define __FINANCE_OBJECT_TRANSACTION_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define FINANCE_TYPE_OBJECT_TRANSACTION (finance_object_transaction_get_type())

G_DECLARE_FINAL_TYPE (FinanceObjectTransaction, finance_object_transaction, FINANCE, OBJECT_TRANSACTION, GObject)

FinanceObjectTransaction *      finance_object_transaction_new                          (void);

gdouble                         finance_object_transaction_get_amount                   (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_amount                   (FinanceObjectTransaction *self,
                                                                                         gdouble                   amount);

const gchar *                   finance_object_transaction_get_category                 (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_category                 (FinanceObjectTransaction *self,
                                                                                         const gchar              *category);

GdkRGBA *                       finance_object_transaction_get_color                    (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_color                    (FinanceObjectTransaction *self,
                                                                                         const GdkRGBA            *color);

GDateTime *                     finance_object_transaction_get_date                     (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_date                     (FinanceObjectTransaction *self,
                                                                                         GDateTime                *date);

gint                            finance_object_transaction_get_frequency                (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_frequency                (FinanceObjectTransaction *self,
                                                                                         gint                      frequency);

GDateTime *                     finance_object_transaction_get_frequency_date           (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_frequency_date           (FinanceObjectTransaction *self,
                                                                                         GDateTime                *date);

gint                            finance_object_transaction_get_frequency_number         (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_frequency_number         (FinanceObjectTransaction *self,
                                                                                         gint                      frequency_number);

const gchar *                   finance_object_transaction_get_icon                     (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_icon                     (FinanceObjectTransaction *self,
                                                                                         const gchar              *icon);

const gchar *                   finance_object_transaction_get_name                     (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_name                     (FinanceObjectTransaction *self,
                                                                                         const gchar              *name);

const gchar *                   finance_object_transaction_get_notes                    (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_notes                    (FinanceObjectTransaction *self,
                                                                                         const gchar              *notes);

const gchar *                   finance_object_transaction_get_payee_name               (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_payee_name               (FinanceObjectTransaction *self,
                                                                                         const gchar              *payee_name);

gint                            finance_object_transaction_get_payment                  (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_payment                  (FinanceObjectTransaction *self,
                                                                                         gint                      payment);

const gchar *                   finance_object_transaction_get_payment_information      (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_payment_information      (FinanceObjectTransaction *self,
                                                                                         const gchar              *information);

gint                            finance_object_transaction_get_repeat                   (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_repeat                   (FinanceObjectTransaction *self,
                                                                                         gint                      repeat);

gint                            finance_object_transaction_get_type                     (FinanceObjectTransaction *self);

void                            finance_object_transaction_set_type                     (FinanceObjectTransaction *self,
                                                                                         gint                      type);

G_END_DECLS

#endif /* __FINANCE_OBJECT_TRANSACTION_H__ */
