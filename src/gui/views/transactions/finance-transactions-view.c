/* finance-transactions-view.c
 *
 * Copyright 2021 Danilo Fernandes Galete <galetedanilo@gmail.com>
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

#include "finance-view.h"
#include "finance-transactions-view.h"

struct _FinanceTransactionsView
{
  GtkBox    parent_instance;

  /* The Widgets */
  GtkWidget *flow_box;
};

static void     finance_view_interface_init       (FinanceViewInterface *iface);

G_DEFINE_TYPE_WITH_CODE (FinanceTransactionsView, finance_transactions_view, GTK_TYPE_BOX,
                         G_IMPLEMENT_INTERFACE (FINANCE_TYPE_VIEW, finance_view_interface_init))

/* FinanceView implementation */
static void
finance_transactions_view_add_child (FinanceView *view,
                                     GtkWidget   *child)
{
  FinanceTransactionsView *self = FINANCE_TRANSACTIONS_VIEW (view);

  gtk_flow_box_insert (GTK_FLOW_BOX (self->flow_box), child, -1);
}

GtkWidget *
finance_transactions_view_new (void)
{
  return g_object_new (FINANCE_TYPE_TRANSACTIONS_VIEW, NULL);
}

static void
finance_view_interface_init (FinanceViewInterface *iface)
{
  iface->add_child = finance_transactions_view_add_child;
}

static void
finance_transactions_view_class_init (FinanceTransactionsViewClass *klass)
{
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/views/transactions/finance-transactions-view.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionsView, flow_box);
}

static void
finance_transactions_view_init (FinanceTransactionsView *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
