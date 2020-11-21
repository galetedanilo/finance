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

  GtkWidget   *calendar;
  GtkWidget   *popover;
};

G_DEFINE_TYPE (FinanceEntryDate, finance_entry_date, GTK_TYPE_ENTRY)

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
  GDate					*date;
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
finance_entry_date_class_init (FinanceEntryDateClass *klass)
{
  GtkWidgetClass  *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Finance/gui/finance-entry-date.ui");

  gtk_widget_class_bind_template_child (widget_class, FinanceEntryDate, calendar);
  gtk_widget_class_bind_template_child (widget_class, FinanceEntryDate, popover);

  /* All Signals */
  gtk_widget_class_bind_template_callback (widget_class, on_calendar_day_selected);
  gtk_widget_class_bind_template_callback (widget_class, on_calendar_day_selected_double_click);
  gtk_widget_class_bind_template_callback (widget_class, on_entry_date_icon_press);
  gtk_widget_class_bind_template_callback (widget_class, on_entry_state_flags_changed);
}

static void
finance_entry_date_init (FinanceEntryDate *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}