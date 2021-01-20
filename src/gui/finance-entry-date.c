/* finance-entry-date.c
 *
 * Copyright 2020 galetedanilo <galetedanilo@gmail.com>
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

#include "finance-entry-date.h"

struct _FinanceEntryDate
{
  GtkEntry    parent_instance;

  /* The Widgets */
  GtkWidget   *calendar;
  GtkWidget   *popover;

  GDateTime   *date_time;

  gboolean    is_formatting;
};

G_DEFINE_TYPE (FinanceEntryDate, finance_entry_date, GTK_TYPE_ENTRY)

enum {
  PROP_0,
  PROP_DATE,
  PROP_FORMATTING,
  N_PROPS,
};

static GParamSpec *properties[N_PROPS] = { NULL, };

static void
date_update (FinanceEntryDate *self)
{
  GDateTime *date_time;
  GDate     date;

  g_date_clear (&date, 1);

  g_date_set_parse (&date, gtk_entry_get_text (GTK_ENTRY (self)));

  if (!g_date_valid (&date))
    {
      date_time = g_date_time_new_now_local ();

      finance_entry_date_set_date (self, date_time);

      gtk_entry_set_text (GTK_ENTRY (self), "");

      g_clear_pointer (&date_time, g_date_time_unref);

      return;
    }

  date_time = g_date_time_new_local (g_date_get_year (&date),
                                     g_date_get_month (&date),
                                     g_date_get_day (&date),
                                     0, 0, 0);

  finance_entry_date_set_date (self, date_time);

  g_clear_pointer (&date_time, g_date_time_unref);
}

static void
on_automatic_date_formatting (GtkEditable *editable,
                              const gchar *text,
                              gint        length,
                              gint        *position,
                              gpointer    user_data)
{
  if (gtk_entry_get_text_length (GTK_ENTRY (user_data)) > 9)
    {
      g_signal_stop_emission_by_name (editable, "insert_text");

      return;
    }

  if (g_unichar_isdigit (g_utf8_get_char (text)))
    {
      g_signal_handlers_block_by_func (editable,
                                       (gpointer) on_automatic_date_formatting,
                                       user_data);

      if ((*position == 2) || (*position == 5))
        {
          gtk_editable_insert_text (editable, "/", 1, position);
        }

      gtk_editable_insert_text (editable,
                                text,
                                length,
                                position);

      g_signal_handlers_unblock_by_func (editable,
                                         (gpointer) on_automatic_date_formatting,
                                         user_data);
    }

  g_signal_stop_emission_by_name (editable, "insert_text");
}

static void
on_entry_date_icon_press (GtkEntry              *entry,
                          GtkEntryIconPosition  position,
                          GdkEvent              *event,
                          gpointer              user_data)
{
  FinanceEntryDate *self = FINANCE_ENTRY_DATE (user_data);

  (void)event;

  GdkRectangle icon;

  gtk_entry_get_icon_area (entry, position, &icon);

  gtk_popover_set_relative_to (GTK_POPOVER (self->popover),
                               GTK_WIDGET (entry));

  gtk_popover_set_pointing_to (GTK_POPOVER (self->popover),
                               &icon);

  gtk_popover_popup (GTK_POPOVER (self->popover));
}

static void
on_calendar_day_selected (GtkCalendar *calendar,
                          gpointer    user_data)
{
  FinanceEntryDate *self = FINANCE_ENTRY_DATE (user_data);

  guint year, month, day;
  gchar *format_date;

  gtk_calendar_get_date (calendar, &year, &month, &day);

  g_date_time_unref (self->date_time);

  self->date_time = g_date_time_new_local (year,
                                           month + 1,
                                           day,
                                           0, 0, 0);

  format_date = g_date_time_format (self->date_time, "%x");

  g_signal_handlers_block_by_func (self,
                                   on_automatic_date_formatting,
                                   self);

  gtk_entry_set_text (GTK_ENTRY (self), format_date);

  g_signal_handlers_unblock_by_func (self,
                                     on_automatic_date_formatting,
                                     self);

  g_free (format_date);
}

static void
finance_entry_date_prepare (FinanceEntryDate  *self,
                            GDateTime         *date)
{
  gint year, month, day;

  g_date_time_get_ymd (date, &year, &month, &day);

  gtk_calendar_select_month (GTK_CALENDAR (self->calendar), month - 1, year);
  gtk_calendar_select_day (GTK_CALENDAR (self->calendar), day);
}

GtkWidget *
finance_entry_date_new (void)
{
  return g_object_new (FINANCE_TYPE_ENTRY_DATE, NULL);
}

static void
finance_entry_date_finalize (GObject *object)
{
  FinanceEntryDate *self = FINANCE_ENTRY_DATE (object);

  g_clear_pointer (&self->date_time, g_date_time_unref);

  G_OBJECT_CLASS (finance_entry_date_parent_class)->finalize (object);
}

