/* finance-view-transactions.c
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

#include "finance-view-transactions.h"

struct _FinanceViewTransactions
{
  GtkBox parent_instance;
};

G_DEFINE_TYPE (FinanceViewTransactions, finance_view_transactions, GTK_TYPE_BOX)

enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

GtkWidget *
finance_view_transactions_new (void)
{
  return g_object_new (FINANCE_TYPE_VIEW_TRANSACTIONS, NULL);
}

static void
finance_view_transactions_finalize (GObject *object)
{
  FinanceViewTransactions *self = (FinanceViewTransactions *)object;

  G_OBJECT_CLASS (finance_view_transactions_parent_class)->finalize (object);
}

static void
finance_view_transactions_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *pspec)
{
  FinanceViewTransactions *self = FINANCE_VIEW_TRANSACTIONS (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_view_transactions_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec)
{
  FinanceViewTransactions *self = FINANCE_VIEW_TRANSACTIONS (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_view_transactions_class_init (FinanceViewTransactionsClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = finance_view_transactions_finalize;
  object_class->get_property = finance_view_transactions_get_property;
  object_class->set_property = finance_view_transactions_set_property;
}

static void
finance_view_transactions_init (FinanceViewTransactions *self)
{
}
