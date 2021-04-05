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
  GtkWidget   *list;
  GtkWidget   *search;
  GtkWidget   *sort_ascending;
  GtkWidget   *sort_descending;

  GtkSortType sort;
};

G_DEFINE_TYPE (FinancePane, finance_pane, GTK_TYPE_BOX)

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
finance_pane_class_init (FinancePaneClass *klass)
{
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  g_type_ensure (FINANCE_TYPE_PANE_ROW);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/pane/finance-pane.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinancePane, list);
  gtk_widget_class_bind_template_child (widget_class, FinancePane, search);
  gtk_widget_class_bind_template_child (widget_class, FinancePane, sort_ascending);
  gtk_widget_class_bind_template_child (widget_class, FinancePane, sort_descending);

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_list_box_row_activated);
  gtk_widget_class_bind_template_callback (widget_class, on_pane_search_changed);
  gtk_widget_class_bind_template_callback (widget_class, on_sort_ascending_clicked);
  gtk_widget_class_bind_template_callback (widget_class, on_sort_descending_clicked);
}

static void
finance_pane_init (FinancePane *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->sort = GTK_SORT_ASCENDING;

  gtk_list_box_set_filter_func (GTK_LIST_BOX (self->list),
                                (GtkListBoxFilterFunc)listbox_list_func,
                                (gpointer) self,
                                FALSE);

  gtk_list_box_set_sort_func (GTK_LIST_BOX (self->list),
                              (GtkListBoxSortFunc)listbox_sort_func,
                              (gpointer) self,
                              FALSE);
}

void
finance_pane_add_row (FinancePane *self,
                      GtkWidget   *row)
{
  g_return_if_fail (FINANCE_IS_PANE (self));

  gtk_list_box_insert (GTK_LIST_BOX (self->list), row, -1);
}
