/* finance-pref-box.h
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

#ifndef __FINANCE_PREF_BOX_H__
#define __FINANCE_PREF_BOX_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FINANCE_TYPE_PREF_BOX (finance_pref_box_get_type ())

G_DECLARE_FINAL_TYPE (FinancePrefBox, finance_pref_box, FINANCE, PREF_BOX, GtkBox)

GtkWidget *       finance_pref_box_new        (void);

const gchar *     finance_pref_box_get_title  (FinancePrefBox *self);

void              finance_pref_box_set_title  (FinancePrefBox *self,
                                               const gchar    *title);

G_END_DECLS

#endif /* __FINANCE_PREF_BOX_H__ */
