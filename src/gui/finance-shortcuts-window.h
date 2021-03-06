/* finance-shortcuts-window.h
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

#ifndef __FINANCE_SHORTCUTS_WINDOW_H__
#define __FINANCE_SHORTCUTS_WINDOW_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FINANCE_TYPE_SHORTCUTS_WINDOW (finance_shortcuts_window_get_type())

G_DECLARE_FINAL_TYPE (FinanceShortcutsWindow, finance_shortcuts_window, FINANCE, SHORTCUTS_WINDOW, GtkShortcutsWindow)

G_END_DECLS

#endif /* __FINANCE_SHORTCUTS_WINDOW_H__ */
