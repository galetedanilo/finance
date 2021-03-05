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
  gdouble         amount;
};

G_DEFINE_TYPE (FinancePaneRow, finance_pane_row, GTK_TYPE_LIST_BOX_ROW)

enum {
  PROP_0,
  PROP_ICON,
  PROP_COLOR,
  PROP_TITLE,
  PROP_INFO,
  PROP_SELECTED,
  PROP_AMOUNT,
  PROP_SYMBOL,
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

  g_clear_pointer (&self->color, gdk_rbga_clear);

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
    case PROP_COLOR:
      g_value_set_boxed (value, finance_pane_row_get_color (self));
      break;

    case PROP_TITLE:
      g_value_set_string (value, finance_pane_row_get_title (self));
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
    case PROP_COLOR:
      finance_pane_row_set_color (self, g_value_get_boxed (value));
      break;

    case PROP_TITLE:
      finance_pane_row_set_title (self, g_value_get_string (value));
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
