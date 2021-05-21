/* finance-window.c
 *
 * Copyright 2020 galetedanilo
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
 */

#include <glib/gi18n.h>
#include "finance-config.h"

#include "finance-view.h"
#include "finance-window.h"

struct _FinanceWindow
{
  HdyApplicationWindow  parent_instance;

  /* Template widgets */
  GtkWidget   *box_content;
  GtkWidget   *box_content_left;
  GtkWidget   *header_bar_right;
  GtkWidget   *header_bar_squeezer;
  GtkWidget   *label_title;
  GtkWidget   *leaflet;
  GtkWidget   *left_panel;
  GtkWidget   *scrolled_window_transaction_editor;
  GtkWidget   *stack;
  GtkWidget   *stack_switcher_top;
  GtkWidget   *transaction_editor;
  GtkWidget   *transaction_view;
  GtkWidget   *view_switcher_bottom;

  GSettings   *settings;
  GObject     *controller_transactions;
};

static void     finance_window_prepare_new_transaction      (FinanceWindow *self);

G_DEFINE_TYPE (FinanceWindow, finance_window, HDY_TYPE_APPLICATION_WINDOW)

static void
on_add_credit_clicked (GtkButton *button,
                       gpointer   user_data)
{
  FinanceWindow *self = FINANCE_WINDOW (user_data);

  (void)button;

  finance_window_prepare_new_transaction (self);
}

static void
on_add_debit_clicked (GtkButton *button,
                      gpointer   user_data)
{
  FinanceWindow *self = FINANCE_WINDOW (user_data);

  (void)button;

  finance_window_prepare_new_transaction (self);
}

static void
on_cancel_button_clicked (GtkButton *button,
                          gpointer   user_data)
{
  FinanceWindow *self = FINANCE_WINDOW (user_data);

  (void)button;

  hdy_squeezer_set_child_enabled (HDY_SQUEEZER (self->header_bar_squeezer),
                                  self->stack_switcher_top, TRUE);

  gtk_widget_set_sensitive (self->transaction_editor, FALSE);
  gtk_label_set_text (GTK_LABEL (self->label_title), _("Finance"));
  gtk_stack_set_visible_child_name (GTK_STACK (self->stack), "home");
}

static void
on_headerbar_squeezer_notify (GObject     *object,
                              GParamSpec  *pspec,
                              gpointer    user_data)
{
  FinanceWindow *self = FINANCE_WINDOW (user_data);

  (void)pspec;

  hdy_view_switcher_bar_set_reveal (HDY_VIEW_SWITCHER_BAR (self->view_switcher_bottom),
                                    hdy_squeezer_get_visible_child (HDY_SQUEEZER (object))
                                    != self->stack_switcher_top);
}

static void
on_swipe_back_clicked (GtkButton *button,
                       gpointer   user_data)
{
  FinanceWindow *self = FINANCE_WINDOW (user_data);

  (void)button;

  hdy_leaflet_set_visible_child (HDY_LEAFLET (self->leaflet), self->box_content_left);
}

static void
on_swipe_forward_clicked (GtkButton *button,
                          gpointer   user_data)
{
  FinanceWindow *self = FINANCE_WINDOW (user_data);

  (void)button;

  hdy_leaflet_set_visible_child (HDY_LEAFLET (self->leaflet), self->box_content);
}

static void
finance_window_prepare_new_transaction (FinanceWindow *self)
{
  hdy_squeezer_set_child_enabled (HDY_SQUEEZER (self->header_bar_squeezer),
                                  self->stack_switcher_top, FALSE);

  finance_transaction_editor_clear (FINANCE_TRANSACTION_EDITOR (self->transaction_editor));

  gtk_widget_set_sensitive (self->transaction_editor, TRUE);
  gtk_label_set_text (GTK_LABEL (self->label_title), _("New"));
  hdy_leaflet_set_visible_child (HDY_LEAFLET (self->leaflet), self->box_content);
  gtk_stack_set_visible_child (GTK_STACK (self->stack), self->scrolled_window_transaction_editor);
}

static void
finance_window_dispose (GObject *object)
{
  FinanceWindow *self = FINANCE_WINDOW (object);

  g_clear_object (&self->settings);
  g_clear_object (&self->controller_transactions);

  G_OBJECT_CLASS (finance_window_parent_class)->dispose (object);
}

static void
finance_window_class_init (FinanceWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  g_type_ensure (FINANCE_TYPE_LEFT_PANEL);
  g_type_ensure (FINANCE_TYPE_TRANSACTION_EDITOR);
  g_type_ensure (FINANCE_TYPE_TRANSACTION_VIEW);

  G_OBJECT_CLASS (klass)->dispose     = finance_window_dispose;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/gui/finance-window.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, box_content);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, box_content_left);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, header_bar_right);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, header_bar_squeezer);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, label_title);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, leaflet);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, left_panel);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, scrolled_window_transaction_editor);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, stack);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, stack_switcher_top);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, transaction_editor);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, transaction_view);
  gtk_widget_class_bind_template_child (widget_class, FinanceWindow, view_switcher_bottom);

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_add_credit_clicked);
  gtk_widget_class_bind_template_callback (widget_class, on_add_debit_clicked);
  gtk_widget_class_bind_template_callback (widget_class, on_cancel_button_clicked);
  gtk_widget_class_bind_template_callback (widget_class, on_headerbar_squeezer_notify);
  gtk_widget_class_bind_template_callback (widget_class, on_swipe_back_clicked);
  gtk_widget_class_bind_template_callback (widget_class, on_swipe_forward_clicked);
}

static void
finance_window_init (FinanceWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  hdy_init();

  self->settings = g_settings_new ("org.gnome.finance");

  self->controller_transactions = g_object_new (FINANCE_TYPE_TRANSACTION_VIEW_CONTROLLER,
                                                "pane", self->left_panel,
                                                "view", self->transaction_view,
                                                NULL);

  finance_transaction_view_controller_startup (self->controller_transactions);
}
