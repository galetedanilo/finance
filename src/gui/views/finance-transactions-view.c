/* finance-transactions-view.c
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

#include "finance-transactions-view.h"

struct _FinanceTransactionsView
{
  GtkBox     parent_instance;

  /* The widgets */
  GtkFlowBox *flow_box;
};

G_DEFINE_TYPE (FinanceTransactionsView, finance_transactions_view, GTK_TYPE_BOX)

enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

GtkWidget *
finance_transactions_view_new (void)
{
  return g_object_new (FINANCE_TYPE_TRANSACTIONS_VIEW, NULL);
}

static void
finance_transactions_view_finalize (GObject *object)
{
  FinanceTransactionsView *self = (FinanceTransactionsView *)object;

  G_OBJECT_CLASS (finance_transactions_view_parent_class)->finalize (object);
}

static void
finance_transactions_view_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *pspec)
{
  FinanceTransactionsView *self = FINANCE_TRANSACTIONS_VIEW (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_transactions_view_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec)
{
  FinanceTransactionsView *self = FINANCE_TRANSACTIONS_VIEW (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_transactions_view_class_init (FinanceTransactionsViewClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize = finance_transactions_view_finalize;
  object_class->get_property = finance_transactions_view_get_property;
  object_class->set_property = finance_transactions_view_set_property;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/views/finance-transactions-view.ui");

  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionsView, flow_box);
}

static void
finance_transactions_view_init (FinanceTransactionsView *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  /* for (int x = 0; x < 5; x++) */
  /*   { */
  /*     GtkWidget *child = finance_view_child_new (); */
  /*     gtk_flow_box_insert (GTK_FLOW_BOX (self->flow_box), child, -1); */
  /*   } */
}
