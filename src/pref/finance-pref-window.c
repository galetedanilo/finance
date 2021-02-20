/* finance-pref-window.c
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

#include "finance-pref-window.h"

struct _FinancePrefWindow
{
  GtkWindow   parent_instance;

  /* The Widgets */
  GtkWidget   *date;
  GtkWidget   *amount;
  GtkWidget   *decimal_places;
  GtkWidget   *currency_symbol;
  GtkWidget   *local_symbol;
  GtkWidget   *international_symbol;


  GSettings   *settings;
};

G_DEFINE_TYPE (FinancePrefWindow, finance_pref_window, GTK_TYPE_WINDOW)

static void
finance_pref_window_dispose (GObject *object)
{
  FinancePrefWindow *self = FINANCE_PREF_WINDOW (object);

  g_clear_object (&self->settings);

  G_OBJECT_CLASS (finance_pref_window_parent_class)->dispose (object);
}

static void
finance_pref_window_class_init (FinancePrefWindowClass *klass)
{
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  g_type_ensure (FINANCE_TYPE_PREF_BOX);
  g_type_ensure (FINANCE_TYPE_PREF_LIST_BOX);
  g_type_ensure (FINANCE_TYPE_PREF_ROW_CHECK);
  g_type_ensure (FINANCE_TYPE_PREF_ROW_SPIN);
  g_type_ensure (FINANCE_TYPE_PREF_ROW_SWITCH);

  G_OBJECT_CLASS (klass)->dispose     = finance_pref_window_dispose;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/pref/finance-pref-window.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePrefWindow, date);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefWindow, amount);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefWindow, decimal_places);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefWindow, currency_symbol);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefWindow, local_symbol);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefWindow, international_symbol);
}

static void
finance_pref_window_init (FinancePrefWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->settings = g_settings_new ("org.gnome.finance");

  finance_pref_row_switch_add_settings (FINANCE_PREF_ROW_SWITCH (self->date), self->settings);
  finance_pref_row_switch_add_settings (FINANCE_PREF_ROW_SWITCH (self->amount), self->settings);
  finance_pref_row_switch_add_settings (FINANCE_PREF_ROW_SWITCH (self->currency_symbol), self->settings);

  finance_pref_row_spin_add_settings (FINANCE_PREF_ROW_SPIN (self->decimal_places), self->settings);

  finance_pref_row_check_add_settings (FINANCE_PREF_ROW_CHECK (self->local_symbol), self->settings);
  finance_pref_row_check_add_settings (FINANCE_PREF_ROW_CHECK (self->international_symbol), self->settings);

  g_object_bind_property (self->currency_symbol, "active",
                          self->local_symbol, "sensitive",
                          G_BINDING_DEFAULT);

  g_object_bind_property (self->currency_symbol, "active",
                          self->international_symbol, "sensitive",
                          G_BINDING_DEFAULT);
}

