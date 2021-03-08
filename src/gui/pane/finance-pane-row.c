/* finance-pane-row.c
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

#include "finance-pane-row.h"

struct _FinancePaneRow
{
  GtkListBoxRow   parent_class;

  /* The Widgets */
  GtkWidget       *image;
  GtkWidget       *title;
  GtkWidget       *info;
  GtkWidget       *revealer;
  GtkWidget       *check;

  GdkRGBA         *color;
  gchar           *icon;
};

G_DEFINE_TYPE (FinancePaneRow, finance_pane_row, GTK_TYPE_LIST_BOX_ROW)

enum {
  PROP_0,
  PROP_ICON,
  PROP_COLOR,
  PROP_TITLE,
  PROP_INFO,
  PROP_SELECTED,
  N_PROPS,
};

static GParamSpec *properties [N_PROPS] = { NULL, };

GtkWidget *
finance_pane_row_new (void)
{
  return g_object_new (FINANCE_TYPE_PANE_ROW, NULL);
}

static void
finance_pane_row_finalize (GObject *object)
{
  FinancePaneRow *self = (FinancePaneRow *)object;

  g_clear_pointer (&self->icon, g_free);

  G_OBJECT_CLASS (finance_pane_row_parent_class)->finalize (object);
}

static void
finance_pane_row_dispose (GObject *object)
{
  FinancePaneRow *self = (FinancePaneRow *)object;

  g_clear_pointer (&self->color, gdk_rgba_free);

  G_OBJECT_CLASS (finance_pane_row_parent_class)->dispose (object);
}

