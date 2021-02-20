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
  GVariant      *value;
  gboolean      active;

  gulong        handler;
};

enum {
  PROP_0,
  PROP_TITLE,
  PROP_TEXT,
  PROP_KEY,
  PROP_VALUE,
  PROP_ACTIVE,
  N_PROPS
};

static GParamSpec *properties[N_PROPS] = { NULL, };

static void   finance_pref_row_interface_init     (FinancePrefRowInterface *iface);

G_DEFINE_TYPE_WITH_CODE (FinancePrefRowCheck, finance_pref_row_check, GTK_TYPE_LIST_BOX_ROW,
                         G_IMPLEMENT_INTERFACE (FINANCE_TYPE_PREF_ROW, finance_pref_row_interface_init))

static void
active_preference (FinancePrefRowCheck *self)
{
  GVariant *value;

  value = g_settings_get_value (self->settings, self->key);

  if (g_variant_is_of_type (value, G_VARIANT_TYPE_BOOLEAN))
    {
      gboolean v1, v2;

      v1 = g_variant_get_boolean (self->value);
      v2 = g_settings_get_boolean (self->settings, self->key);

      gtk_revealer_set_reveal_child (GTK_REVEALER (self->pref_check), (v1 == v2));

      g_variant_unref (value);

      return;
    }
  
  /* G_TYPE_ENUM */
  if (g_variant_is_of_type (value, G_VARIANT_TYPE_STRING) &&
      g_variant_is_of_type (self->value, G_VARIANT_TYPE_INT32))
    {
      gint32 v1, v2;
      
      v1 = g_variant_get_int32 (self->value);
      v2 = g_settings_get_enum (self->settings, self->key);


      gtk_revealer_set_reveal_child (GTK_REVEALER (self->pref_check), (v1 == v2));

      g_variant_unref (value);

      return;
    }

  if (g_variant_is_of_type (value, G_VARIANT_TYPE_STRING))
    {
      const gchar *v1;
      gchar *v2;

      v1 = g_variant_get_string (self->value, NULL);
      v2 = g_settings_get_string (self->settings, self->key);

      gtk_revealer_set_reveal_child (GTK_REVEALER (self->pref_check), !g_strcmp0 (v1, v2));

      g_variant_unref (value);
      g_free (v2);

      return;
    }

  if (g_variant_is_of_type (value, G_VARIANT_TYPE_INT16))
    {
      gint16 v1, v2;

      v1 = g_variant_get_int16 (self->value);
      v2 = g_settings_get_int (self->settings, self->key);

      gtk_revealer_set_reveal_child (GTK_REVEALER (self->pref_check), (v1 == v2));

      g_variant_unref (value);

      return;
    }

  if (g_variant_is_of_type (value, G_VARIANT_TYPE_INT32))
    {
      gint32 v1, v2;

      v1 = g_variant_get_int32 (self->value);
      v2 = g_settings_get_int (self->settings, self->key);

      gtk_revealer_set_reveal_child (GTK_REVEALER (self->pref_check), (v1 == v2));

      g_variant_unref (value);

      return;
    }

  if (g_variant_is_of_type (value, G_VARIANT_TYPE_INT64))
    {
      gint64 v1, v2;

      v1 = g_variant_get_int64 (self->value);
      v2 = g_settings_get_int64 (self->settings, self->key);

      gtk_revealer_set_reveal_child (GTK_REVEALER (self->pref_check), (v1 == v2));

      g_variant_unref (value);

      return;
    }

  if (g_variant_is_of_type (value, G_VARIANT_TYPE_DOUBLE))
    {
      gdouble v1, v2;

      v1 = g_variant_get_double (self->value);
      v2 = g_settings_get_double (self->settings, self->key);

      gtk_revealer_set_reveal_child (GTK_REVEALER (self->pref_check), (v1 == v2));

      g_variant_unref (value);

      return;
    }
  
  g_variant_unref (value);
}

