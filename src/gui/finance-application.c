/* finance-application.c
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

#include <glib/gi18n.h>
#include "finance-config.h"

#include "finance-application.h"
#include "finance-preferences-window.h"
#include "finance-shortcuts-window.h"
#include "finance-window.h"

struct _FinanceApplication
{
  GtkApplication      parent_instance;

  GtkWidget           *window;
};

G_DEFINE_TYPE (FinanceApplication, finance_application, GTK_TYPE_APPLICATION)

enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

FinanceApplication *
finance_application_new (void)
{
  return g_object_new (FINANCE_TYPE_APPLICATION,
                       "resource-base-path", "/org/gnome/finance",
                       "application-id", "org.gnome.Finance",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}

static void
finance_application_finalize (GObject *object)
{
  FinanceApplication *self = (FinanceApplication *)object;

  G_OBJECT_CLASS (finance_application_parent_class)->finalize (object);
}

static void
finance_application_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  FinanceApplication *self = FINANCE_APPLICATION (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_application_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec)
{
  FinanceApplication *self = FINANCE_APPLICATION (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
on_about_dialog_response (GtkAboutDialog  *dialog,
                          gint            response,
                          gpointer        user_data)
{
  (void)user_data;

  if (response == GTK_RESPONSE_CANCEL)
    gtk_widget_destroy (GTK_WIDGET (dialog));
}


static void
finance_application_preferences (GSimpleAction  *aciton,
                                 GVariant       *parameter,
                                 gpointer       user_data)
{
  FinanceApplication *self = FINANCE_APPLICATION (user_data);

  GtkWidget *window;

  window = g_object_new (FINANCE_TYPE_PREFERENCES_WINDOW,
                         "transient-for", GTK_WINDOW (self->window),
                         "use-header-bar", TRUE,
                         "modal", TRUE,
                         "destroy-with-parent", TRUE,
                         "window-position", GTK_WIN_POS_CENTER_ON_PARENT,
                         NULL);


  gtk_window_present (GTK_WINDOW (window));
}

static void
finance_application_shortcuts (GSimpleAction  *action,
                               GVariant       *parameter,
                               gpointer       user_data)
{
  FinanceApplication *self = FINANCE_APPLICATION (user_data);

  GtkWidget *window;

  window = g_object_new (FINANCE_TYPE_SHORTCUTS_WINDOW,
                         "application", G_APPLICATION (self),
                         "transient-for", GTK_WINDOW (self->window),
                         "modal", TRUE,
                         "destroy-with-parent", TRUE,
                         "window-position", GTK_WIN_POS_CENTER_ON_PARENT,
                         NULL);


  gtk_window_present (GTK_WINDOW (window));
}

static void
finance_application_help (GSimpleAction *action,
                          GVariant      *parameter,
                          gpointer      user_data)
{

}

static void
finance_application_about (GSimpleAction  *action,
                           GVariant       *parameter,
                           gpointer       user_data)
{
  FinanceApplication *self = FINANCE_APPLICATION (user_data);

  (void)action;
  (void)parameter;

  GtkWidget *about_dialog;

  const gchar *authors[] = {
    "Danilo Fernandes Galete <galetedanilo@gmail.com>",
    NULL
  };

  const gchar *artists[] = {
    "Danilo Fernandes Galete <galetedanilo@gmail.com>",
    NULL
  };

  about_dialog = g_object_new (GTK_TYPE_ABOUT_DIALOG,
                               "transient-for", GTK_WINDOW (self->window),
                               "modal", TRUE,
                               "destroy-with-parent", TRUE,
                               "logo-icon-name", "org.gnome.Finance",
                               "program-name", _("GNOME Finance"),
                               "version", "1.0",
                               "comments", "Personal Finance Manager for GNOME",
                               "website-label", "Visit GNOME Finance website",
                               "website", "https://wiki.gnome.org/Apps/Finance",
                               "copyright", "Copyright \xC2\xA9 2019 - 2020, Danilo Fernandes Galete, et al",
                               "license-type", GTK_LICENSE_GPL_3_0,
                               "authors", authors,
                               "artists", artists,
                               "translator-credits", _("translator-credits"),/* The Translators Name */
                               NULL);

  g_signal_connect (about_dialog,
                    "response",
                    G_CALLBACK (on_about_dialog_response),
                    NULL);

  gtk_widget_show (about_dialog);
}

static void
finance_application_quit (GSimpleAction *action,
                          GVariant      *parameter,
                          gpointer      user_data)
{
  FinanceApplication *self = FINANCE_APPLICATION (user_data);

  (void)action;
  (void)parameter;

  gtk_widget_destroy (self->window);
}

static void
finance_application_activate (GApplication *app)
{
  FinanceApplication *self = FINANCE_APPLICATION (app);

  if (!self->window)
    {
      self->window = g_object_new (FINANCE_TYPE_WINDOW,
                                   "application", self,
                                   NULL);

      g_signal_connect (self->window,
                        "destroy",
                        G_CALLBACK (gtk_widget_destroy),
                        &self->window);

      gtk_widget_show (self->window);
    }

  gtk_window_present (GTK_WINDOW (self->window));
}

static void
finance_application_startup (GApplication *app)
{
  static const GActionEntry entries[] = {
    { "preferences", finance_application_preferences },
    { "shortcuts", finance_application_shortcuts },
    { "help", finance_application_help },
    { "about", finance_application_about },
    { "quit", finance_application_quit },

  };

  const gchar *preferences_accels[2]  = { "F3", NULL};
  const gchar *shortcuts_accels[2]    = { "F2", NULL};
  const gchar *help_accels[2]         = { "F1", NULL};
  const gchar *quit_accels[2]         = { "<Ctrl>Q", NULL};

  g_action_map_add_action_entries (G_ACTION_MAP (app),
                                   entries,
                                   G_N_ELEMENTS (entries),
                                   app);

  gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                         "app.preferences",
                                         preferences_accels);

  gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                         "app.shortcuts",
                                         shortcuts_accels);

  gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                         "app.help",
                                         help_accels);

  gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                         "app.quit",
                                         quit_accels);

  G_APPLICATION_CLASS (finance_application_parent_class)->startup (app);
}

static void
finance_application_class_init (FinanceApplicationClass *klass)
{
  G_OBJECT_CLASS (klass)->finalize = finance_application_finalize;
  G_OBJECT_CLASS (klass)->get_property = finance_application_get_property;
  G_OBJECT_CLASS (klass)->set_property = finance_application_set_property;

  G_APPLICATION_CLASS (klass)->activate = finance_application_activate;
  G_APPLICATION_CLASS (klass)->startup  = finance_application_startup;

}

static void
finance_application_init (FinanceApplication *self)
{
  g_set_application_name (_("Finance"));
}