static void
finance_pane_row_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  FinancePaneRow *self = FINANCE_PANE_ROW (object);

  switch (prop_id)
    {
    case PROP_ICON:
      g_value_set_string (value, finance_pane_row_get_icon (self));
      break;

    case PROP_COLOR:
      g_value_set_boxed (value, finance_pane_row_get_color (self));
      break;

    case PROP_TITLE:
      g_value_set_string (value, finance_pane_row_get_title (self));
      break;

    case PROP_INFO:
      g_value_set_string (value, finance_pane_row_get_info (self));
      break;

    case PROP_SELECTED:
      g_value_set_boolean (value, finance_pane_row_is_selected (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_pane_row_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  FinancePaneRow *self = FINANCE_PANE_ROW (object);

  switch (prop_id)
    {
    case PROP_ICON:
      finance_pane_row_set_icon (self, g_value_get_string (value));
      break;

    case PROP_COLOR:
      finance_pane_row_set_color (self, g_value_get_boxed (value));
      break;

    case PROP_TITLE:
      finance_pane_row_set_title (self, g_value_get_string (value));
      break;

    case PROP_INFO:
      finance_pane_row_set_info (self, g_value_get_string (value));
      break;

    case PROP_SELECTED:
      finance_pane_row_set_selected (self, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_pane_row_class_init (FinancePaneRowClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize      = finance_pane_row_finalize;
  object_class->dispose       = finance_pane_row_dispose;
  object_class->get_property  = finance_pane_row_get_property;
  object_class->set_property  = finance_pane_row_set_property;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/pane/finance-pane-row.ui");
}

static void
finance_pane_row_init (FinancePaneRow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

/**
 * finance_pane_row_get_icon:
 * @self: a #FinancePaneRow object.
 *
 * Returns the pane row icon.
 *
 * Returns: The pane row icon as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pane_row_get_icon (FinancePaneRow *self)
{
  g_return_val_if_fail (FINANCE_IS_PANE_ROW (self), NULL);

  return self->icon;
}

/**
 * finance_pane_row_set_icon:
 * @self: a #FinancePaneRow instance.
 * @icon: the icon to set, as a string.
 *
 * Sets the icon, replacing the current contents.
 *
 * Since:1.0
 */
void
finance_pane_row_set_icon (FinancePaneRow *self,
                           const gchar    *icon)
{
  g_return_if_fail (FINANCE_IS_PANE_ROW (self));

  cairo_surface_t *surface;

  g_free (self->icon);

  self->icon = g_strdup (icon);

  surface = finance_utils_create_circle (self->color, 140, self->icon);

  gtk_image_set_from_surface (GTK_IMAGE (self->image), surface);

  g_clear_pointer (&surface, cairo_surface_destroy);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON]);
}

/**
 * finance_pane_row_get_color:
 * @self: a #FinancePaneRow object.
 *
 * Returns the row icon color.
 *
 * Returns: (transfer none): a #GdkRGBA with the color.
 *
 * Since: 1.0
 */
GdkRGBA *
finance_pane_row_get_color (FinancePaneRow *self)
{
  g_return_val_if_fail (FINANCE_IS_PANE_ROW (self), NULL);

  return self->color;
}

/**
 * finance_pane_row_set_color:
 * @self: a #FinancePaneRow instance.
 * @color: a #GdkRGBA.
 *
 * Sets the icon color.
 *
 * Since: 1.0
 */
void
finance_pane_row_set_color (FinancePaneRow *self,
                            const GdkRGBA  *color)
{
  g_return_if_fail (FINANCE_IS_PANE_ROW (self));

  gdk_rgba_free (self->color);

  self->color = gdk_rgba_copy (color);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_COLOR]);
}

/**
 * finance_pane_row_get_title:
 * @self: a #FinancePaneRow object.
 *
 * Returns the title.
 *
 * Returns: The title as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pane_row_get_title (FinancePaneRow *self)
{
  g_return_val_if_fail (FINANCE_IS_PANE_ROW (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->title));
}

/**
 * finance_pane_row_set_title:
 * @self: a #FinancePaneRow instance.
 * @title: the title to set, as a string.
 *
 * Sets the title, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pane_row_set_title (FinancePaneRow *self,
                            const gchar    *title)
{
  g_return_if_fail (FINANCE_IS_PANE_ROW (self));

  gtk_label_set_text (GTK_LABEL (self->title), title);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TITLE]);
}

/**
 * finance_pane_row_get_info:
 * @self: a #FinancePaneRow object.
 *
 * Returns the information text.
 *
 * Returns: The information text as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pane_row_get_info (FinancePaneRow *self)
{
  g_return_val_if_fail (FINANCE_IS_PANE_ROW (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->info));
}

/**
 * finance_pane_row_set_info:
 * @self: a #FinancePaneRow instance.
 * @info: the information text to set, as a string.
 *
 * Sets the information text, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pane_row_set_info (FinancePaneRow *self,
                           const gchar    *info)
{
  g_return_if_fail (FINANCE_IS_PANE_ROW (self));

  gtk_label_set_text (GTK_LABEL (self->info), info);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_INFO]);
}

/**
 * finance_pane_row_is_selected:
 * @self: a #FinancePaneRow object.
 *
 * Returns whether the row is in its “on” or “off” state.
 *
 * Returns: #TRUE if the row is selected, and #FALSE otherwise
 *
 * Since: 1.0
 */
gboolean
finance_pane_row_is_selected (FinancePaneRow *self)
{
  g_return_val_if_fail (FINANCE_IS_PANE_ROW (self), FALSE);

  return gtk_check_button_get_active (GTK_CHECK_BUTTON (self->check));
}

/**
 * finance_pane_row_set_selected:
 * @self: a #FinancePaneRow instance.
 * @selected: #TRUE if row is to be selected, and #FALSE otherwise.
 *
 * Changes the state of #FinancePaneRow to the desired one.
 *
 * Since: 1.0
 */
void
finance_pane_row_set_selected (FinancePaneRow *self,
                               gboolean       selected)
{
  g_return_if_fail (FINANCE_IS_PANE_ROW (self));

  gtk_check_button_set_active (GTK_CHECK_BUTTON (self->check), selected);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_SELECTED]);
}
