/* finance-pref-row-switch.c
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

#include "finance-pref-row-switch.h"
#include "finance-pref-row.h"

struct _FinancePrefRowSwitch
{
  GtkListBoxRow parent_instance;

  /* The Widgets */
  GtkWidget     *title;
  GtkWidget     *text;
  GtkWidget     *pref_switch;

  GSettings     *settings;

  gchar         *key;
  gboolean      active;
};

enum {
  PROP_0,
  PROP_TITLE,
  PROP_TEXT,
  PROP_KEY,
  PROP_ACTIVE,
  N_PROPS
};

static GParamSpec *properties[N_PROPS] = { NULL, };

static void   finance_pref_row_interface_init     (FinancePrefRowInterface *iface);

G_DEFINE_TYPE_WITH_CODE (FinancePrefRowSwitch, finance_pref_row_switch, GTK_TYPE_LIST_BOX_ROW,
                         G_IMPLEMENT_INTERFACE (FINANCE_TYPE_PREF_ROW, finance_pref_row_interface_init))

static void
finance_pref_row_switch_change_preference (FinancePrefRowSwitch *self)
{
  gtk_switch_set_state (GTK_SWITCH (self->pref_switch), !self->active);
}

GtkWidget *
finance_pref_row_switch_new (void)
{
  return g_object_new (FINANCE_TYPE_PREF_ROW_SWITCH, NULL);
}

static void
finance_pref_row_switch_finalize (GObject *object)
{
  FinancePrefRowSwitch *self = (FinancePrefRowSwitch *)object;

  g_clear_pointer (&self->key, g_free);
  g_clear_object (&self->settings);

  G_OBJECT_CLASS (finance_pref_row_switch_parent_class)->finalize (object);
}

