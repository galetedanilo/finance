/* finance-pref-row-switch.h
 *
 * Copyright 2020 galetedanilo <galetedanilo@gmail.com>
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

#ifndef __FINANCE_PREF_ROW_SWITCH_H__
#define __FINANCE_PREF_ROW_SWITCH_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FINANCE_TYPE_PREF_ROW_SWITCH (finance_pref_row_switch_get_type())

G_DECLARE_FINAL_TYPE (FinancePrefRowSwitch, finance_pref_row_switch, FINANCE, PREF_ROW_SWITCH, GtkListBoxRow)

GtkWidget*    finance_pref_row_switch_new               (void);

const gchar*  finance_pref_row_switch_get_title         (FinancePrefRowSwitch *self);

void          finance_pref_row_switch_set_title         (FinancePrefRowSwitch *self,
                                                         const gchar          *title);

const gchar*  finance_pref_row_switch_get_text          (FinancePrefRowSwitch *self);

void          finance_pref_row_switch_set_text          (FinancePrefRowSwitch *self,
                                                         const gchar          *title);

gboolean      finance_pref_row_switch_get_active        (FinancePrefRowSwitch *self);

void          finance_pref_row_switch_set_active        (FinancePrefRowSwitch *self,
                                                         gboolean             active);
G_END_DECLS

#endif /* __FINANCE_PREF_ROW_SWITCH_H__ */
