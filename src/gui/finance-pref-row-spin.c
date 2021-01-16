/* finance-pref-row-spin.c
 *
 * Copyright 2021 galetedanilo <galetedanilo@gmail.com>
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

#include "finance-pref-row-spin.h"
#include "finance-pref-row.h"

struct _FinancePrefRowSpin
{
  GtkListBoxRow parent_instance;

  /* The Widgets */
  GtkWidget     *title;
  GtkWidget     *text;
  GtkWidget     *pref_spin;

  GSettings     *settings;

  GtkAdjustment *adjustment;

  gchar         *key;
};

enum {
  PROP_0,
  PROP_TITLE,
  PROP_TEXT,
  PROP_KEY,
  PROP_MIN_NUM,
  PROP_MAX_NUM,
  PROP_INCREMENT,
  PROP_VALUE,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static void   finance_pref_row_interface_init       (FinancePrefRowInterface *iface);

G_DEFINE_TYPE_WITH_CODE (FinancePrefRowSpin, finance_pref_row_spin, GTK_TYPE_LIST_BOX_ROW,
                         G_IMPLEMENT_INTERFACE (FINANCE_TYPE_PREF_ROW, finance_pref_row_interface_init))

static const gchar *
finance_pref_row_spin_get_title (FinancePrefRowSpin *self)
{
  return gtk_label_get_text (GTK_LABEL (self->title));
}

static void
finance_pref_row_spin_set_title (FinancePrefRowSpin *self,
                                 const gchar         *title)
{
  gtk_label_set_text (GTK_LABEL (self->title), title);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TITLE]);
}

static const gchar *
finance_pref_row_spin_get_text (FinancePrefRowSpin *self)
{
  return gtk_label_get_text (GTK_LABEL (self->text));
}

static void
finance_pref_row_spin_set_text (FinancePrefRowSpin *self,
                                const gchar        *text)
{
  gtk_label_set_text (GTK_LABEL (self->text), text);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TEXT]);
}

static const gchar *
finance_pref_row_spin_get_key (FinancePrefRowSpin *self)
{
  return self->key;
}

static void
finance_pref_row_spin_set_key (FinancePrefRowSpin *self,
                               const gchar        *key)
{
  g_free (self->key);

  self->key = g_strdup (key);

  if (self->settings)
    g_settings_bind (self->settings, self->key,
                     self->pref_spin, "value",
                     G_SETTINGS_BIND_DEFAULT);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_KEY]);
}

static void
finance_pref_row_spin_change_preference (FinancePrefRowSpin *self)
{

}

static void
finance_pref_row_spin_add_settings (FinancePrefRowSpin *self,
                                    GSettings          *settings)
{
  g_assert (G_IS_SETTINGS (settings));

  self->settings = g_object_ref (settings);

  g_settings_bind (self->settings, self->key,
                   self->pref_spin, "value",
                   G_SETTINGS_BIND_DEFAULT);
}

GtkWidget *
finance_pref_row_spin_new (void)
{
  return g_object_new (FINANCE_TYPE_PREF_ROW_SPIN, NULL);
}

static void
finance_pref_row_spin_finalize (GObject *object)
{
  FinancePrefRowSpin *self = (FinancePrefRowSpin *)object;

  g_clear_pointer (&self->key, g_free);
  g_clear_object (&self->settings);

  G_OBJECT_CLASS (finance_pref_row_spin_parent_class)->finalize (object);
}