static void
finance_pref_row_switch_get_property (GObject    *object,
                                      guint       prop_id,
                                      GValue     *value,
                                      GParamSpec *pspec)
{
  FinancePrefRowSwitch *self = FINANCE_PREF_ROW_SWITCH (object);

  switch (prop_id)
    {
    case PROP_TITLE:
      g_value_set_string (value, finance_pref_row_switch_get_title (self));
      break;

    case PROP_TEXT:
      g_value_set_string (value, finance_pref_row_switch_get_text (self));
      break;

    case PROP_KEY:
      g_value_set_string (value, finance_pref_row_switch_get_key (self));
      break;

    case PROP_ACTIVE:
      g_value_set_boolean (value, finance_pref_row_switch_get_active (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pref_row_switch_set_property (GObject      *object,
                                      guint         prop_id,
                                      const GValue *value,
                                      GParamSpec   *pspec)
{
  FinancePrefRowSwitch *self = FINANCE_PREF_ROW_SWITCH (object);

  switch (prop_id)
    {
    case PROP_TITLE:
      finance_pref_row_switch_set_title (self, g_value_get_string (value));
      break;

    case PROP_TEXT:
      finance_pref_row_switch_set_text (self, g_value_get_string (value));
      break;

    case PROP_KEY:
      finance_pref_row_switch_set_key (self, g_value_get_string (value));
      break;

    case PROP_ACTIVE:
      finance_pref_row_switch_set_active (self, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pref_row_interface_init (FinancePrefRowInterface *iface)
{
  iface->change_preference  = finance_pref_row_switch_change_preference;
}

static void
finance_pref_row_switch_class_init (FinancePrefRowSwitchClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize      = finance_pref_row_switch_finalize;
  object_class->get_property  = finance_pref_row_switch_get_property;
  object_class->set_property  = finance_pref_row_switch_set_property;

  /**
   * FinancePrefRowSwitch::title:
   *
   * The title of the preference row
   */
  properties[PROP_TITLE] = g_param_spec_string ("title",
                                                "Title",
                                                "The title of the preference row",
                                                NULL,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowSwitch::text:
   *
   * The text of the preference row
   */
  properties[PROP_TEXT] = g_param_spec_string ("text",
                                               "Text",
                                               "The text of the preference row",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowSwitch::key:
   *
   * The key of the preference row
   */
  properties[PROP_KEY] = g_param_spec_string ("key",
                                              "Key",
                                              "The key of the preference row",
                                              NULL,
                                              G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowSwitch::active:
   *
   * Whether the preference row is in its on or off state
   */
  properties[PROP_ACTIVE] = g_param_spec_boolean ("active",
                                                  "Active",
                                                  "Whether the preference row is in its on or off state",
                                                  FALSE,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/pref/finance-pref-row-switch.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowSwitch, title);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowSwitch, text);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowSwitch, pref_switch);
}

static void
finance_pref_row_switch_init (FinancePrefRowSwitch *self)
{
  self->key     = NULL;
  self->active  = FALSE;

  gtk_widget_init_template (GTK_WIDGET (self));

  g_object_bind_property (self->pref_switch, "state",
                          self, "active",
                          G_BINDING_DEFAULT);
}

/**
 * finance_pref_row_switch_add_settings:
 * @self: a #FinancePrefRowSwitch instance.
 * @settings: a #GSettings
 *
 * Sets a #GSetting references in #FinancePrefRowSwitch.
 *
 * Since: 1.0
 */
void
finance_pref_row_switch_add_settings (FinancePrefRowSwitch *self,
                                      GSettings            *settings)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self));

  g_assert (G_IS_SETTINGS (settings));

  self->settings = g_object_ref (settings);

  g_settings_bind (self->settings, self->key,
                   self, "active",
                   G_SETTINGS_BIND_DEFAULT);
}

/**
 * finance_pref_row_switch_get_title:
 * @self: a #FinancePrefRowSwitch object.
 *
 * Returns the title from the label of the row.
 *
 * Returns: The title in the #FinancePrefRowSwitch, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pref_row_switch_get_title (FinancePrefRowSwitch *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->title));
}

/**
 * finance_pref_row_switch_set_title:
 * @self: a #FinancePrefRowSwitch instance.
 * @title: The title to set.
 *
 * Sets the title within the #FinancePrefRowSwitch, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pref_row_switch_set_title (FinancePrefRowSwitch *self,
                                   const gchar          *title)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self));

  gtk_label_set_text (GTK_LABEL (self->title), title);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TITLE]);
}

/**
 * finance_pref_row_switch_get_text:
 * @self: a #FinancePrefRowSwitch object.
 *
 * Returns the tex from the label of the row.
 *
 * Returns: The text in the #FinancePrefRowSwitch, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pref_row_switch_get_text (FinancePrefRowSwitch *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->text));
}

/**
 * finance_pref_row_switch_set_text:
 * @self: a #FinancePrefRowSwitch instance.
 * @title: The text to set.
 *
 * Sets the text within the #FinancePrefRowSwitch, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pref_row_switch_set_text (FinancePrefRowSwitch  *self,
                                  const gchar           *text)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self));

  gtk_label_set_text (GTK_LABEL (self->text), text);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TEXT]);
}

/**
 * finance_pref_row_switch_get_key:
 * @self: a #FinancePrefRowSwitch object.
 *
 * Returns the key of the row.
 *
 * Returns: The key in the #FinancePrefRowSwitch, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pref_row_switch_get_key (FinancePrefRowSwitch *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self), NULL);

  return self->key;
}

/**
 * finance_pref_row_switch_set_key:
 * @self: a #FinancePrefRowSwitch instance.
 * @key: The key to set.
 *
 * Sets the key within the #FinancePrefRowSwitch, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pref_row_switch_set_key (FinancePrefRowSwitch *self,
                                 const gchar          *key)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self));

  g_free (self->key);

  self->key = g_strdup (key);

  if (self->settings)
    g_settings_bind (self->settings, self->key,
                     self, "active",
                     G_SETTINGS_BIND_DEFAULT);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_KEY]);
}

/**
 * finance_pref_row_switch_get_active:
 * @self: a #FinancePrefRowSwitch object.
 *
 * Returns whether the preference is in its “on” or “off” state.
 *
 * Returns: #TRUE if the preference is active, and #FALSE otherwise
 *
 * Since: 1.0
 */
gboolean
finance_pref_row_switch_get_active (FinancePrefRowSwitch *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self), FALSE);

  return self->active;
}

/**
 * finance_pref_row_switch_set_active:
 * @self: a #FinancePrefRowSwitch instance.
 * @active: #TRUE if preference should be active, and #FALSE otherwise.
 *
 * Changes the state of #FinancePrefRowSwitch to the desired one.
 *
 * Since: 1.0
 */
void
finance_pref_row_switch_set_active (FinancePrefRowSwitch  *self,
                                    gboolean              active)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self));

  self->active = active;

  gtk_switch_set_state (GTK_SWITCH (self->pref_switch), active);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ACTIVE]);
}
