/* finance-pref-box.c
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

#include "finance-pref-box.h"

struct _FinancePrefBox
{
  GtkBox      parent_instance;

  /* The Widgets */
  GtkWidget   *title;
};

G_DEFINE_TYPE (FinancePrefBox, finance_pref_box, GTK_TYPE_BOX)

enum {
  PROP_0,
  PROP_TITLE,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

GtkWidget *
finance_pref_box_new (void)
{
  return g_object_new (FINANCE_TYPE_PREF_BOX, NULL);
}

static void
finance_pref_box_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  FinancePrefBox *self = FINANCE_PREF_BOX (object);

  switch (prop_id)
    {
    case PROP_TITLE:
      g_value_set_string (value, finance_pref_box_get_title (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pref_box_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  FinancePrefBox *self = FINANCE_PREF_BOX (object);

  switch (prop_id)
    {
    case PROP_TITLE:
      finance_pref_box_set_title (self, g_value_get_string (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pref_box_class_init (FinancePrefBoxClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->get_property = finance_pref_box_get_property;
  object_class->set_property = finance_pref_box_set_property;

  /**
   * FinancePrefBox::title:
   *
   * The title of the preference box
   */
  properties[PROP_TITLE] = g_param_spec_string ("title",
                                                "Title",
                                                "The title of the preference box",
                                                NULL,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/pref/finance-pref-box.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePrefBox, title);
}

static void
finance_pref_box_init (FinancePrefBox *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

/**
 * finance_pref_box_get_title:
 * @self: a #FinancePrefBox.
 *
 * Returns the title from the label of the preference box.
 *
 * Returns: The title in the #FinancePrefBox, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pref_box_get_title (FinancePrefBox *self)
{
  g_return_val_if_fail (FINANCE_IS_PREF_BOX (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->title));
}

/**
 * finance_pref_box_set_title:
 * @self: a #FinancePrefBox.
 * @title: The title to set.
 *
 * Sets the title within the #FinancePrefBox, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pref_box_set_title (FinancePrefBox  *self,
                            const gchar     *title)
{
  g_return_if_fail (FINANCE_IS_PREF_BOX (self));

  gtk_label_set_text (GTK_LABEL (self->title), title);
}
