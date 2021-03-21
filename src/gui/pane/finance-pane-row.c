/* finance-pane-row.c
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

#include "finance-pane-row.h"

struct _FinancePaneRow
{
  GtkListBoxRow   parent_instance;

  /* The Widgets */
  GtkWidget       *image;
  GtkWidget       *title;
  GtkWidget       *amount;
  GtkWidget       *revealer;
  GtkWidget       *check;

  GdkRGBA         *color;
  gchar           *icon;
};

G_DEFINE_TYPE (FinancePaneRow, finance_pane_row, GTK_TYPE_LIST_BOX_ROW)

enum {
  PROP_0,
  PROP_ICON,
  PROP_COLOR,
  PROP_TITLE,
  PROP_AMOUNT,
  PROP_SELECTED,
  N_PROPS,
};

enum {
  CHANGE,
  N_SIGNALS
};

static GParamSpec *properties [N_PROPS] = { NULL, };

static guint signals[N_SIGNALS] = { 0, };

/*
 * Show the check button, when the mouse is over the row.
 */
static void
on_row_state_flags_changed (GtkWidget     *object,
                            GtkStateFlags flags,
                            gpointer      user_data)
{
  FinancePaneRow *self = FINANCE_PANE_ROW (user_data);

  flags = gtk_widget_get_state_flags (object);

  if (!gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self->check)))
    {
      gtk_revealer_set_reveal_child (GTK_REVEALER (self->revealer),
                                     (flags & GTK_STATE_FLAG_PRELIGHT) != 0);
    }
}

static void
on_check_toggled (GtkToggleButton *button,
                  gpointer        user_data)
{
  FinancePaneRow *self = FINANCE_PANE_ROW (user_data);

  (void)button;

  g_signal_emit(self, signals[CHANGE], 0);
}

GtkWidget *
finance_pane_row_new (void)
{
  return g_object_new (FINANCE_TYPE_PANE_ROW, NULL);
}

static void
finance_pane_row_finalize (GObject *object)
{
  FinancePaneRow *self = (FinancePaneRow *)object;

  g_clear_pointer (&self->icon, g_free);

  G_OBJECT_CLASS (finance_pane_row_parent_class)->finalize (object);
}

static void
finance_pane_row_dispose (GObject *object)
{
  FinancePaneRow *self = (FinancePaneRow *)object;

  g_clear_pointer (&self->color, gdk_rgba_free);

  G_OBJECT_CLASS (finance_pane_row_parent_class)->dispose (object);
}

