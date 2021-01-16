/* finance-pref-row-spin.h
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

#ifndef __FINANCE_PREF_ROW_SPIN_H__
#define __FINANCE_PREF_RWO_SPIN_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FINANCE_TYPE_PREF_ROW_SPIN (finance_pref_row_spin_get_type ())

G_DECLARE_FINAL_TYPE (FinancePrefRowSpin, finance_pref_row_spin, FINANCE, PREF_ROW_SPIN, GtkListBoxRow)

GtkWidget *     finance_pref_row_spin_new           (void);

gdouble         finance_pref_row_spin_get_min_num   (FinancePrefRowSpin *self);

void            finance_pref_row_spin_set_min_num   (FinancePrefRowSpin *self,
                                                     gdouble            value);

gdouble         finance_pref_row_spin_get_max_num   (FinancePrefRowSpin *self);

void            finance_pref_row_spin_set_max_num   (FinancePrefRowSpin *self,
                                                     gdouble            value);

gdouble         finance_pref_row_spin_get_increment (FinancePrefRowSpin *self);

void            finance_pref_row_spin_set_increment (FinancePrefRowSpin *self,
                                                     gdouble            value);

gdouble         finance_pref_row_spin_get_display   (FinancePrefRowSpin *self);

void            finance_pref_row_spin_set_display   (FinancePrefRowSpin *self,
                                                     gdouble            value);

gdouble         finance_pref_row_spin_get_value     (FinancePrefRowSpin *self);

void            finance_pref_row_spin_set_value     (FinancePrefRowSpin *self,
                                                     gdouble            value);

G_END_DECLS

#endif /* __FINANCE_PREF_ROW_SPIN_H__ */
