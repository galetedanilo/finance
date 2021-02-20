/* finance-shortcuts-window.c
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

#include "finance-shortcuts-window.h"

struct _FinanceShortcutsWindow
{
  GtkShortcutsWindow  parent_instance;
};

G_DEFINE_TYPE (FinanceShortcutsWindow, finance_shortcuts_window, GTK_TYPE_SHORTCUTS_WINDOW)

static void
finance_shortcuts_window_class_init (FinanceShortcutsWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/gui/finance-shortcuts-window.ui");
}

static void
finance_shortcuts_window_init (FinanceShortcutsWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
