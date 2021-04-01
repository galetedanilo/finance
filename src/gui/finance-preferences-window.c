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
#include "finance-enums.h"

struct _FinancePreferencesWindow
{
  HdyPreferencesWindow parent_instance;

  /* The Widgets */
  GtkWidget   *action_row_international;
  GtkWidget   *action_row_local;
  GtkWidget   *radio_button_international;
  GtkWidget   *radio_button_local;
  GtkWidget   *spin_decimal_places;
  GtkWidget   *switch_amount;
  GtkWidget   *switch_currency_symbol;
  GtkWidget   *switch_date;

  GSettings   *settings;
};

G_DEFINE_TYPE (FinancePreferencesWindow, finance_preferences_window, HDY_TYPE_PREFERENCES_WINDOW)

static void
on_currency_symbol_international_toggled (GtkToggleButton *button,
                                          gpointer         user_data)
{
  FinancePreferencesWindow *self = FINANCE_PREFERENCES_WINDOW (user_data);

  (void)button;

  g_settings_set_enum (self->settings, "symbol-type", FINANCE_INTERNATIONAL);
}

static void
on_currency_symbol_local_toggled (GtkToggleButton *button,
                                  gpointer         user_data)
{
  FinancePreferencesWindow *self = FINANCE_PREFERENCES_WINDOW (user_data);

  (void)button;

  g_settings_set_enum (self->settings, "symbol-type", FINANCE_LOCAL);
}

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

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/gui/finance-preferences-window.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, action_row_international);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, action_row_local);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, radio_button_international);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, radio_button_local);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, spin_decimal_places);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, switch_amount);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, switch_currency_symbol);
  gtk_widget_class_bind_template_child (widget_class, FinancePreferencesWindow, switch_date);

  /* All signal */
  gtk_widget_class_bind_template_callback (widget_class, on_currency_symbol_international_toggled);
  gtk_widget_class_bind_template_callback (widget_class, on_currency_symbol_local_toggled);
}

static void
finance_preferences_window_init (FinancePreferencesWindow *self)
{
  FinanceSymbol symbol;

  gtk_widget_init_template (GTK_WIDGET (self));

  hdy_action_row_add_prefix (HDY_ACTION_ROW (self->action_row_international),
                             self->radio_button_international);

  hdy_action_row_add_prefix (HDY_ACTION_ROW (self->action_row_local),
                             self->radio_button_local);

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

  symbol = g_settings_get_enum (self->settings, "symbol-type");

  if (symbol == FINANCE_LOCAL)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->radio_button_local), TRUE);
  else
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->radio_button_international), TRUE);
}
