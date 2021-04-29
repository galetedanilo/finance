/* finance-transaction-editor.h
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

#ifndef __FINANCE_TRANSACTION_EDITOR_H__
#define __FINANCE_TRANSACTION_EDITOR_H__

#include <gtk/gtk.h>

#include "finance-date-entry.h"
#include "finance-monetary-entry.h"
#include "finance-utils.h"

G_BEGIN_DECLS

#define FINANCE_TYPE_TRANSACTION_EDITOR (finance_transaction_editor_get_type())

G_DECLARE_FINAL_TYPE (FinanceTransactionEditor, finance_transaction_editor, FINANCE, TRANSACTION_EDITOR, GtkGrid)

GtkWidget *     finance_transaction_editor_new                        (void);

gdouble         finance_transaction_editor_get_amount                 (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_amount                 (FinanceTransactionEditor *self,
                                                                       gdouble                   amount);

gint            finance_transaction_editor_get_category               (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_category               (FinanceTransactionEditor *self,
                                                                       gint                      id_category);

GdkRGBA *       finance_transaction_editor_get_color                  (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_color                  (FinanceTransactionEditor *self,
                                                                       const GdkRGBA            *color);

const gchar *   finance_transaction_editor_get_date                   (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_date                   (FinanceTransactionEditor *self,
                                                                       const gchar              *date);

gint            finance_transaction_editor_get_frequency              (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_frequency              (FinanceTransactionEditor *self,
                                                                       gint                      frequency);

const gchar *   finance_transaction_editor_get_frequency_date         (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_frequency_date         (FinanceTransactionEditor *self,
                                                                       const gchar              *date);

gint            finance_transaction_editor_get_frequency_number       (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_frequency_number       (FinanceTransactionEditor *self,
                                                                       gint                      frequency_number);

const gchar *   finance_transaction_editor_get_icon                   (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_icon                   (FinanceTransactionEditor *self,
                                                                       const gchar              *icon);

gboolean        finance_transaction_editor_get_mobile                 (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_mobile                 (FinanceTransactionEditor *self,
                                                                       gboolean                  mobile);

const gchar *   finance_transaction_editor_get_name                   (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_name                   (FinanceTransactionEditor *self,
                                                                       const gchar              *name);

const gchar *   finance_transaction_editor_get_notes                  (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_notes                  (FinanceTransactionEditor *self,
                                                                       const gchar              *notes);

const gchar *   finance_transaction_editor_get_payee_name             (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_payee_name             (FinanceTransactionEditor *self,
                                                                       const gchar              *payee_name);

gint            finance_transaction_editor_get_payment                (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_payment                (FinanceTransactionEditor *self,
                                                                       gint                      payment);

const gchar *   finance_transaction_editor_get_payment_information    (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_payment_information    (FinanceTransactionEditor *self,
                                                                       const gchar              *information);

gint            finance_transaction_editor_get_repeat                 (FinanceTransactionEditor *self);

void            finance_transaction_editor_set_repeat                 (FinanceTransactionEditor *self,
                                                                       gint                      repeat);

void            finance_transaction_editor_clear                      (FinanceTransactionEditor *self);

G_END_DECLS

#endif /* __FINANCE_TRANSACTION_EDITOR_H__ */
