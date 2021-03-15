/* finance-pane-row.h
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

#ifndef __FINANCE_PANE_ROW_H__
#define __FINANCE_PANE_ROW_H__

#include <gtk/gtk.h>

#include "finance-utils.h"

G_BEGIN_DECLS

#define FINANCE_TYPE_PANE_ROW (finance_pane_row_get_type ())

G_DECLARE_FINAL_TYPE (FinancePaneRow, finance_pane_row, FINANCE, PANE_ROW, GtkListBoxRow)

GtkWidget *     finance_pane_row_new              (void);

const gchar *   finance_pane_row_get_icon         (FinancePaneRow *self);

void            finance_pane_row_set_icon         (FinancePaneRow *self,
                                                   const gchar    *icon);

GdkRGBA *       finance_pane_row_get_color        (FinancePaneRow *self);

void            finance_pane_row_set_color        (FinancePaneRow *self,
                                                   const GdkRGBA  *color);

const gchar *   finance_pane_row_get_title        (FinancePaneRow *self);

void            finance_pane_row_set_title        (FinancePaneRow *self,
                                                   const gchar    *title);

const gchar *   finance_pane_row_get_amount       (FinancePaneRow *self);

void            finance_pane_row_set_amount       (FinancePaneRow *self,
                                                   const gchar    *amount);

gboolean        finance_pane_row_get_select       (FinancePaneRow *self);

void            finance_pane_row_set_select       (FinancePaneRow *self,
                                                   gboolean       selected);

G_END_DECLS

#endif /* __FINANCE_PANE_ROW_H__ */
