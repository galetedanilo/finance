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
 * finance_utils_rgba_get_color:
 *
 * Returns a color from the GNOME Human Interface Guidelines color palette.
 *
 * Returns: (transfer full): a #GdkRGBA
 *
 * Since: 1.0
 */
GdkRGBA *
finance_utils_rgba_get_color (void)
{
  GdkRGBA color;
  int     id;

  /**
   * The Gnome palette colors
   * By GNOME Human Interface Guidelines
   * See: https://gitlab.gnome.org/Community/Design/HIG-app-icons/blob/master/GNOME%20HIG.gpl
   */
  int rgb[45][3] = {
    {153, 193, 241},
    { 98, 160, 234},
    { 53, 132, 228},
    { 28, 113, 216},
    { 26,  95, 180},
    {143, 240, 164},
    { 87, 227, 137},
    { 51, 209, 122},
    { 46, 194, 126},
    { 38, 162, 105},
    {249, 240, 107},
    {248, 228,  92},
    {246, 211,  45},
    {245, 194,  17},
    {229, 165,  10},
    {255, 190, 111},
    {255, 163,  72},
    {255, 120,   0},
    {230,  97,   0},
    {198,  70,   0},
    {246,  97,  81},
    {237,  51,  59},
    {224,  27,  36},
    {192,  28,  40},
    {165,  29,  45},
    {220, 138, 221},
    {192,  97, 203},
    {145,  65, 172},
    {129,  61, 156},
    { 97,  53, 131},
    {205, 171, 143},
    {181, 131,  90},
    {152, 106,  68},
    {134,  94,  60},
    { 99,  69,  44},
    {255, 255, 255},
    {246, 245, 244},
    {222, 221, 218},
    {192, 191, 188},
    {154, 153, 150},
    {119, 118, 123},
    { 94,  92, 100},
    { 61,  56,  70},
    { 36,  31,  49},
    {  0,   0,   0}
  };

  id = g_random_int_range (0, 44);

  color.red   = rgb [id] [0] / 255.;
  color.green = rgb [id] [1] / 255.;
  color.blue  = rgb [id] [2] / 255.;
  color.alpha = 1.0;

  return gdk_rgba_copy (&color);
}

/**
 * finance_utils_create_circle_with_color:
 * @color: a #GdkRGBA.
 * @size: a #gint.
 *
 * Creates a circular surface filled with @color. The
 * surface is always @size x @size.
 *
 * Returns: (transfer full): a #cairo_surface_t
 */
cairo_surface_t*
finance_utils_create_circle_with_color (const GdkRGBA *color,
                                        gint          size)
{
  cairo_surface_t *surface;
  cairo_t         *cr;

  surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, size, size);
  cr = cairo_create (surface);

  cairo_set_source_rgba (cr,
                         color->red,
                         color->green,
                         color->blue,
                         color->alpha);

  cairo_arc (cr, size / 2.0, size / 2.0, size / 2.0, 0., 2 * G_PI);
  cairo_fill (cr);
  cairo_destroy (cr);

  return surface;
}

