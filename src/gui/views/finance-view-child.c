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
  GtkFlowBoxChild parent_instance;
};

G_DEFINE_TYPE (FinanceViewChild, finance_view_child, GTK_TYPE_FLOW_BOX_CHILD)

enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

GtkWidget *
finance_view_child_new (void)
{
  return g_object_new (FINANCE_TYPE_VIEW_CHILD, NULL);
}

static void
finance_view_child_finalize (GObject *object)
{
  FinanceViewChild *self = (FinanceViewChild *)object;

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

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/view/finance-view-child.ui");

}

static void
finance_view_child_init (FinanceViewChild *self)
{
}
