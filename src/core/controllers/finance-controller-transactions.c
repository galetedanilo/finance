/* finance-controller-transactions.c
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

#include "finance-controller-transactions.h"

struct _FinanceControllerTransactions
{
  GObject   parent_instance;

  /* The Objects */
  GObject   *pane;
  GObject   *view_transactions;

};

G_DEFINE_TYPE (FinanceControllerTransactions, finance_controller_transactions, G_TYPE_OBJECT)

enum {
  PROP_0,
  PROP_PANE,
  PROP_VIEW,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static void
finance_controller_transactions_finalize (GObject *object)
{
  FinanceControllerTransactions *self = (FinanceControllerTransactions *)object;

  g_clear_object (&self->pane);
  g_clear_object (&self->view_transactions);

  G_OBJECT_CLASS (finance_controller_transactions_parent_class)->finalize (object);
}

static void
finance_controller_transactions_get_property (GObject    *object,
                                              guint       prop_id,
                                              GValue     *value,
                                              GParamSpec *pspec)
{
  FinanceControllerTransactions *self = FINANCE_CONTROLLER_TRANSACTIONS (object);

  switch (prop_id)
    {
    case PROP_PANE:
      g_value_set_object (value, self->pane);
      break;

    case PROP_VIEW:
      g_value_set_object (value, self->view_transactions);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_controller_transactions_set_property (GObject      *object,
                                              guint         prop_id,
                                              const GValue *value,
                                              GParamSpec   *pspec)
{
  FinanceControllerTransactions *self = FINANCE_CONTROLLER_TRANSACTIONS (object);

  switch (prop_id)
    {
    case PROP_PANE:
      g_assert (self->pane == NULL);
      self->pane = g_value_get_object (value);
      break;

    case PROP_VIEW:
      g_assert (self->view_transactions == NULL);
      self->view_transactions = g_value_dup_object (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_controller_transactions_class_init (FinanceControllerTransactionsClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize      = finance_controller_transactions_finalize;
  object_class->get_property  = finance_controller_transactions_get_property;
  object_class->set_property  = finance_controller_transactions_set_property;

  /**
   * FinanceControllerTransaction::pane:
   *
   * Sets pane
   */
  properties[PROP_PANE] = g_param_spec_object ("pane",
                                               "The Pane",
                                               "The left pane in the main window",
                                               FINANCE_TYPE_PANE,
                                               G_PARAM_READWRITE);

    /**
   * FinanceControllerTransaction::view:
   *
   * Sets view
   */
  properties[PROP_VIEW] = g_param_spec_object ("view",
                                               "The View",
                                               "The view transactions",
                                               FINANCE_TYPE_VIEW,
                                               G_PARAM_READWRITE);

  g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
finance_controller_transactions_init (FinanceControllerTransactions *self)
{
  //self->child = g_ptr_array_new
}

void
finance_controller_transactions_startup (FinanceControllerTransactions *self)
{
    for(int x = 0; x < 200; x++)
    {
        //this is a test
        GtkWidget *summary = finance_child_summary_new ();
        GtkWidget *row = finance_pane_row_new ();

        finance_pane_row_set_icon (row, "TR");
        finance_pane_row_set_title (row, "Transaction Name Title");
        finance_pane_row_set_amount (row, "R$2,540.45");

      finance_child_summary_set_name (summary, "Teste");

      finance_view_insert_child (FINANCE_VIEW (self->view_transactions), summary);



      finance_pane_prepend_row (FINANCE_PANE (self->pane), row);
    }
}
