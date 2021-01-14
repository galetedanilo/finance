/* finance-pref-row-check.c
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

#include "finance-pref-row-check.h"
#include "finance-pref-row.h"

struct _FinancePrefRowCheck
{
  GtkListBoxRow parent_instance;

  /* The Widgets */
  GtkWidget     *title;
  GtkWidget     *text;
  GtkWidget     *pref_check;

  GSettings     *settings;

  gchar         *key;
};

enum {
  PROP_0,
  PROP_TITLE,
  PROP_TEXT,
  PROP_KEY,
  N_PROPS
};

static GParamSpec *properties[N_PROPS] = { NULL, };

static void   finance_pref_row_interface_init     (FinancePrefRowInterface *iface);

G_DEFINE_TYPE_WITH_CODE (FinancePrefRowCheck, finance_pref_row_check, GTK_TYPE_LIST_BOX_ROW,
                         G_IMPLEMENT_INTERFACE (FINANCE_TYPE_PREF_ROW, finance_pref_row_interface_init))

static const gchar *
finance_pref_row_check_get_title (FinancePrefRowCheck *self)
{
  return gtk_label_get_text (GTK_LABEL (self->title));
}

static void
finance_pref_row_check_set_title (FinancePrefRowCheck *self,
                                  const gchar         *title)
{
  gtk_label_set_text (GTK_LABEL (self->title), title);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TITLE]);
}

static const gchar *
finance_pref_row_check_get_text (FinancePrefRowCheck *self)
{
  return gtk_label_get_text (GTK_LABEL (self->text));
}

static void
finance_pref_row_check_set_text (FinancePrefRowCheck *self,
                                 const gchar         *text)
{
  gtk_label_set_text (GTK_LABEL (self->text), text);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TEXT]);
}

static const gchar *
finance_pref_row_check_get_key (FinancePrefRowCheck *self)
{
  return self->key;
}

static void
finance_pref_row_check_set_key (FinancePrefRowCheck *self,
                                const gchar         *key)
{
  g_free (self->key);

  self->key = g_strdup (key);

  if (self->settings)
    g_settings_bind (self->settings, self->key,
                     self->pref_check, "reveal-child",
                     G_SETTINGS_BIND_DEFAULT);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_KEY]);
}

static void
finance_pref_row_check_change_preference (FinancePrefRowCheck *self)
{
  gtk_revealer_set_reveal_child (GTK_REVEALER (self->pref_check),
                                 !gtk_revealer_get_reveal_child (GTK_REVEALER (self->pref_check)));
}

static void
finance_pref_row_check_add_settings (FinancePrefRowCheck *self,
                                     GSettings           *settings)
{
  g_assert (G_IS_SETTINGS (settings));

  self->settings = g_object_ref (settings);

  g_settings_bind (self->settings, self->key,
                   self->pref_check, "reveal-child",
                   G_SETTINGS_BIND_DEFAULT);
}

GtkWidget *
finance_pref_row_check_new (void)
{
  return g_object_new (FINANCE_TYPE_PREF_ROW_CHECK, NULL);
}

static void
finance_pref_row_check_finalize (GObject *object)
{
  FinancePrefRowCheck *self = (FinancePrefRowCheck *)object;

  g_clear_pointer (&self->key, g_free);
  g_clear_object (&self->settings);

  G_OBJECT_CLASS (finance_pref_row_check_parent_class)->finalize (object);
}

static void
finance_pref_row_check_get_property (GObject    *object,
                                     guint       prop_id,
                                     GValue     *value,
                                     GParamSpec *pspec)
{
  FinancePrefRowCheck *self = FINANCE_PREF_ROW_CHECK (object);

  switch (prop_id)
    {
    case PROP_TITLE:
      g_value_set_string (value, finance_pref_row_check_get_title (self));
      break;

    case PROP_TEXT:
      g_value_set_string (value, finance_pref_row_check_get_text (self));
      break;

    case PROP_KEY:
      g_value_set_string (value, finance_pref_row_check_get_key (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pref_row_check_set_property (GObject      *object,
                                     guint         prop_id,
                                     const GValue *value,
                                     GParamSpec   *pspec)
{
  FinancePrefRowCheck *self = FINANCE_PREF_ROW_CHECK (object);

  switch (prop_id)
    {
    case PROP_TITLE:
      finance_pref_row_check_set_title (self, g_value_get_string (value));
      break;

    case PROP_TEXT:
      finance_pref_row_check_set_text (self, g_value_get_string (value));
      break;

    case PROP_KEY:
      finance_pref_row_check_set_key (self, g_value_get_string (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pref_row_interface_init (FinancePrefRowInterface *iface)
{
  iface->get_title          = finance_pref_row_check_get_title;
  iface->set_title          = finance_pref_row_check_set_title;
  iface->get_text           = finance_pref_row_check_get_text;
  iface->set_text           = finance_pref_row_check_set_text;
  iface->get_key            = finance_pref_row_check_get_key;
  iface->set_key            = finance_pref_row_check_set_key;
  iface->change_preference  = finance_pref_row_check_change_preference;
  iface->add_settings       = finance_pref_row_check_add_settings;
}

static void
finance_pref_row_check_class_init (FinancePrefRowCheckClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize      = finance_pref_row_check_finalize;
  object_class->get_property  = finance_pref_row_check_get_property;
  object_class->set_property  = finance_pref_row_check_set_property;

  /**
   * FinancePrefRowCheck::title:
   *
   * The title of the preference row
   */
  properties[PROP_TITLE] = g_param_spec_string ("title",
                                                "Title",
                                                "The title of the preference row",
                                                NULL,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowCheck::text:
   *
   * The text of the preference row
   */
  properties[PROP_TEXT] = g_param_spec_string ("text",
                                               "Text",
                                               "The text of the preference row",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowCheck::key:
   *
   * The key of the preference row
   */
  properties[PROP_KEY] = g_param_spec_string ("key",
                                              "Key",
                                              "The key of the preference row",
                                              NULL,
                                              G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/gui/finance-pref-row-check.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowCheck, title);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowCheck, text);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowCheck, pref_check);
}

static void
finance_pref_row_check_init (FinancePrefRowCheck *self)
{
  self->key         = NULL;

  gtk_widget_init_template (GTK_WIDGET (self));
}

