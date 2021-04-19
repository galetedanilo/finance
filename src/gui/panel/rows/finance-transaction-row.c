/* finance-transaction-row.c
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

#include "finance-config.h"

#include "finance-transaction-row.h"

struct _FinanceTransactionRow
{
  GtkListBoxRow   parent_instance;

  /* The Widgets */
  GtkWidget       *amount;
  GtkWidget       *check;
  GtkWidget       *image;
  GtkWidget       *revealer;
  GtkWidget       *title;

  GdkRGBA         *color;
  gchar           *icon;
};

G_DEFINE_TYPE (FinanceTransactionRow, finance_transaction_row, GTK_TYPE_LIST_BOX_ROW)

enum {
  PROP_0,
  PROP_AMOUNT,
  PROP_COLOR,
  PROP_ICON,
  PROP_SELECTED,
  PROP_TITLE,
  N_PROPS,
};


static GParamSpec *properties [N_PROPS] = { NULL, };

static void
create_icon (FinanceTransactionRow *self)
{
  cairo_surface_t *surface;

  surface = finance_utils_create_circle (self->color, 45, self->icon);

  gtk_image_set_from_surface (GTK_IMAGE (self->image_icon), surface);

  g_clear_pointer (&surface, cairo_surface_destroy);
}

/*
 * Show the check button, when the mouse is over the row.
 */
static void
on_row_state_flags_changed (GtkWidget     *object,
                            GtkStateFlags flags,
                            gpointer      user_data)
{
  FinanceTransactionRow *self = FINANCE_TRANSACTION_ROW (user_data);

  flags = gtk_widget_get_state_flags (object);

  if (!gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self->check)))
    {
      gtk_revealer_set_reveal_child (GTK_REVEALER (self->revealer),
                                     (flags & GTK_STATE_FLAG_PRELIGHT) != 0);
    }
}

GtkWidget *
finance_transaction_row_new (void)
{
  return g_object_new (FINANCE_TYPE_TRANSACTION_ROW, NULL);
}

static void
finance_transaction_row_finalize (GObject *object)
{
  FinanceTransactionRow *self = (FinanceTransactionRow *)object;

  g_clear_pointer (&self->icon, g_free);

  G_OBJECT_CLASS (finance_transaction_row_parent_class)->finalize (object);
}

static void
finance_transaction_row_dispose (GObject *object)
{
  FinanceTransactionRow *self = (FinanceTransactionRow *)object;

  g_clear_pointer (&self->color, gdk_rgba_free);

  G_OBJECT_CLASS (finance_transaction_row_parent_class)->dispose (object);
}

