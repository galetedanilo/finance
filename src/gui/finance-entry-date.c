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
on_entry_date_move_focus (GtkWidget *widget,
                          GdkEvent  *event,
                          gpointer  user_data)
{
  FinanceEntryDate *self = FINANCE_ENTRY_DATE (user_data);

  (void)widget;
  (void)event;

  GDate parse_date;

  g_date_clear (&parse_date, 1);

  g_date_set_parse (&parse_date,
                    gtk_entry_get_text (GTK_ENTRY (self)));

  /* if the date is not valid reset the entry to empty */
  if (!g_date_valid (&parse_date))
    gtk_entry_set_text (GTK_ENTRY (self), "");
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
  GDateTime     *time;
  gint          day, month, year;

  gtk_entry_get_icon_area (entry, position, &icon);

  gtk_popover_set_relative_to (GTK_POPOVER (self->popover),
                               GTK_WIDGET (entry));

  gtk_popover_set_pointing_to (GTK_POPOVER (self->popover),
                               &icon);

  time = g_date_time_new_now_local ();

  g_date_time_get_ymd (time,
                       &year,
                       &month,
                       &day);

  gtk_calendar_select_month (GTK_CALENDAR (self->calendar),
                             (month - 1),
                             year);

  gtk_calendar_select_day (GTK_CALENDAR (self->calendar),
                           day);

  gtk_popover_popup (GTK_POPOVER (self->popover));

  g_date_time_unref (time);
}


static void
on_calendar_day_selected (GtkCalendar *calendar,
                          gpointer    user_data)
{
  FinanceEntryDate *self = FINANCE_ENTRY_DATE (user_data);

  (void)calendar;

  GDateTime *time;
  guint     day, month, year;

  gtk_calendar_get_date (calendar,
                         &year,
                         &month,
                         &day);

  time = g_date_time_new_local (year,
                                month + 1,
                                day, 1, 1, 1);

  gtk_entry_set_text (GTK_ENTRY (self),
                      g_date_time_format (time, "%x"));

  g_date_time_unref (time);
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
  gtk_widget_class_bind_template_callback (widget_class, on_entry_date_move_focus);
}

static void
finance_entry_date_init (FinanceEntryDate *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
