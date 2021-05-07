/* finance-transaction-entity.h
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

#ifndef __FINANCE_TRANSACTION_ENTITY_H__
#define __FINANCE_TRANSACTION_ENTITY_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define FINANCE_TYPE_TRANSACTION_ENTITY (finance_transaction_entity_get_type())

G_DECLARE_FINAL_TYPE (FinanceTransactionEntity, finance_transaction_entity, FINANCE, TRANSACTION_ENTITY, GObject)

FinanceTransactionEntity *      finance_transaction_entity_new                          (void);

gdouble                         finance_transaction_entity_get_amount                   (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_amount                   (FinanceTransactionEntity *self,
                                                                                         gdouble                   amount);

const gchar *                   finance_transaction_entity_get_category                 (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_category                 (FinanceTransactionEntity *self,
                                                                                         const gchar              *category);

GDateTime *                     finance_transaction_entity_get_date                     (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_date                     (FinanceTransactionEntity *self,
                                                                                         GDateTime                *date);

gint                            finance_transaction_entity_get_frequency                (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_frequency                (FinanceTransactionEntity *self,
                                                                                         gint                      frequency);

GDateTime *                     finance_transaction_entity_get_frequency_date           (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_frequency_date           (FinanceTransactionEntity *self,
                                                                                         GDateTime                *date);

gint                            finance_transaction_entity_get_frequency_number         (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_frequency_number         (FinanceTransactionEntity *self,
                                                                                         gint                      frequency_number);

GdkRGBA *                       finance_transaction_entity_get_icon_color               (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_icon_color               (FinanceTransactionEntity *self,
                                                                                         const GdkRGBA            *color);

const gchar *                   finance_transaction_entity_get_icon_name                (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_icon_name                (FinanceTransactionEntity *self,
                                                                                         const gchar              *name);

const gchar *                   finance_transaction_entity_get_icon_text                (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_icon_text                (FinanceTransactionEntity *self,
                                                                                         const gchar              *text);

const gchar *                   finance_transaction_entity_get_name                     (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_name                     (FinanceTransactionEntity *self,
                                                                                         const gchar              *name);

const gchar *                   finance_transaction_entity_get_notes                    (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_notes                    (FinanceTransactionEntity *self,
                                                                                         const gchar              *notes);

const gchar *                   finance_transaction_entity_get_payee_name               (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_payee_name               (FinanceTransactionEntity *self,
                                                                                         const gchar              *payee_name);

gint                            finance_transaction_entity_get_payment                  (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_payment                  (FinanceTransactionEntity *self,
                                                                                         gint                      payment);

const gchar *                   finance_transaction_entity_get_payment_information      (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_payment_information      (FinanceTransactionEntity *self,
                                                                                         const gchar              *information);

gint                            finance_transaction_entity_get_repeat                   (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_repeat                   (FinanceTransactionEntity *self,
                                                                                         gint                      repeat);

gint                            finance_transaction_entity_get_type                     (FinanceTransactionEntity *self);

void                            finance_transaction_entity_set_type                     (FinanceTransactionEntity *self,
                                                                                         gint                      type);

G_END_DECLS

#endif /* __FINANCE_TRANSACTION_ENTITY_H__ */
