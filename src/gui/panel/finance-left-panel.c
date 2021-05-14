/* finance-left-panel.c
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

#include "finance-left-panel.h"

struct _FinanceLeftPanel
{
  GtkBox      parent_instance;

  /* The Widgets */
  GtkWidget   *button_ascending;
  GtkWidget   *button_descending;
  GtkWidget   *entry_search;
  GtkWidget   *list_box;

  GtkSortType sort;
};

G_DEFINE_TYPE (FinanceLeftPanel, finance_left_panel, GTK_TYPE_BOX)

static gboolean
list_box_filter_func (GtkListBoxRow *row,
                      gpointer       user_data)
{
  FinanceLeftPanel *self = FINANCE_LEFT_PANEL (user_data);

  if (strcasestr (finance_transaction_row_get_title (FINANCE_TRANSACTION_ROW (row)),
                  gtk_entry_get_text (GTK_ENTRY (self->entry_search))))
    return TRUE;

  return FALSE;

}

static gint
list_box_sort_func (GtkListBoxRow *row1,
                    GtkListBoxRow *row2,
                    gpointer       user_data)
{
  FinanceLeftPanel *self = FINANCE_LEFT_PANEL (user_data);

  if (self->sort == GTK_SORT_ASCENDING)
    return strcasecmp (finance_transaction_row_get_title (FINANCE_TRANSACTION_ROW (row1)),
                       finance_transaction_row_get_title (FINANCE_TRANSACTION_ROW (row2)));

  return -1 * strcasecmp (finance_transaction_row_get_title (FINANCE_TRANSACTION_ROW (row1)),
                          finance_transaction_row_get_title (FINANCE_TRANSACTION_ROW (row2)));
}

static void
on_left_panel_search_changed (GtkSearchEntry *entry,
                              gpointer        user_data)
{
  FinanceLeftPanel *self = FINANCE_LEFT_PANEL (user_data);

  (void)entry;

  gtk_list_box_invalidate_filter (GTK_LIST_BOX (self->list_box));
}

static void
on_list_box_row_activated (GtkListBox    *box,
                           GtkListBoxRow *row,
                           gpointer       user_data)
{
  FinanceLeftPanel *self = FINANCE_LEFT_PANEL (user_data);
}

static void
on_button_ascending_clicked (GtkButton *button,
                             gpointer   user_data)
{
  FinanceLeftPanel *self = FINANCE_LEFT_PANEL (user_data);

  gtk_widget_set_visible (GTK_WIDGET (button), FALSE);

  gtk_widget_set_visible (self->button_descending, TRUE);

  self->sort = GTK_SORT_ASCENDING;

  gtk_list_box_invalidate_sort (GTK_LIST_BOX (self->list_box));
}

static void
on_button_descending_clicked (GtkButton *button,
                              gpointer   user_data)
{
  FinanceLeftPanel *self = FINANCE_LEFT_PANEL (user_data);

  gtk_widget_set_visible (button, FALSE);

  gtk_widget_set_visible (self->button_ascending, TRUE);

  self->sort = GTK_SORT_DESCENDING;

  gtk_list_box_invalidate_sort (GTK_LIST_BOX (self->list_box));
}

GtkWidget *
finance_left_panel_new (void)
{
  return g_object_new (FINANCE_TYPE_LEFT_PANEL, NULL);
}

static void
finance_left_panel_class_init (FinanceLeftPanelClass *klass)
{
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  g_type_ensure (FINANCE_TYPE_TRANSACTION_ROW);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/panel/finance-left-panel.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceLeftPanel, button_ascending);
  gtk_widget_class_bind_template_child (widget_class, FinanceLeftPanel, button_descending);
  gtk_widget_class_bind_template_child (widget_class, FinanceLeftPanel, entry_search);
  gtk_widget_class_bind_template_child (widget_class, FinanceLeftPanel, list_box);

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_button_ascending_clicked);
  gtk_widget_class_bind_template_callback (widget_class, on_button_descending_clicked);
  gtk_widget_class_bind_template_callback (widget_class, on_left_panel_search_changed);
  gtk_widget_class_bind_template_callback (widget_class, on_list_box_row_activated);
}

static void
finance_left_panel_init (FinanceLeftPanel *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->sort = GTK_SORT_ASCENDING;

  gtk_list_box_set_filter_func (GTK_LIST_BOX (self->list_box),
                                (GtkListBoxFilterFunc)list_box_filter_func,
                                (gpointer) self,
                                FALSE);

  gtk_list_box_set_sort_func (GTK_LIST_BOX (self->list_box),
                              (GtkListBoxSortFunc)list_box_sort_func,
                              (gpointer) self,
                              FALSE);
}

/**
 * finance_left_panel_add_row:
 * @self: a #FinanceLeftPanel
 * @widget: a #GtkWidget to add
 *
 * Prepend a widget to the list. If a sort function is set,
 * the widget will actually be inserted at the calculated position
 * and this function has the same effect of gtk_container_add().
 *
 * Since: 1.0
 */
void
finance_left_panel_add_row (FinanceLeftPanel *self,
                            GtkWidget        *widget)
{
  g_return_if_fail (FINANCE_IS_LEFT_PANEL (self));
  g_return_if_fail (widget == NULL);
  g_return_if_fail (GTK_IS_WIDGET (widget));

  gtk_list_box_prepend (GTK_LIST_BOX (self->list_box), widget);
}
