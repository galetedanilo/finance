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

  gboolean    is_formatting;
};

G_DEFINE_TYPE (FinanceEntryDate, finance_entry_date, GTK_TYPE_ENTRY)

enum {
  PROP_0,
  PROP_FORMATTING,
  N_PROPS,
};

static GParamSpec *properties[N_PROPS] = { NULL, };

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
          gtk_editable_insert_text (editable, "//", length, position);
        }

      gtk_editable_insert_text (editable,
                                text,
                                length,
                                position);

      g_signal_handlers_unblock_by_func (editable,
                                         (gpointer) on_automatic_date_formatting,
                                         user_data);
    }
  else if ((g_strcmp0 (text, "/") == 0) && ((*position == 2) || (*position == 5)))
    {
      g_signal_handlers_block_by_func (editable,
                                       (gpointer) on_automatic_date_formatting,
                                       user_data);

      gchar *check = gtk_editable_get_chars (editable, *position, *position + 1);

      if (!(g_strcmp0 (check, "/") == 0))
        gtk_editable_insert_text (editable,
                                  text,
                                  length,
                                  position);

      if (check)
        g_free (check);

      g_signal_handlers_unblock_by_func (editable,
                                         (gpointer) on_automatic_date_formatting,
                                         user_data);
    }

  g_signal_stop_emission_by_name (editable, "insert_text");
}

static void
on_entry_state_flags_changed (GtkWidget     *widget,
                              GtkStateFlags flags,
                              gpointer      user_data)
{
  (void)user_data;

  GDateTime *datetime;
  GDate     *date;
  gint      year, month, day;
  gchar     *str;

  if (flags & (GTK_STATE_FLAG_DIR_LTR | GTK_STATE_FLAG_FOCUSED))
    {
      date = g_date_new ();

      g_date_set_parse (date, gtk_entry_get_text (GTK_ENTRY (widget)));

      if (!g_date_valid (date))
        {
          gtk_entry_set_text (GTK_ENTRY (widget), "");

          g_date_free (date);

          return;
        }

      year  = g_date_get_year (date);
      month = g_date_get_month (date);
      day   = g_date_get_day (date);

      datetime = g_date_time_new_local (year, month, day, 1, 1, 1);

      str = g_date_time_format (datetime, "%x");

      gtk_entry_set_text (GTK_ENTRY (widget), str);

      g_free (str);
      g_date_time_unref (datetime);
      g_date_free (date);
    }
}

static void
on_entry_date_icon_press (GtkEntry              *entry,
                          GtkEntryIconPosition  position,
                          GdkEvent              *event,
                          gpointer              user_data)
{
  FinanceEntryDate *self = FINANCE_ENTRY_DATE (user_data);

  (void)event;

  GdkRectangle  icon;
  GDateTime     *datetime;
  GDate         *date;
  gint          day, month, year;

  gtk_entry_get_icon_area (entry, position, &icon);

  gtk_popover_set_relative_to (GTK_POPOVER (self->popover),
                               GTK_WIDGET (entry));

  gtk_popover_set_pointing_to (GTK_POPOVER (self->popover),
                               &icon);

  if (gtk_entry_get_text_length (entry))
    {
      date = g_date_new ();

      g_date_set_parse (date, gtk_entry_get_text (entry));

      if (!g_date_valid (date))
        {
          datetime = g_date_time_new_now_local ();

          g_date_time_get_ymd (datetime, &year, &month, &day);

          gtk_calendar_select_month (GTK_CALENDAR (self->calendar),
                                     (month - 1),
                                     year);

          gtk_calendar_select_day (GTK_CALENDAR (self->calendar),
                                   day);

          gtk_popover_popup (GTK_POPOVER (self->popover));

          g_date_time_unref (datetime);
          g_date_free (date);

          return;
        }

      year	= g_date_get_year (date);
      month	= g_date_get_month (date);
      day   = g_date_get_day (date);

      gtk_calendar_select_month (GTK_CALENDAR (self->calendar),
                                 (month - 1),
                                 year);

      gtk_calendar_select_day (GTK_CALENDAR (self->calendar),
                               day);

      gtk_popover_popup (GTK_POPOVER (self->popover));

      g_date_free (date);

      return;
    }

  datetime = g_date_time_new_now_local ();

  g_date_time_get_ymd (datetime, &year, &month, &day);

  gtk_calendar_select_month (GTK_CALENDAR (self->calendar),
                             (month - 1),
                             year);

  gtk_calendar_select_day (GTK_CALENDAR (self->calendar),
                           day);

  gtk_popover_popup (GTK_POPOVER (self->popover));

  g_date_time_unref (datetime);
}

static void
on_calendar_day_selected (GtkCalendar *calendar,
                          gpointer    user_data)
{
  FinanceEntryDate *self = FINANCE_ENTRY_DATE (user_data);

  GDateTime *date;
  guint day, month, year;
  gchar *format_date;

  gtk_calendar_get_date (calendar, &year, &month, &day);

  date = g_date_time_new_local (year, month + 1, day, 1, 1, 1);

  format_date = g_date_time_format (date, "%x");

  gtk_entry_set_text (GTK_ENTRY (self), format_date);

  g_free (format_date);

  g_date_time_unref (date);
}

static void
on_calendar_day_selected_double_click (GtkCalendar  *calendar,
                                       gpointer     user_data)
{
  FinanceEntryDate *self = FINANCE_ENTRY_DATE (user_data);

  (void)calendar;

  gtk_popover_popdown (GTK_POPOVER (self->popover));
}

GtkWidget *
finance_entry_date_new (void)
{
  return g_object_new (FINANCE_TYPE_ENTRY_DATE, NULL);
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

  object_class->get_property = finance_entry_date_get_property;
  object_class->set_property = finance_entry_date_set_property;

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

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Finance/gui/finance-entry-date.ui");

  gtk_widget_class_bind_template_child (widget_class, FinanceEntryDate, calendar);
  gtk_widget_class_bind_template_child (widget_class, FinanceEntryDate, popover);

  /* All Signals */
  gtk_widget_class_bind_template_callback (widget_class, on_calendar_day_selected);
  gtk_widget_class_bind_template_callback (widget_class, on_calendar_day_selected_double_click);
  gtk_widget_class_bind_template_callback (widget_class, on_entry_date_icon_press);
  gtk_widget_class_bind_template_callback (widget_class, on_entry_state_flags_changed);
  gtk_widget_class_bind_template_callback (widget_class, on_automatic_date_formatting);
}

static void
finance_entry_date_init (FinanceEntryDate *self)
{
  self->is_formatting = TRUE;

  gtk_widget_init_template (GTK_WIDGET (self));
}

/**
 * finance_entry_date_get_formatting:
 * @self: a #FinanceEntryDate instance.
 *
 * Gets whether the formatting is in its “on” or “off” state.
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
 * Change automatic date formatting states.
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