static gboolean
finance_entry_date_focus_out_event (GtkWidget     *widget,
                                    GdkEventFocus *event)
{
  date_update (FINANCE_ENTRY_DATE (widget));

  return GTK_WIDGET_CLASS (finance_entry_date_parent_class)->focus_out_event (widget, event);
}

static void
finance_entry_date_get_property (GObject    *object,
                                 guint      prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  FinanceEntryDate *self = FINANCE_ENTRY_DATE (object);

  switch (prop_id)
    {
    case PROP_DATE:
      g_value_set_boxed (value, finance_entry_date_get_date (self));
      break;

    case PROP_FORMATTING:
      g_value_set_boolean (value, finance_entry_date_get_formatting (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_entry_date_set_property (GObject      *object,
                                 guint        prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  FinanceEntryDate *self = FINANCE_ENTRY_DATE (object);

  switch (prop_id)
    {
    case PROP_DATE:
      finance_entry_date_set_date (self, g_value_get_boxed (value));
      break;

    case PROP_FORMATTING:
      finance_entry_date_set_formatting (self, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finance_entry_date_class_init (FinanceEntryDateClass *klass)
{
  GObjectClass    *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize     = finance_entry_date_finalize;
  object_class->get_property = finance_entry_date_get_property;
  object_class->set_property = finance_entry_date_set_property;

  widget_class->focus_out_event = finance_entry_date_focus_out_event;

  /**
   * FinanceEntryDate::date:
   *
   * The current date set.
   */
  properties[PROP_DATE] = g_param_spec_boxed ("date",
                                              "The current date set",
                                              "The current date set",
                                              G_TYPE_DATE_TIME,
                                              G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  /**
   * FinanceEntryDate::formatting:
   *
   * Enable automatic date formatting
   */
  properties[PROP_FORMATTING] = g_param_spec_boolean ("formatting",
                                                      "Enable automatic date formatting",
                                                      "Enable automatic date formatting",
                                                      FALSE,
                                                      G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties (object_class, N_PROPS, properties);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/finance/gui/finance-entry-date.ui");

  gtk_widget_class_bind_template_child (widget_class, FinanceEntryDate, calendar);
  gtk_widget_class_bind_template_child (widget_class, FinanceEntryDate, popover);

  /* All Signals */
  gtk_widget_class_bind_template_callback (widget_class, on_calendar_day_selected);
  gtk_widget_class_bind_template_callback (widget_class, on_entry_date_icon_press);
  gtk_widget_class_bind_template_callback (widget_class, on_automatic_date_formatting);
}

static void
finance_entry_date_init (FinanceEntryDate *self)
{
  self->date_time     = g_date_time_new_now_local ();
  self->is_formatting = TRUE;

  gtk_widget_init_template (GTK_WIDGET (self));
}

/**
 * finance_entry_date_get_date:
 * @self: a #FinanceEntryDate instance.
 *
 * Get the value of the date.
 *
 * Returns: a #GDateTime with the date.
 *
 * Since: 1.0
 */
GDateTime *
finance_entry_date_get_date (FinanceEntryDate *self)
{
  g_return_val_if_fail (FINANCE_IS_ENTRY_DATE (self), NULL);

  return self->date_time;
}

/**
 * finance_entry_date_set_date:
 * @self: a #FinanceEntryDate object.
 * @date: a valid #GDateTime.
 *
 * Set the value of the entry date.
 *
 * Since: 1.0
 */
void
finance_entry_date_set_date (FinanceEntryDate *self,
                             GDateTime        *date)
{
  g_return_if_fail (FINANCE_IS_ENTRY_DATE (self));

  finance_entry_date_prepare (self, date);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_DATE]);
}

/**
 * finance_entry_date_get_formatting:
 * @self: a #FinanceEntryDate instance.
 *
 * Gets whether the formatting is in its “on” or “off” state.
 *
 * Returns: %TRUE if the automatic date formatting is active, and %FALSE otherwise.
 *
 * Since: 1.0
 */
gboolean
finance_entry_date_get_formatting (FinanceEntryDate *self)
{
  g_return_val_if_fail (FINANCE_IS_ENTRY_DATE (self), FALSE);

  return self->is_formatting;
}

/**
 * finance_entry_date_set_formatting:
 * @self: a #FinanceEntryDate object.
 * @is_formatting: %TRUE if formatting should be active, and %FALSE otherwise.
 *
 * Change automatic date formatting states. %TRUE if formatting should be active, and %FALSE otherwise.
 *
 * Since: 1.0
 */
void
finance_entry_date_set_formatting (FinanceEntryDate *self,
                                   gboolean         is_formatting)
{
  g_return_if_fail (FINANCE_IS_ENTRY_DATE (self));

  if (self->is_formatting == is_formatting)
    return;

  self->is_formatting = is_formatting;

  if (self->is_formatting)
    g_signal_handlers_unblock_by_func (self, on_automatic_date_formatting, self);
  else
    g_signal_handlers_block_by_func (self, on_automatic_date_formatting, self);

  g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_FORMATTING]);
}
