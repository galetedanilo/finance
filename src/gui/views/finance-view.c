/* finance-view.c
 *
 * Copyright 2021 Danilo Fernandes Galete <galetedanilo@gmail.com>
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

#include "finance-view.h"

G_DEFINE_INTERFACE (FinanceView, finance_view, GTK_TYPE_WIDGET)

static void
finance_view_default_init (FinanceViewInterface *iface)
{
  (void)iface;
}

void
finance_view_add_child (FinanceView *view,
                        GtkWidget   *widget)
{
  g_return_if_fail (FINANCE_IS_VIEW (view));
  g_return_if_fail (widget == NULL);
  g_return_if_fail (GTK_IS_WIDGET (widget));

  g_return_if_fail (FINANCE_VIEW_GET_IFACE (view)->add_child);

  FINANCE_VIEW_GET_IFACE (view)->add_child (view, widget);
}
