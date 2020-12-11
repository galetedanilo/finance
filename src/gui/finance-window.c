/* finance-window.c
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

#include <glib/gi18n.h>
#include "finance-config.h"

#include "finance-window.h"

struct _FinanceWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkWidget           *toggle_button_panel;

  GtkWidget           *entry_date;
  GtkWidget           *entry_amount;
  GtkWidget           *revealer_panel;

  /* Window State */
  gint                width;
  gint                height;
  gint                pos_x;
  gint                pos_y;
  gboolean            maximized;
  gboolean            left_panel;

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

  self->left_panel = status;
}

static gboolean
on_window_state_event (GtkWidget  *widget,
                       GdkEvent   *event,
                       gpointer   user_data)
{
  FinanceWindow *self = FINANCE_WINDOW (widget);

  GdkEventWindowState *state;
  (void)user_data;

  state	= (GdkEventWindowState*) event;

  self->maximized = state->new_window_state & GDK_WINDOW_STATE_MAXIMIZED;

  return FALSE;
}

static gboolean
finance_window_configure_event (GtkWidget         *widget,
                                GdkEventConfigure *event)
{
  FinanceWindow *self = FINANCE_WINDOW (widget);

  gboolean resp;

  gtk_window_get_size (GTK_WINDOW (self),
                       &self->width,
                       &self->height);

  gtk_window_get_position (GTK_WINDOW (self),
                           &self->pos_x,
                           &self->pos_y);

  resp = GTK_WIDGET_CLASS (finance_window_parent_class)->configure_event (widget, event);

  return resp;
}

static void
finance_window_constructed (GObject *object)
{
  FinanceWindow *self = FINANCE_WINDOW (object);

  GSettings *settings;

  settings = g_settings_new ("org.gnome.Finance");

  self->maximized   = g_settings_get_boolean (settings, "maximized");
  self->left_panel  = g_settings_get_boolean (settings, "left-panel");

  if (self->maximized)
    {
      gtk_window_maximize (GTK_WINDOW (self));

    }
  else
    {
      g_settings_get (settings, "width", "i", &self->width);
      g_settings_get (settings, "height", "i", &self->height);
      g_settings_get (settings, "pos-x", "i", &self->pos_x);
      g_settings_get (settings, "pos-y", "i", &self->pos_y);

      gtk_window_set_default_size (GTK_WINDOW (self),
                                   self->width,
                                   self->height);

      gtk_window_move (GTK_WINDOW (self),
                       self->pos_x,
                       self->pos_y);

    }

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->toggle_button_panel),
                                self->left_panel);

  G_OBJECT_CLASS (finance_window_parent_class)->constructed (object);
}

static void
finance_window_finalize (GObject *object)
{
  FinanceWindow *self = FINANCE_WINDOW (object);

  GSettings *settings;

  settings = g_settings_new ("org.gnome.Finance");

  g_settings_set_boolean (settings, "maximized", self->maximized);
  g_settings_set_boolean (settings, "left-panel", self->left_panel);

  g_settings_set (settings, "width", "i", self->width);
  g_settings_set (settings, "height", "i", self->height);
  g_settings_set (settings, "pos-x", "i", self->pos_x);
  g_settings_set (settings, "pos-y", "i", self->pos_y);

  G_OBJECT_CLASS (finance_window_parent_class)->finalize (object);
}
static void
finance_window_dispose (GObject *object)
{
  FinanceWindow *self = FINANCE_WINDOW (object);

  G_OBJECT_CLASS (finance_window_parent_class)->dispose (object);
}

static void
finance_window_class_init (FinanceWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  g_type_ensure (FINANCE_TYPE_ENTRY_DATE);
  g_type_ensure (FINANCE_TYPE_ENTRY_MONETARY);

  widget_class->configure_event       = finance_window_configure_event;

  G_OBJECT_CLASS (klass)->constructed = finance_window_constructed;
  G_OBJECT_CLASS (klass)->finalize    = finance_window_finalize;
  G_OBJECT_CLASS (klass)->dispose     = finance_window_dispose;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Finance/gui/finance-window.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, toggle_button_panel);

  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, entry_date);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, entry_amount);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, revealer_panel);

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_left_panel_show_toggled);
  gtk_widget_class_bind_template_callback (widget_class, on_window_state_event);

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

  gtk_widget_init_template (GTK_WIDGET (self));

  gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                         "win.show-panel",
                                         show_panel);
}
