/* finance-window.h
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
 */

#ifndef __FINANCE_WINDOW_H__
#define __FINANCE_WINDOW_H__

#include <gtk/gtk.h>

#include "finance-transaction.h"

G_BEGIN_DECLS

#define FINANCE_TYPE_WINDOW (finance_window_get_type())

G_DECLARE_FINAL_TYPE (FinanceWindow, finance_window, FINANCE, WINDOW, GtkApplicationWindow)

G_END_DECLS

#endif /* __FINANCE_WINDOW_H__ */
