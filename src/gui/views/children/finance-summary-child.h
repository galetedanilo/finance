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

G_DECLARE_FINAL_TYPE (FinanceSummaryChild, finance_summary_child, FINANCE, SUMMARY_CHILD, GtkButton)

GtkWidget *     finance_summary_child_new                 (void);

gdouble         finance_summary_child_get_amount          (FinanceSummaryChild *self);

void            finance_summary_child_set_amount          (FinanceSummaryChild *self,
                                                           double               amount);

const gchar *   finance_summary_child_get_amount_string   (FinanceSummaryChild *self);

void            finance_summary_child_set_amount_string   (FinanceSummaryChild *self,
                                                           const gchar         *amount);

const gchar *   finance_summary_child_get_category        (FinanceSummaryChild *self);

void            finance_summary_child_set_category        (FinanceSummaryChild *self,
                                                           const gchar         *category);

GdkRGBA *       finance_summary_child_get_color           (FinanceSummaryChild *self);

void            finance_summary_child_set_color           (FinanceSummaryChild *self,
                                                           const GdkRGBA       *color);

gboolean        finance_summary_child_get_currency_symbol (FinanceSummaryChild  *self);

void            finance_summary_child_set_currency_symbol (FinanceSummaryChild *self,
                                                           gboolean             currency_symbol);

void            finance_summary_child_set_date            (FinanceSummaryChild *self,
                                                           GDateTime           *date);

const gchar *   finance_summary_child_get_icon            (FinanceSummaryChild *self);

void            finance_summary_child_set_icon            (FinanceSummaryChild *self,
                                                           const gchar         *icon);

const gchar *   finance_summary_child_get_name            (FinanceSummaryChild *self);

void            finance_summary_child_set_name            (FinanceSummaryChild *self,
                                                           const gchar         *name);

void            finance_summary_child_set_payee_name      (FinanceSummaryChild *self,
                                                           const gchar         *payee_name);

void            finance_summary_child_set_payment         (FinanceSummaryChild *self,
                                                           gint                 payment);

void            finance_summary_child_set_repeat          (FinanceSummaryChild *self,
                                                           gint                 repeat);

void            finance_summary_child_set_symbol          (FinanceSummaryChild *self,
                                                           gint                 symbol);

G_END_DECLS

#endif /* __FINANCE_SUMMARY_CHILD_H__ */
