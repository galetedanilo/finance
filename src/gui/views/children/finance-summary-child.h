/* finance-summary-child.h
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

#ifndef __FINANCE_SUMMARY_CHILD_H__
#define __FINANCE_SUMMARY_CHILD_H__

#include <gtk/gtk.h>

#include "finance-utils.h"

G_BEGIN_DECLS

#define FINANCE_TYPE_SUMMARY_CHILD (finance_summary_child_get_type ())

G_DECLARE_FINAL_TYPE (FinanceSummaryChild, finance_summary_child, FINANCE, SUMMARY_CHILD, GtkGrid)

GtkWidget *     finance_summary_child_new                 (void);

const gchar *   finance_summary_child_get_amount          (FinanceSummaryChild *self);

void            finance_summary_child_set_amount          (FinanceSummaryChild *self,
                                                           const gchar         *amount);

const gchar *   finance_summary_child_get_category        (FinanceSummaryChild *self);

void            finance_summary_child_set_category        (FinanceSummaryChild *self,
                                                           const gchar         *category);

const gchar *   finance_summary_child_get_date            (FinanceSummaryChild *self);

void            finance_summary_child_set_date            (FinanceSummaryChild *self,
                                                           const gchar         *date);

const gchar *   finance_summary_child_get_icon_name       (FinanceSummaryChild *self);

void            finance_summary_child_set_icon_name       (FinanceSummaryChild *self,
                                                           const gchar         *icon_name);

const gchar *   finance_summary_child_get_name            (FinanceSummaryChild *self);

void            finance_summary_child_set_name            (FinanceSummaryChild *self,
                                                           const gchar         *name);

const gchar *   finance_summary_child_get_payee_name      (FinanceSummaryChild *self);

void            finance_summary_child_set_payee_name      (FinanceSummaryChild *self,
                                                           const gchar         *payee_name);

const gchar *   finance_summary_child_get_payment         (FinanceSummaryChild *self);

void            finance_summary_child_set_payment         (FinanceSummaryChild *self,
                                                           const gchar         *payment);

const gchar *   finance_summary_child_get_repeat          (FinanceSummaryChild *self);

void            finance_summary_child_set_repeat          (FinanceSummaryChild *self,
                                                           const gchar         *repeat);

gboolean        finance_summary_child_get_selected        (FinanceSummaryChild *self);

void            finance_summary_child_set_selected        (FinanceSummaryChild *self,
                                                           gboolean             selected);

gint            finance_summary_child_get_transaction     (FinanceSummaryChild *self);

void            finance_summary_child_set_transaction     (FinanceSummaryChild *self,
                                                           gint                 transaction);

G_END_DECLS

#endif /* __FINANCE_SUMMARY_CHILD_H__ */
