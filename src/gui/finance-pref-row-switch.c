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

#include "finance-pref-row-switch.h"

struct _FinancePrefRowSwitch
{
  GtkListBoxRow parent_instance;

  /* The Widgets */
  GtkWidget     *title;
  GtkWidget     *text;
  GtkWidget     *pref_switch;
};

G_DEFINE_TYPE (FinancePrefRowSwitch, finance_pref_row_switch, GTK_TYPE_LIST_BOX_ROW)

enum {
  PROP_0,
  PROP_TITLE,
  PROP_TEXT,
  PROP_ACTIVE,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static void
on_pref_switch_activate (GObject    *object,
                         GParamSpec *pspec,
                         gpointer   user_data)
{
  (void)object;
  (void)pspec;

  g_object_notify_by_pspec (G_OBJECT(user_data), properties[PROP_ACTIVE]);
}

GtkWidget *
finance_pref_row_switch_new (void)
{
  return g_object_new (FINANCE_TYPE_PREF_ROW_SWITCH, NULL);
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

    case PROP_ACTIVE:
      finance_pref_row_switch_set_active (self, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pref_row_switch_class_init (FinancePrefRowSwitchClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

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
                                                G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_EXPLICIT_NOTIFY);

  /**
   * FinancePrefRowSwitch::text:
   *
   * The text of the preference row
   */
  properties[PROP_TEXT] = g_param_spec_string ("text",
                                               "Text",
                                               "The text of the preference row",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_EXPLICIT_NOTIFY);

  /**
   * FinancePrefRowSwitch::active:
   *
   * Activate the preference row
   */
  properties[PROP_ACTIVE] = g_param_spec_boolean ("active",
                                                  "Active",
                                                  "Activate the preference row",
                                                  FALSE,
                                                  G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/gui/finance-pref-row-switch.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowSwitch, title);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowSwitch, text);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowSwitch, pref_switch);

  gtk_widget_class_bind_template_callback (widget_class, on_pref_switch_activate);
}

static void
finance_pref_row_switch_init (FinancePrefRowSwitch *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

/**
 * finance_pref_row_switch_get_title:
 * @self: a #FinancePrefRowSwitch instance.
 *
 * Fetches the title from the label of the row.
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
 * @self: a #FinancePrefRowSwitch object.
 * @title: The title you want to set
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
}

/**
 * finance_pref_row_switch_get_text:
 * @self: a #FinancePrefRowSwitch instance.
 *
 * Fetches the text from the label of the row.
 *
 * Returns: The text in the #FinancePrefRowSwitch, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar*
finance_pref_row_switch_get_text (FinancePrefRowSwitch *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->text));
}

/**
 * finance_pref_row_switch_set_text:
 * @self: a #FinancePrefRowSwitch object.
 * @title: The title you want to set
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
}

/**
 * finance_pref_row_switch_get_active:
 * @self: a #FinancePrefRowSwitch instance.
 *
 * Gets whether the #FinancePrefRowSwitch is in its “on” or “off” state.
 *
 * Returns: %TRUE if the #FinancePrefRowSwitch is active, and %FALSE otherwise.
 *
 * Since: 1.0
 */
gboolean
finance_pref_row_switch_get_active (FinancePrefRowSwitch *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self), FALSE);

  return gtk_switch_get_active (GTK_SWITCH (self->pref_switch));
}

/**
 * finance_pref_row_switch_set_active:
 * @self: a #FinancePrefRowSwitch object.
 * @is_active: %TRUE if preference should be active, and %FALSE otherwise.
 *
 * Changes the state of #FinancePrefRowSwitch to the desired one.
 *
 * Since: 1.0
 */
void
finance_pref_row_switch_set_active (FinancePrefRowSwitch  *self,
                                    gboolean              is_active)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_SWITCH (self));

  gtk_switch_set_active (GTK_SWITCH (self->pref_switch), is_active);
}

