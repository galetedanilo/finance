/* finance-child-summary.h
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

#ifndef __FINANCE_CHILD_SUMMARY_H__
#define __FINANCE_CHILD_SUMMARY_H__

#include <gtk/gtk.h>

#include "finance-utils.h"

G_BEGIN_DECLS

#define FINANCE_TYPE_CHILD_SUMMARY (finance_child_summary_get_type ())

G_DECLARE_FINAL_TYPE (FinanceChildSummary, finance_child_summary, FINANCE, CHILD_SUMMARY, GtkButton)

GtkWidget *     finance_child_summary_new           (void);

const gchar *   finance_child_summary_get_icon      (FinanceChildSummary *self);

void            finance_child_summary_set_icon      (FinanceChildSummary *self,
                                                     const gchar         *icon);

GdkRGBA *       finance_child_summary_get_color     (FinanceChildSummary *self);

void            finance_child_summary_set_color     (FinanceChildSummary *self,
                                                     const GdkRGBA       *color);

const gchar *   finance_child_summary_get_name      (FinanceChildSummary *self);

void            finance_child_summary_set_name      (FinanceChildSummary *self,
                                                     const gchar         *name);

const gchar *   finance_child_summary_get_amount    (FinanceChildSummary *self);

void            finance_child_summary_set_amount    (FinanceChildSummary *self,
                                                     const gchar         *amount);

const gchar *   finance_child_summary_get_date      (FinanceChildSummary *self);

void            finance_child_summary_set_date      (FinanceChildSummary *self,
                                                     const gchar         *date);

const gchar *   finance_child_summary_get_payee_name(FinanceChildSummary *self);

void            finance_child_summary_set_payee_name(FinanceChildSummary *self,
                                                     const gchar         *payee_name);

const gchar *   finance_child_summary_get_payment   (FinanceChildSummary *self);

void            finance_child_summary_set_payment   (FinanceChildSummary *self,
                                                     const gchar         *payment);

const gchar *   finance_child_summary_get_category  (FinanceChildSummary *self);

void            finance_child_summary_set_category  (FinanceChildSummary *self,
                                                     const gchar         *category);

const gchar *   finance_child_summary_get_repeat    (FinanceChildSummary *self);

void            finance_child_summary_set_repeat    (FinanceChildSummary *self,
                                                     const gchar         *repeat);

G_END_DECLS

#endif /* __FINANCE_CHILD_SUMMARY_H__ */
