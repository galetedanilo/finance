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
  HdyPreferencesWindow parent_instance;

  /* The Widgets */
  GtkWidget   *radio_international;
  GtkWidget   *radio_local;
  GtkWidget   *spin_decimal_places;
  GtkWidget   *switch_amount;
  GtkWidget   *switch_currency_symbol;
  GtkWidget   *switch_date;

  GSettings   *settings;
};

G_DEFINE_TYPE (FinancePreferencesWindow, finance_preferences_window, HDY_TYPE_PREFERENCES_WINDOW)

static void
finance_preferences_window_dispose (GObject *object)
{
  FinancePreferencesWindow *self = FINANCE_PREFERENCES_WINDOW (object);

  g_clear_object (&self->settings);

  G_OBJECT_CLASS (finance_preferences_window_parent_class)->dispose (object);
}

static void
finance_preferences_window_class_init (FinancePreferencesWindowClass *klass)
{
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  G_OBJECT_CLASS (klass)->dispose = finance_preferences_window_dispose;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/pref/finance-preferences-window.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, radio_international);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, radio_local);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, spin_decimal_places);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, switch_amount);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, switch_currency_symbol);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, switch_date);
}

static void
finance_preferences_window_init (FinancePreferencesWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->settings = g_settings_new ("org.gnome.finance");

  g_settings_bind (self->settings, "date",
                   self->switch_date, "active",
                   G_SETTINGS_BIND_DEFAULT);

  g_settings_bind (self->settings, "amount",
                   self->switch_amount, "active",
                   G_SETTINGS_BIND_DEFAULT);

  g_settings_bind (self->settings, "decimal-places",
                   self->spin_decimal_places, "value",
                   G_SETTINGS_BIND_DEFAULT);

  g_settings_bind (self->settings, "currency-symbol",
                   self->switch_currency_symbol, "active",
                   G_SETTINGS_BIND_DEFAULT);
}

