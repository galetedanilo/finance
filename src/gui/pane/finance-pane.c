/* finance-pane.c
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

#include "finance-pane.h"

struct _FinancePane
{
  GtkBox      parent_instance;

  /* The Widgets */
  GtkWidget   *search;
  GtkWidget   *list;
};

G_DEFINE_TYPE (FinancePane, finance_pane, GTK_TYPE_BOX)

enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static gboolean
finance_pane_filter_list (GtkListBoxRow *row,
                          gpointer      user_data)
{
  FinancePane *self = FINANCE_PANE (user_data);

  if (strcasestr (finance_pane_row_get_title (FINANCE_PANE_ROW (row)),
                  gtk_entry_get_text (GTK_ENTRY (self->search))))
    return TRUE;
  else
    return FALSE;

}

static void
on_pane_search_changed (GtkSearchEntry  *entry,
                        gpointer        user_data)
{
  FinancePane *self = FINANCE_PANE (user_data);

  gtk_list_box_set_filter_func (GTK_LIST_BOX (self->list),
                                (GtkListBoxFilterFunc)finance_pane_filter_list,
                                (gpointer) self,
                                FALSE);
}

GtkWidget *
finance_pane_new (void)
{
  return g_object_new (FINANCE_TYPE_PANE, NULL);
}

static void
finance_pane_finalize (GObject *object)
{
  FinancePane *self = (FinancePane *)object;

  G_OBJECT_CLASS (finance_pane_parent_class)->finalize (object);
}

static void
finance_pane_get_property (GObject    *object,
                           guint       prop_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
  FinancePane *self = FINANCE_PANE (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pane_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
  FinancePane *self = FINANCE_PANE (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
finance_pane_class_init (FinancePaneClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize      = finance_pane_finalize;
  object_class->get_property  = finance_pane_get_property;
  object_class->set_property  = finance_pane_set_property;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/pane/finance-pane.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePane, search);
  gtk_widget_class_bind_template_child (widget_class, FinancePane, list);

  gtk_widget_class_bind_template_callback (widget_class, on_pane_search_changed);
}

static void
finance_pane_init (FinancePane *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  //this is a test
  GtkWidget *row = finance_pane_row_new ();

  finance_pane_row_set_icon (row, "TR");
  finance_pane_row_set_title (row, "Transaction Name Title");
  finance_pane_row_set_amount (row, "R$2,540.45");

  gtk_list_box_insert (GTK_LIST_BOX (self->list), row, -1);

}
