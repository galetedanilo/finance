/* finance-window.c
 *
 * Copyright 2020 galetedanilo
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

#include "finance-config.h"

#include "finance-window.h"

struct _FinanceWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkWidget           *toggle_button_panel;

  GtkWidget           *transaction;
  GtkWidget           *revealer_panel;

  GSettings   *settings;

  /* Window State */
  gint                width;
  gint                height;
};

G_DEFINE_TYPE (FinanceWindow, finance_window, GTK_TYPE_APPLICATION_WINDOW)

static void
on_left_panel_show_action_activated (GSimpleAction  *action,
                                     GVariant       *parameter,
                                     gpointer       user_data)
{
  FinanceWindow *self = FINANCE_WINDOW (user_data);

  (void)action;
  (void)parameter;

  gboolean status = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self->toggle_button_panel));

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->toggle_button_panel), !status);

}

static void
on_left_panel_show_toggled (GtkToggleButton *toggle_button,
                            gpointer        user_data)
{
  FinanceWindow *self = FINANCE_WINDOW (user_data);

  gboolean status = gtk_toggle_button_get_active (toggle_button);

  gtk_revealer_set_reveal_child (GTK_REVEALER (self->revealer_panel), status);

}


static void
finance_window_constructed (GObject *object)
{
  FinanceWindow *self = FINANCE_WINDOW (object);


  g_settings_bind (self->settings, "left-panel",
                   self->toggle_button_panel, "active",
                   G_SETTINGS_BIND_DEFAULT);

  G_OBJECT_CLASS (finance_window_parent_class)->constructed (object);
}

static void
finance_window_finalize (GObject *object)
{
  FinanceWindow *self = FINANCE_WINDOW (object);


  G_OBJECT_CLASS (finance_window_parent_class)->finalize (object);
}
static void
finance_window_dispose (GObject *object)
{
  FinanceWindow *self = FINANCE_WINDOW (object);

  g_clear_object (&self->settings);

  G_OBJECT_CLASS (finance_window_parent_class)->dispose (object);
}

static void
finance_window_class_init (FinanceWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  g_type_ensure (FINANCE_TYPE_TRANSACTION);

  G_OBJECT_CLASS (klass)->constructed = finance_window_constructed;
  G_OBJECT_CLASS (klass)->finalize    = finance_window_finalize;
  G_OBJECT_CLASS (klass)->dispose     = finance_window_dispose;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/gui/finance-window.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, toggle_button_panel);

  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, transaction);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, revealer_panel);

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_left_panel_show_toggled);

}

static void
finance_window_init (FinanceWindow *self)
{
  GApplication *app = g_application_get_default ();

  static const GActionEntry entries[] = {
    { "show-panel", on_left_panel_show_action_activated }

  };

  const gchar *show_panel[] = { "<CTRL>R", NULL};

  g_action_map_add_action_entries (G_ACTION_MAP (self),
                                   entries,
                                   G_N_ELEMENTS (entries),
                                   self);

  self->settings = g_settings_new ("org.gnome.finance");

  gtk_widget_init_template (GTK_WIDGET (self));

  gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                         "win.show-panel",
                                         show_panel);
}