static void
change_settings (FinancePrefRowCheck *self)
{
  GVariant *value;

  value = g_settings_get_value (self->settings, self->key);

  if (g_variant_is_of_type (value, G_VARIANT_TYPE_BOOLEAN))
    {
      g_settings_set_boolean (self->settings,
                              self->key,
                              g_variant_get_boolean (self->value));

      g_variant_unref (value);

      return;
    }

  /* G_TYPE_ENUM */
  if (g_variant_is_of_type (value, G_VARIANT_TYPE_STRING) &&
      g_variant_is_of_type (self->value, G_VARIANT_TYPE_INT32))
    {
      g_settings_set_enum (self->settings,
                           self->key,
                           g_variant_get_int32 (self->value));

      g_variant_unref (value);

      return;
    }
  
  if (g_variant_is_of_type (value, G_VARIANT_TYPE_STRING))
    {
      g_settings_set_string (self->settings,
                             self->key,
                             g_variant_get_string (self->value, NULL));

      g_variant_unref (value);

      return;
    }

  if (g_variant_is_of_type (value, G_VARIANT_TYPE_INT16))
    {
      g_settings_set_int (self->settings,
                          self->key,
                          g_variant_get_int16 (self->value));

      g_variant_unref (value);

      return;
    }

  if (g_variant_is_of_type (value, G_VARIANT_TYPE_INT32))
    {
      g_settings_set_int (self->settings,
                          self->key,
                          g_variant_get_int32 (self->value));

      g_variant_unref (value);

      return;
    }

  if (g_variant_is_of_type (value, G_VARIANT_TYPE_INT64))
    {
      g_settings_set_int64 (self->settings,
                            self->key,
                            g_variant_get_int64 (self->value));

      g_variant_unref (value);

      return;
    }

  if (g_variant_is_of_type (value, G_VARIANT_TYPE_DOUBLE))
    {
      g_settings_set_double (self->settings,
                             self->key,
                             g_variant_get_double (self->value));

      g_variant_unref (value);

      return;
    }

  g_variant_unref (value);
}

static void
finance_pref_row_check_change_preference (FinancePrefRowCheck *self)
{
  gtk_revealer_set_reveal_child (GTK_REVEALER (self->pref_check), TRUE);
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

  g_clear_object (&self->settings);

  g_clear_pointer (&self->key, g_free);

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

    case PROP_VALUE:
      g_value_set_variant (value, finance_pref_row_check_get_value (self));
      break;

    case PROP_ACTIVE:
      g_value_set_boolean (value, finance_pref_row_check_get_active (self));
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

    case PROP_VALUE:
      finance_pref_row_check_set_value (self, value);
      break;

    case PROP_ACTIVE:
      finance_pref_row_check_set_active (self, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pref_row_interface_init (FinancePrefRowInterface *iface)
{
  iface->change_preference  = finance_pref_row_check_change_preference;
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

  /**
   * FinancePrefRowCheck::value:
   *
   * The key value of the preference row
   */
  properties[PROP_VALUE] = g_param_spec_variant ("value",
                                                 "Value",
                                                 "The key value of the preference row",
                                                 G_VARIANT_TYPE_ANY,
                                                 NULL,
                                                 G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowCheck::active:
   *
   * Whether the preference row is in its on or off state
   */
  properties[PROP_ACTIVE] = g_param_spec_boolean ("active",
                                                  "Active",
                                                  "Whether the preference row is in its on or off state",
                                                  FALSE,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/pref/finance-pref-row-check.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowCheck, title);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowCheck, text);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowCheck, pref_check);
}

static void
finance_pref_row_check_init (FinancePrefRowCheck *self)
{
  self->key     = NULL;
  self->active  = FALSE;

  gtk_widget_init_template (GTK_WIDGET (self));

  g_object_bind_property (self->pref_check,
                          "reveal-child",
                          self, "active",
                          G_BINDING_DEFAULT);
}

/**
 * finance_pref_row_check_add_settings:
 * @self: a #FinancePrefRowCheck instance.
 * @settings: a #GSettings
 *
 * Sets a #GSetting references in #FinancePrefRowCheck.
 *
 * Since: 1.0
 */
void
finance_pref_row_check_add_settings (FinancePrefRowCheck *self,
                                     GSettings           *settings)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_CHECK (self));

  gchar *signal_detail;

  g_assert (G_IS_SETTINGS (settings));

  self->settings = g_object_ref (settings);

  signal_detail = g_strdup_printf ("changed::%s", self->key);

  self->handler =  g_signal_connect_object (self->settings,
                                            signal_detail,
                                            G_CALLBACK (active_preference),
                                            self,
                                            G_CONNECT_SWAPPED);


  active_preference (self);

  g_free (signal_detail);
}

