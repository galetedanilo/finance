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
  GtkWidget   *sort_ascending;
  GtkWidget   *sort_descending;
  GtkWidget   *list;

  GPtrArray   *selected;
  GtkSortType sort;
};

G_DEFINE_TYPE (FinancePane, finance_pane, GTK_TYPE_BOX)

enum {
  PROP_0,
  PROP_NUM_ROWS_SELECTED,
  N_PROPS
};

enum {
  ROW_CHANGE_STATE,
  N_SIGNALS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static guint signals[N_SIGNALS] = { 0, };

static gboolean
listbox_list_func (GtkListBoxRow  *row,
                   gpointer       user_data)
{
  FinancePane *self = FINANCE_PANE (user_data);

  if (strcasestr (finance_pane_row_get_title (FINANCE_PANE_ROW (row)),
                  gtk_entry_get_text (GTK_ENTRY (self->search))))
    return TRUE;

  return FALSE;

}

static gint
listbox_sort_func (GtkListBoxRow *row1,
                   GtkListBoxRow *row2,
                   gpointer       user_data)
{
  FinancePane *self = FINANCE_PANE (user_data);

  if (self->sort == GTK_SORT_ASCENDING)
    return strcasecmp (finance_pane_row_get_title (FINANCE_PANE_ROW (row1)),
                       finance_pane_row_get_title (FINANCE_PANE_ROW (row2)));

  return -1 * strcasecmp (finance_pane_row_get_title (FINANCE_PANE_ROW (row1)),
                          finance_pane_row_get_title (FINANCE_PANE_ROW (row2)));
}

static void
on_list_box_row_activated (GtkListBox    *box,
                           GtkListBoxRow *row,
                           gpointer      user_data)
{
  FinancePane *self = FINANCE_PANE (user_data);
}


static void
on_pane_search_changed (GtkSearchEntry  *entry,
                        gpointer        user_data)
{
  FinancePane *self = FINANCE_PANE (user_data);

  (void)entry;

  gtk_list_box_invalidate_filter (GTK_LIST_BOX (self->list));
}

static void
on_sort_ascending_clicked (GtkButton *button,
                           gpointer   user_data)
{
  FinancePane *self = FINANCE_PANE (user_data);

  (void)button;

  gtk_widget_set_visible (self->sort_ascending, FALSE);
  gtk_widget_set_visible (self->sort_descending, TRUE);

  self->sort = GTK_SORT_ASCENDING;

  gtk_list_box_invalidate_sort (GTK_LIST_BOX (self->list));
}

static void
on_sort_descending_clicked (GtkButton *button,
                            gpointer   user_data)
{
  FinancePane *self = FINANCE_PANE (user_data);

  (void)button;

  gtk_widget_set_visible (self->sort_descending, FALSE);
  gtk_widget_set_visible (self->sort_ascending, TRUE);

  self->sort = GTK_SORT_DESCENDING;

  gtk_list_box_invalidate_sort (GTK_LIST_BOX (self->list));
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

  g_ptr_array_free (self->selected, TRUE);

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
    case PROP_NUM_ROWS_SELECTED:
      g_value_set_uint (value, finance_pane_get_num_rows_selected (self));
      break;

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

  g_type_ensure (FINANCE_TYPE_PANE_ROW);

  /**
   * FinancePane::row-change-state:
   *
   * Emitted when the row is changes its state
   */
  signals[ROW_CHANGE_STATE] = g_signal_new ("row-change-state",
                                            FINANCE_TYPE_PANE,
                                            G_SIGNAL_RUN_LAST,
                                            0,
                                            NULL, NULL, NULL,
                                            G_TYPE_NONE,
                                            0);

  /**
   * FinancePane::num-rows-selected:
   *
   * The number of rows selected
   */
  properties[PROP_NUM_ROWS_SELECTED] = g_param_spec_uint ("num-rows-selected",
                                                          "Num rows selected",
                                                          "The number of rows selected",
                                                          0,
                                                          G_MAXUINT,
                                                          0,
                                                          G_PARAM_READABLE);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/pane/finance-pane.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePane, search);
  gtk_widget_class_bind_template_child (widget_class, FinancePane, sort_ascending);
  gtk_widget_class_bind_template_child (widget_class, FinancePane, sort_descending);
  gtk_widget_class_bind_template_child (widget_class, FinancePane, list);

  /* All signals */
  gtk_widget_class_bind_template_callback (widget_class, on_pane_search_changed);
  gtk_widget_class_bind_template_callback (widget_class, on_sort_ascending_clicked);
  gtk_widget_class_bind_template_callback (widget_class, on_sort_descending_clicked);
  gtk_widget_class_bind_template_callback (widget_class, on_list_box_row_activated);
}

static void
finance_pane_init (FinancePane *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->selected = g_ptr_array_new ();
  self->sort = GTK_SORT_ASCENDING;

  gtk_list_box_set_filter_func (GTK_LIST_BOX (self->list),
                                (GtkListBoxFilterFunc)listbox_list_func,
                                (gpointer) self,
                                FALSE);

  gtk_list_box_set_sort_func (GTK_LIST_BOX (self->list),
                              (GtkListBoxSortFunc)listbox_sort_func,
                              (gpointer) self,
                              FALSE);


  //this is a test
  GtkWidget *row = finance_pane_row_new ();

  finance_pane_row_set_icon (row, "TR");
  finance_pane_row_set_title (row, "Transaction Name Title");
  finance_pane_row_set_amount (row, "R$2,540.45");
  gtk_list_box_insert (GTK_LIST_BOX (self->list), row, -1);

  row = finance_pane_row_new ();
  finance_pane_row_set_icon (row, "BC");
  finance_pane_row_set_title (row, "New Home");
  finance_pane_row_set_amount (row, "R$2,540.45");
  gtk_list_box_insert (GTK_LIST_BOX (self->list), row, -1);

  row = finance_pane_row_new ();
  finance_pane_row_set_icon (row, "VT");
  finance_pane_row_set_title (row, "View System");
  finance_pane_row_set_amount (row, "R$2,540.45");
  gtk_list_box_insert (GTK_LIST_BOX (self->list), row, -1);

  row = finance_pane_row_new ();
  finance_pane_row_set_icon (row, "BA");
  finance_pane_row_set_title (row, "Bank");
  finance_pane_row_set_amount (row, "R$2,540.45");
  gtk_list_box_insert (GTK_LIST_BOX (self->list), row, -1);


}

/**
 * finance_pane_get_num_rows_selected:
 * @self: a #FinancePane object.
 *
 * Returns the number of rows selected.
 *
 * Returns: the number of rows selected as a #guint.
 *
 * Since: 1.0
 */
guint
finance_pane_get_num_rows_selected (FinancePane *self)
{
  g_return_val_if_fail (FINANCE_IS_PANE (self), 0);

  return 1;//self->selected->len;
}