static void
finance_transaction_row_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  FinanceTransactionRow *self = FINANCE_TRANSACTION_ROW (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      g_value_set_string (value, finance_transaction_row_get_amount (self));
      break;

    case PROP_COLOR:
      g_value_set_boxed (value, finance_transaction_row_get_color (self));
      break;

    case PROP_ICON:
      g_value_set_string (value, finance_transaction_row_get_icon (self));
      break;

    case PROP_SELECTED:
      g_value_set_boolean (value, finance_transaction_row_get_selected (self));
      break;

    case PROP_TITLE:
      g_value_set_string (value, finance_transaction_row_get_title (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_transaction_row_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  FinanceTransactionRow *self = FINANCE_TRANSACTION_ROW (object);

  switch (prop_id)
    {
    case PROP_AMOUNT:
      finance_transaction_row_set_amount (self, g_value_get_string (value));
      break;

    case PROP_COLOR:
      finance_transaction_row_set_color (self, g_value_get_boxed (value));
      break;

    case PROP_ICON:
      finance_transaction_row_set_icon (self, g_value_get_string (value));
      break;

    case PROP_TITLE:
      finance_transaction_row_set_title (self, g_value_get_string (value));
      break;

    case PROP_SELECTED:
      finance_transaction_row_set_selected (self, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_transaction_row_class_init (FinanceTransactionRowClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize      = finance_transaction_row_finalize;
  object_class->dispose       = finance_transaction_row_dispose;
  object_class->get_property  = finance_transaction_row_get_property;
  object_class->set_property  = finance_transaction_row_set_property;

  /**
   * FinanceTransactionRow::amount:
   *
   * The transaction row amount
   */
  properties[PROP_AMOUNT] =  g_param_spec_string ("amount",
                                                  "Amount",
                                                  "The transaction row amount",
                                                  NULL,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionRow::color:
   *
   * The background color of the icon
   */
  properties[PROP_COLOR] = g_param_spec_boxed ("color",
                                               "Color",
                                               "The background color of the icon",
                                               GDK_TYPE_RGBA,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionRow::icon:
   *
   * The two letters that are part of the icon image
   */
  properties[PROP_ICON] = g_param_spec_string ("icon",
                                               "Icon",
                                               "The two letters that are part of the icon image",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionRow::title:
   *
   * The transaction row title
   */
  properties[PROP_TITLE] = g_param_spec_string ("title",
                                                "Title",
                                                "The transaction row title",
                                                NULL,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceTransactionRow::selected
   *
   * The transaction row selected
   */
  properties[PROP_SELECTED] = g_param_spec_boolean ("selected",
                                                    "Select",
                                                    "The transaction row is selected",
                                                    FALSE,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/pane/rows/finance-transaction-row.ui");

  /* The Widgets */
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionRow, image);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionRow, title);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionRow, amount);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionRow, revealer);
  gtk_widget_class_bind_template_child (widget_class, FinanceTransactionRow, check);

  /* The CallBacks */
  gtk_widget_class_bind_template_callback (widget_class, on_row_state_flags_changed);
}

static void
finance_transaction_row_init (FinanceTransactionRow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->color = finance_utils_random_rgba_color ();

  self->icon = g_strdup ("NW");
}

/**
 * finance_transaction_row_get_icon:
 * @self: a #FinanceTransactionRow
 *
 * Returns the two letters that are part of the icon image
 *
 * Returns: A two-letter string , or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_row_get_icon (FinanceTransactionRow *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_ROW (self), NULL);

  return self->icon;
}

/**
 * finance_transaction_row_set_icon:
 * @self: a #FinanceTransactionRow
 * @icon: the icon to set, as a two-letter string
 *
 * Sets the two letters that are part of the icon image,
 * replacing the current contents.
 *
 * Since:1.0
 */
void
finance_transaction_row_set_icon (FinanceTransactionRow *self,
                                  const gchar           *icon)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_ROW (self));

  g_clear_pointer (&self->icon, g_free);

  self->icon = g_strdup (icon);

  create_icon (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON]);
}

/**
 * finance_transaction_row_get_color:
 * @self: a #FinanceTransactionRow
 *
 * Returns the background color of the icon
 *
 * Returns: (transfer none): a #GdkRGBA with the color
 *
 * Since: 1.0
 */
GdkRGBA *
finance_transaction_row_get_color (FinanceTransactionRow *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_ROW (self), NULL);

  return self->color;
}

/**
 * finance_transaction_row_set_color:
 * @self: a #FinanceTransactionRow
 * @color: a #GdkRGBA
 *
 * Sets the background color of the icon.
 *
 * Since: 1.0
 */
void
finance_transaction_row_set_color (FinanceTransactionRow *self,
                                   const GdkRGBA         *color)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_ROW (self));

  g_clear_pointer (&self->color, gdk_rgba_free);

  self->color = gdk_rgba_copy (color);

  create_icon (self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_COLOR]);
}

/**
 * finance_transaction_row_get_title:
 * @self: a #FinanceTransactionRow
 *
 * Returns the title
 *
 * Returns: The title as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_row_get_title (FinanceTransactionRow *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_ROW (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->title));
}

/**
 * finance_transaction_row_set_title:
 * @self: a #FinanceTransactionRow
 * @title: the title to set, as a string
 *
 * Sets the title, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_transaction_row_set_title (FinanceTransactionRow *self,
                                   const gchar           *title)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_ROW (self));

  gtk_label_set_text (GTK_LABEL (self->title), title);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TITLE]);
}

/**
 * finance_transaction_row_get_amount:
 * @self: a #FinanceTransactionRow
 *
 * Returns the amount as a string
 *
 * Returns: The amount as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_transaction_row_get_amount (FinanceTransactionRow *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_ROW (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->amount));
}

/**
 * finance_transaction_row_set_amount:
 * @self: a #FinanceTransactionRow
 * @amount: the amount to set, as a string
 *
 * Sets the amount, replacing the current contents
 *
 * Since: 1.0
 */
void
finance_transaction_row_set_amount (FinanceTransactionRow *self,
                                    const gchar           *amount)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_ROW (self));

  gtk_label_set_text (GTK_LABEL (self->amount), amount);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_AMOUNT]);
}

/**
 * finance_transaction_row_get_selected:
 * @self: a #FinanceTransactionRow
 *
 * Returns whether the row is in its “on” or “off” state
 *
 * Returns: #TRUE if the row is selected, and #FALSE otherwise
 *
 * Since: 1.0
 */
gboolean
finance_transaction_row_get_selected (FinanceTransactionRow *self)
{
  g_return_val_if_fail (FINANCE_IS_TRANSACTION_ROW (self), FALSE);

  return gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self->check));
}

/**
 * finance_transaction_row_set_selected:
 * @self: a #FinanceTransactionRow
 * @selected: #TRUE if row is to be selected, and #FALSE otherwise
 *
 * Changes the state of #FinanceTransactionRow to the desired one
 *
 * Since: 1.0
 */
void
finance_transaction_row_set_selected (FinanceTransactionRow *self,
                                      gboolean               selected)
{
  g_return_if_fail (FINANCE_IS_TRANSACTION_ROW (self));

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->check), selected);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_SELECTED]);
}
