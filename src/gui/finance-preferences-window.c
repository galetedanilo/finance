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

#include "finance-config.h"

#include "finance-preferences-window.h"

struct _FinancePreferencesWindow
{
  GtkDialog   parent_instance;

  GtkWidget   *combo_box_date;

  GSettings   *settings;

  gboolean    date_formatting;
};

G_DEFINE_TYPE (FinancePreferencesWindow, finance_preferences_window, GTK_TYPE_DIALOG)

static void
on_combo_box_date_changed (GtkComboBox  *widget,
                           gpointer     user_data)
{
  FinancePreferencesWindow *self = FINANCE_PREFERENCES_WINDOW (user_data);

  self->date_formatting = gtk_combo_box_get_active (widget);
}

static void
finance_preferences_window_constructed (GObject *object)
{
  FinancePreferencesWindow *self = FINANCE_PREFERENCES_WINDOW (object);

  self->date_formatting = g_settings_get_boolean (self->settings, "date-formatting");

  gtk_combo_box_set_active (GTK_COMBO_BOX (self->combo_box_date), self->date_formatting);

  G_OBJECT_CLASS (finance_preferences_window_parent_class)->constructed (object);
}

static void
finance_preferences_window_finalize (GObject *object)
{
  FinancePreferencesWindow *self = FINANCE_PREFERENCES_WINDOW (object);

  g_settings_set_boolean (self->settings, "date-formatting", self->date_formatting);

  G_OBJECT_CLASS (finance_preferences_window_parent_class)->finalize (object);
}

static void
finance_preferences_window_class_init (FinancePreferencesWindowClass *klass)
{
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  G_OBJECT_CLASS (klass)->constructed = finance_preferences_window_constructed;
  G_OBJECT_CLASS (klass)->finalize    = finance_preferences_window_finalize;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Finance/gui/finance-preferences-window.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, combo_box_date);

  /* All Signals */
  gtk_widget_class_bind_template_callback (widget_class, on_combo_box_date_changed);
}

static void
finance_preferences_window_init (FinancePreferencesWindow *self)
{
  self->settings = g_settings_new ("org.gnome.Finance");

  gtk_widget_init_template (GTK_WIDGET (self));
}
