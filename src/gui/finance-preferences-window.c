/* finance-preferences-window.c
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

#include "finance-preferences-window.h"

struct _FinancePreferencesWindow
{
  GtkDialog   parent_instance;
};

G_DEFINE_TYPE (FinancePreferencesWindow, finance_preferences_window, GTK_TYPE_DIALOG)

static void
finance_preferences_window_class_init (FinancePreferencesWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Finance/gui/finance-preferences-window.ui");
}

static void
finance_preferences_window_init (FinancePreferencesWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}