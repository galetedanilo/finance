/* finance-utils.c
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

#include "finance-utils.h"

/**
 * finance_utils_random_rgba_color:
 *
 * Returns a color from the GNOME Human Interface Guidelines color palette.
 *
 * Returns: (transfer full): a #GdkRGBA
 *
 * Since: 1.0
 */
GdkRGBA *
finance_utils_random_rgba_color (void)
{
  GdkRGBA color;
  int     id;

  /**
   * The Gnome palette colors
   * By GNOME Human Interface Guidelines
   * See: https://gitlab.gnome.org/Community/Design/HIG-app-icons/blob/master/GNOME%20HIG.gpl
   */
  int rgb[24][3] = {
    { 53, 132, 228},
    { 28, 113, 216},
    { 26,  95, 180},
    { 51, 209, 122},
    { 46, 194, 126},
    { 38, 162, 105},
    {246, 211,  45},
    {245, 194,  17},
    {229, 165,  10},
    {255, 120,   0},
    {230,  97,   0},
    {198,  70,   0},
    {224,  27,  36},
    {192,  28,  40},
    {165,  29,  45},
    { 97,  53, 131},
    {205, 171, 143},
    {181, 131,  90},
    { 99,  69,  44},
    {255, 255, 255},
    {246, 245, 244},
    {119, 118, 123},
    { 94,  92, 100},
    { 61,  56,  70},
  };

  id = g_random_int_range (0, 23);

  color.red   = rgb [id] [0] / 255.;
  color.green = rgb [id] [1] / 255.;
  color.blue  = rgb [id] [2] / 255.;
  color.alpha = 1.0;

  return gdk_rgba_copy (&color);
}

/**
 * finance_utils_create_circle_transaction:
 * @color: a #GdkRGBA.
 * @str: a #gchar, to define the letters in the icon.
 *
 * Creates a circular surface filled with @color.
 *
 * Returns: (transfer full): a #cairo_surface_t
 *
 * Since: 1.0
 */
cairo_surface_t *
finance_utils_create_circle_transaction (const GdkRGBA *color,
                                         const gchar   *str)
{
  cairo_surface_t *surface;
  cairo_t         *cr;
  gint            arc_size;
  gdouble         font_size;

  arc_size = 140;
  font_size = 50.0;

  surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, arc_size, arc_size);
  cr = cairo_create (surface);

  cairo_select_font_face (cr, "Sans",
                          CAIRO_FONT_SLANT_NORMAL,
                          CAIRO_FONT_WEIGHT_BOLD);

  cairo_set_font_size (cr, font_size);

  cairo_arc (cr,
             arc_size / 2.0,
             arc_size / 2.0,
             arc_size / 2.0,
             0.0,
             2 * G_PI);

  cairo_set_source_rgba (cr,
                         color->red,
                         color->green,
                         color->blue,
                         color->alpha);
  cairo_fill (cr);

  cairo_move_to (cr, 30.0 , 85.0);

  cairo_text_path (cr, str);
  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_fill (cr);

  cairo_destroy (cr);

  return surface;
}

