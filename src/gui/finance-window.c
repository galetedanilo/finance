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

  /* Window State */
  gint                width;
  gint                height;
  gint                pos_x;
  gint                pos_y;
  gboolean            maximized;

};

G_DEFINE_TYPE (FinanceWindow, finance_window, GTK_TYPE_APPLICATION_WINDOW)

static void
finance_window_constructed (GObject *object)
{
  FinanceWindow *self = FINANCE_WINDOW (object);

  GSettings     *settings;

  settings = g_settings_new ("org.gnome.Finance");

  self->maximized = g_settings_get_boolean (settings, "maximized");

  g_settings_get (settings, "width", "i", &self->width);
  g_settings_get (settings, "height", "i", &self->height);
  g_settings_get (settings, "pos-x", "i", &self->pos_x);
  g_settings_get (settings, "pos-y", "i", &self->pos_y);

  if (self->maximized)
    {
      gtk_window_maximize (GTK_WINDOW (self));

    }
  else
    {
      gtk_window_set_default_size (GTK_WINDOW (self),
                                   self->width,
                                   self->height);

      gtk_window_move (GTK_WINDOW (self),
                       self->pos_x,
                       self->pos_y);

    }

  G_OBJECT_CLASS (finance_window_parent_class)->constructed (object);
}

static void
finance_window_finalize (GObject *object)
{
  FinanceWindow *self = FINANCE_WINDOW (object);

  GSettings     *settings;

  settings = g_settings_new ("org.gnome.Finance");

  g_settings_set_boolean (settings, "maximized", self->maximized);

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

  G_OBJECT_CLASS (klass)->constructed = finance_window_constructed;
  G_OBJECT_CLASS (klass)->finalize    = finance_window_finalize;
  G_OBJECT_CLASS (klass)->dispose     = finance_window_dispose;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Finance/gui/finance-window.ui");
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, header_bar);

}

static void
finance_window_init (FinanceWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