static void
finance_pref_row_spin_get_property (GObject    *object,
                                    guint       prop_id,
                                    GValue     *value,
                                    GParamSpec *pspec)
{
  FinancePrefRowSpin *self = FINANCE_PREF_ROW_SPIN (object);

  switch (prop_id)
    {
    case PROP_TITLE:
      g_value_set_string (value, finance_pref_row_spin_get_title (self));
      break;

    case PROP_TEXT:
      g_value_set_string (value, finance_pref_row_spin_get_text (self));
      break;

    case PROP_KEY:
      g_value_set_string (value, finance_pref_row_spin_get_key (self));
      break;

    case PROP_MIN_NUM:
      g_value_set_double (value, finance_pref_row_spin_get_min_num (self));
      break;

    case PROP_MAX_NUM:
      g_value_set_double (value, finance_pref_row_spin_get_max_num (self));
      break;

    case PROP_INCREMENT:
      g_value_set_double (value, finance_pref_row_spin_get_increment (self));
      break;

    case PROP_VALUE:
      g_value_set_double (value, finance_pref_row_spin_get_value (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pref_row_spin_set_property (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec)
{
  FinancePrefRowSpin *self = FINANCE_PREF_ROW_SPIN (object);

  switch (prop_id)
    {
    case PROP_TITLE:
      finance_pref_row_spin_set_title (self, g_value_get_string (value));
      break;

    case PROP_TEXT:
      finance_pref_row_spin_set_text (self, g_value_get_string (value));
      break;

    case PROP_KEY:
      finance_pref_row_spin_set_key (self, g_value_get_string (value));
      break;

    case PROP_MIN_NUM:
      finance_pref_row_spin_set_min_num (self, g_value_get_double (value));
      break;

    case PROP_MAX_NUM:
      finance_pref_row_spin_set_max_num (self, g_value_get_double (value));
      break;

    case PROP_INCREMENT:
      finance_pref_row_spin_set_increment (self, g_value_get_double (value));
      break;

    case PROP_VALUE:
      finance_pref_row_spin_set_value (self, g_value_get_double (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pref_row_interface_init (FinancePrefRowInterface *iface)
{
  iface->get_title          = finance_pref_row_spin_get_title;
  iface->set_title          = finance_pref_row_spin_set_title;
  iface->get_text           = finance_pref_row_spin_get_text;
  iface->set_text           = finance_pref_row_spin_set_text;
  iface->get_key            = finance_pref_row_spin_get_key;
  iface->set_key            = finance_pref_row_spin_set_key;
  iface->change_preference  = finance_pref_row_spin_change_preference;
  iface->add_settings       = finance_pref_row_spin_add_settings;
}

static void
finance_pref_row_spin_class_init (FinancePrefRowSpinClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize      = finance_pref_row_spin_finalize;
  object_class->get_property  = finance_pref_row_spin_get_property;
  object_class->set_property  = finance_pref_row_spin_set_property;

  /**
   * FinancePrefRowSpin::title:
   *
   * The title of the preference row
   */
  properties[PROP_TITLE] = g_param_spec_string ("title",
                                                "Title",
                                                "The title of the preference row",
                                                NULL,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowSpin::text:
   *
   * The text of the preference row
   */
  properties[PROP_TEXT] = g_param_spec_string ("text",
                                               "Text",
                                               "The text of the preference row",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowSpin::key:
   *
   * The key of the preference row
   */
  properties[PROP_KEY] = g_param_spec_string ("key",
                                              "Key",
                                              "The key of the preference row",
                                              NULL,
                                              G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowSpin::min-num:
   *
   * The minimum value in the #GtkSpinButton
   */
  properties[PROP_MIN_NUM] = g_param_spec_double ("min-num",
                                                  "Minimum value",
                                                  "The minimum value",
                                                  -G_MINDOUBLE,
                                                  G_MAXDOUBLE,
                                                  0.0,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowSpin::max-num:
   *
   * The maximum value in the #GtkSpinButton
   */
  properties[PROP_MAX_NUM] = g_param_spec_double ("max-num",
                                                  "Maximum value",
                                                  "The maximum value",
                                                  -G_MINDOUBLE,
                                                  G_MAXDOUBLE,
                                                  0.0,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowSpin::increment:
   *
   * The step increment value
   */
  properties[PROP_INCREMENT] = g_param_spec_double ("increment",
                                                    "Increment value",
                                                    "The increment value",
                                                    -G_MINDOUBLE,
                                                    G_MAXDOUBLE,
                                                    1.0,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePrefRowSpin::value:
   *
   * The value of the adjustment
   */
  properties[PROP_VALUE] = g_param_spec_double ("value",
                                                "Adjustment value",
                                                "The value of the adjustment",
                                                -G_MINDOUBLE,
                                                G_MAXDOUBLE,
                                                0.0,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/gui/finance-pref-row-spin.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowSpin, title);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowSpin, text);
  gtk_widget_class_bind_template_child (widget_class, FinancePrefRowSpin, pref_spin);
}

static void
finance_pref_row_spin_init (FinancePrefRowSpin *self)
{
  self->key = NULL;

  self->adjustment = gtk_adjustment_new (0.0, 0.0, 100.0, 1.0, 5.0, 0.0);

  gtk_widget_init_template (GTK_WIDGET (self));

  gtk_spin_button_set_adjustment (GTK_SPIN_BUTTON (self->pref_spin),
                                  self->adjustment);
}

/**
 * finance_pref_row_spin_get_min_num:
 * @self: a #FinancePrefRowSpin
 *
 * Returns the minimum value on the spin_button.
 *
 * Returns: The minimum value in the #GtkSpinButton.
 *
 * Since: 1.0
 */
gdouble
finance_pref_row_spin_get_min_num (FinancePrefRowSpin *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_SPIN (self), 0.0);

  return gtk_adjustment_get_lower (self->adjustment);
}

/**
 * finance_pref_row_spin_set_min_num:
 * @self: a #FinancePrefRowSpin
 * @value: a #gdouble
 *
 * Sets the minimum value for the #GtkSpinButton.
 *
 * Since: 1.0
 */
void
finance_pref_row_spin_set_min_num (FinancePrefRowSpin *self,
                                   gdouble            value)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_SPIN (self));

  gtk_adjustment_set_lower (self->adjustment, value);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_MIN_NUM]);
}

/**
 * finance_pref_row_spin_get_max_num:
 * @self: a #FinancePrefRowSpin
 *
 * Returns the maximum value on the spin_button.
 *
 * Returns: The maximum value in the #GtkSpinButton.
 *
 * Since:1.0
 */
gdouble
finance_pref_row_spin_get_max_num (FinancePrefRowSpin *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_SPIN (self), 0.0);

  return gtk_adjustment_get_upper (self->adjustment);
}

/**
 * finance_pref_row_spin_set_max_num:
 * @self: a #FinancePrefRowSpin
 * @value: a #gbouble
 *
 * Sets the maximum value for the #GtkSpinButton.
 *
 * Since: 1.0
 */
void
finance_pref_row_spin_set_max_num (FinancePrefRowSpin *self,
                                   gdouble            value)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_SPIN (self));

  gtk_adjustment_set_upper (self->adjustment, value);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_MAX_NUM]);
}

/**
 * finance_pref_row_spin_get_increment:
 * @self: a #FinancePrefRowSpin
 *
 * Returns the step increment value on the spin_button.
 *
 * Returns: The step increment value in the #GtkSpinButton.
 *
 * Since: 1.0
 */
gdouble
finance_pref_row_spin_get_increment (FinancePrefRowSpin *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_SPIN (self), 0.0);

  return gtk_adjustment_get_step_increment (self->adjustment);
}

/**
 * finance_pref_row_spin_set_increment:
 * @self: a #FinancePrefRowSpin
 * @value: a #gdouble
 *
 * Sets the step increment value for the #GtkSpinButton.
 *
 * Since: 1.0
 */
void
finance_pref_row_spin_set_increment (FinancePrefRowSpin *self,
                                     gdouble            value)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_SPIN (self));

  gtk_adjustment_set_step_increment (self->adjustment, value);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_INCREMENT]);
}

/**
 * finance_pref_row_spin_get_value:
 * @self: a #FinancePrefRowSpin
 *
 * Returns the value in the spin_button.
 *
 * Returns: The value in the #GtkSpinButton.
 *
 * Since: 1.0
 */
gdouble
finance_pref_row_spin_get_value (FinancePrefRowSpin *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_ROW_SPIN (self), 0.0);

  return gtk_adjustment_get_value (self->adjustment);
}

/**
 * finance_pref_row_spin_set_value:
 * @self: a #FinancePrefRowSpin
 * @value: a #gdouble
 *
 * Sets the value for the #GtkSpinButton.
 *
 * Since: 1.0
 */
void
finance_pref_row_spin_set_value (FinancePrefRowSpin *self,
                                 gdouble            value)
{
  g_return_if_fail (FINANCE_IS_PREF_ROW_SPIN (self));

  gtk_adjustment_set_value (self->adjustment, value);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_VALUE]);
}
