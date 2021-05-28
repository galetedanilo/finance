/* finance-transaction-view-controller.c
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

#include "finance-transaction-view-controller.h"

struct _FinanceTransactionViewController
{
  GObject   parent_instance;

  /* The Objects */
  GObject   *pane;
  GObject   *view;

};

G_DEFINE_TYPE (FinanceTransactionViewController, finance_transaction_view_controller, G_TYPE_OBJECT)

enum {
  PROP_0,
  PROP_PANE,
  PROP_VIEW,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static void
finance_transaction_view_controller_finalize (GObject *object)
{
  FinanceTransactionViewController *self = (FinanceTransactionViewController *)object;

  g_clear_object (&self->pane);
  g_clear_object (&self->view);

  G_OBJECT_CLASS (finance_transaction_view_controller_parent_class)->finalize (object);
}

static void
finance_transaction_view_controller_get_property (GObject    *object,
                                                  guint       prop_id,
                                                  GValue     *value,
                                                  GParamSpec *pspec)
{
  FinanceTransactionViewController *self = FINANCE_TRANSACTION_VIEW_CONTROLLER (object);

  switch (prop_id)
    {
    case PROP_PANE:
      g_value_set_object (value, self->pane);
      break;

    case PROP_VIEW:
      g_value_set_object (value, self->view);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_transaction_view_controller_set_property (GObject      *object,
                                                   guint         prop_id,
                                                   const GValue *value,
                                                   GParamSpec   *pspec)
{
  FinanceTransactionViewController *self = FINANCE_TRANSACTION_VIEW_CONTROLLER (object);

  switch (prop_id)
    {
    case PROP_PANE:
      g_assert (self->pane == NULL);
      self->pane = g_value_get_object (value);
      break;

    case PROP_VIEW:
      g_assert (self->view == NULL);
      self->view = g_value_dup_object (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_transaction_view_controller_class_init (FinanceTransactionViewControllerClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize      = finance_transaction_view_controller_finalize;
  object_class->get_property  = finance_transaction_view_controller_get_property;
  object_class->set_property  = finance_transaction_view_controller_set_property;

  /**
   * FinanceTransactionViewController::pane:
   *
   * Sets pane
   */
  properties[PROP_PANE] = g_param_spec_object ("pane",
                                               "The Pane",
                                               "The left pane in the main window",
                                               FINANCE_TYPE_LEFT_PANEL,
                                               G_PARAM_READWRITE);

    /**
   * FinancerTransactionViewControlle::view:
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
finance_transaction_view_controller_init (FinanceTransactionViewController *self)
{

}

void
finance_transaction_view_controller_startup (FinanceTransactionViewController *self)
{
      for(int x = 0; x < 1; x++)
    {
        //this is a test
        GtkWidget *summary = finance_summary_child_new ();
        GtkWidget *row = finance_transaction_row_new ();
      GdkRGBA *color = finance_utils_random_rgba_color ();

      g_object_bind_property ((gpointer)summary,
                                "icon-text",
                                (gpointer)row,
                                "icon-text",
                                G_BINDING_DEFAULT);
      g_object_bind_property ((gpointer)summary,
                                "color",
                                (gpointer)row,
                                "color",
                                G_BINDING_DEFAULT);

        g_object_bind_property ((gpointer)summary,
                                "name",
                                (gpointer)row,
                                "title",
                                G_BINDING_DEFAULT);

      g_object_bind_property ((gpointer)summary,
                                "amount",
                                (gpointer)row,
                                "amount",
                                G_BINDING_DEFAULT);

      g_object_bind_property ((gpointer)summary,
                                "selected",
                                (gpointer)row,
                                "selected",
                                G_BINDING_BIDIRECTIONAL | G_BINDING_SYNC_CREATE);

      finance_summary_child_set_name (FINANCE_SUMMARY_CHILD (summary),
                                      "Cadastro para Teste");

      finance_summary_child_set_amount (FINANCE_SUMMARY_CHILD (summary),
                                               "R$ 500,00");

      finance_view_add_child (FINANCE_VIEW (self->view), summary);



      finance_left_panel_add_row (FINANCE_LEFT_PANEL (self->pane), row);

      g_clear_pointer (&color, gdk_rgba_free);
    }


}