static void
finance_pane_row_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  FinancePaneRow *self = FINANCE_PANE_ROW (object);

  switch (prop_id)
    {
    case PROP_ICON:
      g_value_set_string (value, finance_pane_row_get_icon (self));
      break;

    case PROP_COLOR:
      g_value_set_boxed (value, finance_pane_row_get_color (self));
      break;

    case PROP_TITLE:
      g_value_set_string (value, finance_pane_row_get_title (self));
      break;

    case PROP_AMOUNT:
      g_value_set_string (value, finance_pane_row_get_amount (self));
      break;

    case PROP_SELECTED:
      g_value_set_boolean (value, finance_pane_row_is_selected (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_pane_row_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  FinancePaneRow *self = FINANCE_PANE_ROW (object);

  switch (prop_id)
    {
    case PROP_ICON:
      finance_pane_row_set_icon (self, g_value_get_string (value));
      break;

    case PROP_COLOR:
      finance_pane_row_set_color (self, g_value_get_boxed (value));
      break;

    case PROP_TITLE:
      finance_pane_row_set_title (self, g_value_get_string (value));
      break;

    case PROP_AMOUNT:
      finance_pane_row_set_amount (self, g_value_get_string (value));
      break;

    case PROP_SELECTED:
      finance_pane_row_set_selected (self, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_pane_row_class_init (FinancePaneRowClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize      = finance_pane_row_finalize;
  object_class->dispose       = finance_pane_row_dispose;
  object_class->get_property  = finance_pane_row_get_property;
  object_class->set_property  = finance_pane_row_set_property;

  /**
   * FinancePaneRow::change:
   *
   * Emitted when the row is change
   */
  signals[CHANGE] = g_signal_new ("change",
                                  FINANCE_TYPE_PANE_ROW,
                                  G_SIGNAL_RUN_LAST,
                                  0,
                                  NULL, NULL, NULL,
                                  G_TYPE_NONE,
                                  0);

  /**
   * FinancePaneRow::icon:
   *
   * The two letters that are part of the icon image
   */
  properties[PROP_ICON] = g_param_spec_string ("icon",
                                               "Icon",
                                               "The two letters that are part of the icon image",
                                               NULL,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePaneRow::color:
   *
   * The background color of the icon
   */
  properties[PROP_COLOR] = g_param_spec_boxed ("color",
                                               "Color",
                                               "The background color of the icon",
                                               GDK_TYPE_RGBA,
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePaneRow::title:
   *
   * The pane row title
   */
  properties[PROP_TITLE] = g_param_spec_string ("title",
                                                "Title",
                                                "The pane row title",
                                                NULL,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePaneRow::amount:
   *
   * The pane row amount
   */
  properties[PROP_AMOUNT] =  g_param_spec_string ("amount",
                                                  "Amount",
                                                  "The pane row amount",
                                                  NULL,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinancePaneRow::selected
   *
   * The pane row selected
   */
  properties[PROP_SELECTED] = g_param_spec_boolean ("selected",
                                                    "Select",
                                                    "The pane row is selected",
                                                    FALSE,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/pane/finance-pane-row.ui");

  gtk_widget_class_bind_template_child (widget_class, FinancePaneRow, image);
  gtk_widget_class_bind_template_child (widget_class, FinancePaneRow, title);
  gtk_widget_class_bind_template_child (widget_class, FinancePaneRow, amount);
  gtk_widget_class_bind_template_child (widget_class, FinancePaneRow, revealer);
  gtk_widget_class_bind_template_child (widget_class, FinancePaneRow, check);

  /* All signals */
  gtk_widget_class_bind_template_callback (widget_class, on_row_state_flags_changed);
  gtk_widget_class_bind_template_callback (widget_class, on_check_toggled);
}

static void
finance_pane_row_init (FinancePaneRow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  self->color = finance_utils_random_rgba_color ();
}

/**
 * finance_pane_row_get_icon:
 * @self: a #FinancePaneRow object.
 *
 * Returns the two letters that are part of the icon image.
 *
 * Returns: A two-letter string , or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pane_row_get_icon (FinancePaneRow *self)
{
  g_return_val_if_fail (FINANCE_IS_PANE_ROW (self), NULL);

  return self->icon;
}

/**
 * finance_pane_row_set_icon:
 * @self: a #FinancePaneRow instance.
 * @icon: the icon to set, as a two-letter string.
 *
 * Sets the two letters that are part of the icon image,
 * replacing the current contents.
 *
 * Since:1.0
 */
void
finance_pane_row_set_icon (FinancePaneRow *self,
                           const gchar    *icon)
{
  g_return_if_fail (FINANCE_IS_PANE_ROW (self));

  cairo_surface_t *surface;

  g_free (self->icon);

  self->icon = g_strdup (icon);

  surface = finance_utils_create_circle (self->color, 45, self->icon);

  gtk_image_set_from_surface (GTK_IMAGE (self->image), surface);

  g_clear_pointer (&surface, cairo_surface_destroy);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_ICON]);
}

/**
 * finance_pane_row_get_color:
 * @self: a #FinancePaneRow object.
 *
 * Returns the background color of the icon.
 *
 * Returns: (transfer none): a #GdkRGBA with the color.
 *
 * Since: 1.0
 */
GdkRGBA *
finance_pane_row_get_color (FinancePaneRow *self)
{
  g_return_val_if_fail (FINANCE_IS_PANE_ROW (self), NULL);

  return self->color;
}

/**
 * finance_pane_row_set_color:
 * @self: a #FinancePaneRow instance.
 * @color: a #GdkRGBA.
 *
 * Sets the background color of the icon.
 *
 * Since: 1.0
 */
void
finance_pane_row_set_color (FinancePaneRow *self,
                            const GdkRGBA  *color)
{
  g_return_if_fail (FINANCE_IS_PANE_ROW (self));

  gdk_rgba_free (self->color);

  self->color = gdk_rgba_copy (color);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_COLOR]);
}

/**
 * finance_pane_row_get_title:
 * @self: a #FinancePaneRow object.
 *
 * Returns the title.
 *
 * Returns: The title as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pane_row_get_title (FinancePaneRow *self)
{
  g_return_val_if_fail (FINANCE_IS_PANE_ROW (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->title));
}

/**
 * finance_pane_row_set_title:
 * @self: a #FinancePaneRow instance.
 * @title: the title to set, as a string.
 *
 * Sets the title, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pane_row_set_title (FinancePaneRow *self,
                            const gchar    *title)
{
  g_return_if_fail (FINANCE_IS_PANE_ROW (self));

  gtk_label_set_text (GTK_LABEL (self->title), title);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_TITLE]);
}

/**
 * finance_pane_row_get_amount:
 * @self: a #FinancePaneRow object.
 *
 * Returns the amount as a string.
 *
 * Returns: The amount as a string, or %NULL.
 * This string points to internally allocated storage in the object
 * and must not be freed, modified or stored.
 *
 * Since: 1.0
 */
const gchar *
finance_pane_row_get_amount (FinancePaneRow *self)
{
  g_return_val_if_fail (FINANCE_IS_PANE_ROW (self), NULL);

  return gtk_label_get_text (GTK_LABEL (self->amount));
}

/**
 * finance_pane_row_set_amount:
 * @self: a #FinancePaneRow instance.
 * @amount: the amount to set, as a string.
 *
 * Sets the amount, replacing the current contents.
 *
 * Since: 1.0
 */
void
finance_pane_row_set_amount (FinancePaneRow *self,
                             const gchar    *amount)
{
  g_return_if_fail (FINANCE_IS_PANE_ROW (self));

  gtk_label_set_text (GTK_LABEL (self->amount), amount);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_AMOUNT]);
}

/**
 * finance_pane_row_is_selected:
 * @self: a #FinancePaneRow object.
 *
 * Returns whether the row is in its “on” or “off” state.
 *
 * Returns: #TRUE if the row is selected, and #FALSE otherwise
 *
 * Since: 1.0
 */
gboolean
finance_pane_row_is_selected (FinancePaneRow *self)
{
  g_return_val_if_fail (FINANCE_IS_PANE_ROW (self), FALSE);

  return gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self->check));
}

/**
 * finance_pane_row_set_selected:
 * @self: a #FinancePaneRow instance.
 * @selected: #TRUE if row is to be selected, and #FALSE otherwise.
 *
 * Changes the state of #FinancePaneRow to the desired one.
 *
 * Since: 1.0
 */
void
finance_pane_row_set_selected (FinancePaneRow *self,
                               gboolean       selected)
{
  g_return_if_fail (FINANCE_IS_PANE_ROW (self));

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->check), selected);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_SELECTED]);
}