/**
 * finance_pref_row_check_get_title:
 * @self: a #FinancePrefRowCheck object.
 *
 * Returns the title from the label of the row.
 *
 * Returns: The title in the #FinancePrefRowCheck, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pref_row_check_get_title (FinancePrefRowCheck *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_CHECK (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->title));
}

/**
 * finance_pref_row_check_set_title:
 * @self: a #FinancePrefRowCheck instance.
 * @title: The title to set.
 *
 * Sets the title within the #FinancePrefRowCheck, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pref_row_check_set_title (FinancePrefRowCheck *self,
                                  const gchar         *title)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_CHECK (self));

  gtk_label_set_text (GTK_LABEL (self->title), title);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TITLE]);
}

/**
 * finance_pref_row_check_get_text:
 * @self: a #FinancePrefRowCheck object.
 *
 * Returns the tex from the label of the row.
 *
 * Returns: The text in the #FinancePrefRowCheck, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pref_row_check_get_text (FinancePrefRowCheck *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_CHECK (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->text));
}

/**
 * finance_pref_row_check_set_text:
 * @self: a #FinancePrefRowCheck instance.
 * @title: The text to set.
 *
 * Sets the text within the #FinancePrefRowCheck, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pref_row_check_set_text (FinancePrefRowCheck *self,
                                 const gchar         *text)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_CHECK (self));

  gtk_label_set_text (GTK_LABEL (self->text), text);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TEXT]);
}

/**
 * finance_pref_row_check_get_key:
 * @self: a #FinancePrefRowCheck object.
 *
 * Returns the key of the row.
 *
 * Returns: The key in the #FinancePrefRowCheck, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pref_row_check_get_key (FinancePrefRowCheck *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_CHECK (self), NULL);

  return self->key;
}

/**
 * finance_pref_row_check_set_key:
 * @self: a #FinancePrefRowCheck instance.
 * @key: The key to set.
 *
 * Sets the key within the #FinancePrefRowCheck, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pref_row_check_set_key (FinancePrefRowCheck *self,
                                const gchar         *key)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_CHECK (self));

  g_free (self->key);

  self->key = g_strdup (key);

  if (self->handler)
    {
      gchar *signal_detail;

      signal_detail = g_strdup_printf ("changed::%s", self->key);

      g_signal_handler_disconnect (self->settings, self->handler);

      self->handler =  g_signal_connect_object (self->settings,
                                                signal_detail,
                                                G_CALLBACK (active_preference),
                                                self,
                                                G_CONNECT_SWAPPED);

      g_free (signal_detail);
    }


  if (self->settings)
    active_preference (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_KEY]);
}

/**
 * finance_pref_row_check_get_value:
 * @self: a #FinancePrefRowCheck instance.
 *
 * Returns the key value of the preference row.
 *
 * Returns: The key value of the #FinancePrefRowCheck, or %NULL.
 * This #GVariant points to internally allocated storage in the object
 * and must not be freed, modified or stored
 *
 * Since:1.0
 */
GVariant *
finance_pref_row_check_get_value (FinancePrefRowCheck *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_CHECK (self), NULL);

  return self->value;
}

/**
 * finance_pref_row_check_set_value:
 * @self: a #FinancePrefRowCheck object.
 * @value: a #GValue.
 *
 * Sets the value within the #FinancePrefRowCheck, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pref_row_check_set_value (FinancePrefRowCheck *self,
                                  const GValue        *value)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_CHECK (self));

  if (self->value)
    g_variant_unref (self->value);

  self->value = g_value_dup_variant (value);

  if (self->settings)
    active_preference (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_VALUE]);
}

/**
 * finance_pref_row_check_get_active:
 * @self: a #FinancePrefRowCheck object.
 *
 * Returns whether the preference is in its “on” or “off” state.
 *
 * Returns: #TRUE if the preference is active, and #FALSE otherwise
 *
 * Since: 1.0
 */
gboolean
finance_pref_row_check_get_active (FinancePrefRowCheck *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_CHECK (self), FALSE);

  return self->active;
}

/**
 * finance_pref_row_check_set_active:
 * @self: a #FinancePrefRowCheck instance.
 * @active: #TRUE if preference should be active, and #FALSE otherwise.
 *
 * Changes the state of #FinancePrefRowCheck to the desired one.
 *
 * Since: 1.0
 */
void
finance_pref_row_check_set_active (FinancePrefRowCheck *self,
                                   gboolean             active)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_CHECK (self));

  self->active = active;

  gtk_revealer_set_reveal_child (GTK_REVEALER (self->pref_check), self->active);

  if (self->active)
    change_settings (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ACTIVE]);
}
