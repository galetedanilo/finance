/* finance-view-child.c
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

#include "finance-view-child.h"

struct _FinanceViewChild
{
  GtkButton parent_instance;

  /* The widgets */
  GtkWidget *image;
  GtkWidget *name;
  GtkWidget *amount;
  GtkWidget *date;
  GtkWidget *payee_name;
  GtkWidget *payment;
  GtkWidget *payment_info;
  GtkWidget *category;
  GtkWidget *repeat;

  GdkRGBA   *color;
  gchar     *icon;
};

G_DEFINE_TYPE (FinanceViewChild, finance_view_child, GTK_TYPE_BUTTON)

enum {
  PROP_0,
  PROP_ICON,
  PROP_COLOR,
  PROP_NAME,
  PROP_AMOUNT,
  PROP_DATE,
  PROP_PAYEE_NAME,
  PROP_PAYMENT,
  PROP_CATEGORY,
  PROP_REPEAT,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

static void
create_icon (FinanceViewChild *self)
{
  cairo_surface_t *surface;

  surface = finance_utils_create_circle (self->color, 100, self->icon);

  gtk_image_set_from_surface (GTK_IMAGE (self->image), surface);

  g_clear_pointer (&surface, cairo_surface_destroy);
}

GtkWidget *
finance_view_child_new (void)
{
  return g_object_new (FINANCE_TYPE_VIEW_CHILD, NULL);
}

static void
finance_view_child_finalize (GObject *object)
{
  FinanceViewChild *self = (FinanceViewChild *)object;

  g_clear_pointer (&self->color, gdk_rgba_free);

  G_OBJECT_CLASS (finance_view_child_parent_class)->finalize (object);
}

static void
finance_view_child_get_property (GObject    *object,
                                 guint       prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  FinanceViewChild *self = FINANCE_VIEW_CHILD (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_view_child_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  FinanceViewChild *self = FINANCE_VIEW_CHILD (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_view_child_class_init (FinanceViewChildClass *klass)
{
  GObjectClass   *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize      = finance_view_child_finalize;
  object_class->get_property  = finance_view_child_get_property;
  object_class->set_property  = finance_view_child_set_property;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/views/finance-view-child.ui");

  gtk_widget_class_bind_template_child (widget_class, FinanceViewChild, image);
}

static void
finance_view_child_init (FinanceViewChild *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->color = finance_utils_random_rgba_color ();

  create_icon (self);
}

/**
 * finance_view_child_get_icon:
 * @self: a #FinanceViewChild object.
 *
 * Since: 1.0
 */
const gchar *
finance_view_child_get_icon (FinanceViewChild *self)
{
  g_return_val_if_fail (FINANCE_IS_VIEW_CHILD (self), NULL);

  return self->icon;
}

/**
 * finance_child_view_set_icon:
 * @self: a #FinanceChildView instance.
 * @icon: the icon to set, as a string.
 *
 * Since:1.0
 */
void
finance_child_view_set_icon (FinanceViewChild *self,
                             const gchar      *icon)
{
  g_return_if_fail (FINANCE_IS_VIEW_CHILD (self));

  g_free (self->icon);

  self->icon = g_strdup (icon);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON]);
}

/**
 * finance_view_child_get_color:
 * @self: a #FinanceViewChild object.
 *
 * Since: 1.0
 */
GdkRGBA *
finance_view_child_get_color (FinanceViewChild *self)
{
  g_return_val_if_fail (FINANCE_IS_VIEW_CHILD (self), NULL);

  return self->color;
}

/**
 * finance_view_child_set_color:
 * @self: a #FinanceViewChild instance.
 * @color: a #GdkRGBA.
 *
 * Since: 1.0
 */
void
finance_view_child_set_color (FinanceViewChild *self,
                              const GdkRGBA    *color)
{
  g_return_if_fail (FINANCE_IS_VIEW_CHILD (self));

  gdk_rgba_free (self->color);

  self->color = gdk_rgba_copy (color);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_COLOR]);
}

/**
 * finance_view_child_get_name:
 * @self: a #FinanceViewChild object.
 *
 * Since: 1.0
 */
const gchar *
finance_view_child_get_name (FinanceViewChild *self)
{
  g_return_val_if_fail (FINANCE_IS_VIEW_CHILD (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->name));
}

/**
 * finance_view_child_set_name:
 * @self: a #FinanceViewChild instance.
 * @name: the name to set, as a string.
 *
 * Since: 1.0
 */
void
finance_view_child_set_name (FinanceViewChild *self,
                             const gchar      *name)
{
  g_return_if_fail (FINANCE_IS_VIEW_CHILD (self));

  gtk_label_set_text (GTK_LABEL (self->name), name);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_NAME]);
}

/**
 * finance_view_child_get_amount:
 * @self: a #FinanceViewChild instance.
 *
 * Since: 1.0
 */
const gchar *
finance_view_child_get_amount (FinanceViewChild *self)
{
  g_return_val_if_fail (FINANCE_IS_VIEW_CHILD (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->amount));
}

/**
 * finance_view_child_set_amount:
 * @self: a #FinanceTransaction object.
 *
 * Since: 1.0
 */
void
finance_view_child_set_amount (FinanceViewChild *self,
                               const gchar      *amount)
{
  g_return_if_fail (FINANCE_IS_VIEW_CHILD (self));

  gtk_label_set_text (GTK_LABEL (self->amount), amount);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_AMOUNT]);
}

/**
 * finance_view_child_get_date:
 * @self: a #FinanceViewChild instance.
 *
 * Since: 1.0
 */
const gchar *
finance_view_child_get_date (FinanceViewChild *self)
{
  g_return_val_if_fail (FINANCE_IS_VIEW_CHILD (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->date));
}

/**
 * finance_transaction_set_date:
 * @self: a #FinanceTransaction object.
 * @date: a valid date, as a #GDateTime.
 *
 * Sets the date of the financial transaction.
 *
 * Since: 1.0
 */
void
finance_view_child_set_date (FinanceViewChild *self,
                             const gchar      *date)
{
  g_return_if_fail (FINANCE_IS_VIEW_CHILD (self));

  gtk_label_set_text (GTK_LABEL (self->date), date);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_DATE]);
}
