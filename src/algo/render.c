/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:55:36 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/30 13:24:55 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "algo.h"

/**
 * @brief Sets a pixel in an image to a specified color.
 *
 * This function converts a color structure (RGB) into a 24-bit integer value
 * according to the image's endian format, then writes it into the image memory
 * at the given offset.
 *
 * @param color Pointer to the color structure containing RGB values.
 * @param image The image data structure where the pixel will be set.
 * @param offset The pixel index in the image memory array.
 */
static void	color_pixel(t_color color, t_img_data image, int offset)
{
	int	rgba;

	if (image.endian == 1)
		rgba = (color.rgb[0] << 16) | (color.rgb[1] << 8) | color.rgb[2];
	else
		rgba = (color.rgb[2] << 16) | (color.rgb[1] << 8) | color.rgb[0];
	((int *)image.mem)[offset] = rgba;
}

/**
 * @brief Calculates the starting Y coordinate on a texture for a wall slice.
 *
 * This function computes the initial Y position on a texture image that
 * corresponds to the first pixel to render for a given wall. It also calculates
 * the vertical step size to increment the texture coordinate for each screen
 * pixel.
 *
 * @param wall The wall structure containing the projected height on screen.
 * @param y_step Pointer to a double that will store the texture Y increment per
 * screen pixel.
 * @param text_height Height of the texture image in pixels.
 * @return The starting Y coordinate on the texture for the first rendered pixel.
 */
static double	texture_start_y(t_wall wall, double *y_step, int text_height)
{
	double	start_y;

	*y_step = (double)text_height / (double)wall.height;
	start_y = 0.0;
	if (wall.height > WINDOW_HEIGHT)
		start_y = ((wall.height * 0.5) - (WINDOW_HEIGHT * 0.5)) * *y_step;
	return (start_y);
}

/**
 * @brief Calculates the X coordinate on a texture for a wall slice.
 *
 * This function computes which column of the texture image corresponds to the
 * point where a ray intersects a wall. The calculation depends on whether the
 * wall side is horizontal or vertical.
 *
 * @param data The calculation data containing the ray intersection coordinates.
 * @param side The side of the wall hit (HORIZONTAL or VERTICAL).
 * @param text_width The width of the texture image in pixels.
 * @return The X coordinate (column) on the texture for the pixel to render.
 */
static int	texture_coord_x(t_calc data, t_side side, int text_width)
{
	int		x_coord;
	double	wall_x;

	if (side == HORIZONTAL)
		wall_x = data.ray_y - (long)data.ray_y;
	else
		wall_x = data.ray_x - (long)data.ray_x;
	x_coord = (int)(wall_x * text_width);
	return (x_coord);
}

void	write_column(t_sprites sprite, t_wall wall, t_calc data,
		t_color *color)
{
	int		offset;
	t_image	text_wall;

	wall.line = -1;
	text_wall = sprite.text_wall[wall.texture];
	wall.text_x = texture_coord_x(data, wall.side, text_wall.width);
	wall.text_y = texture_start_y(wall, &wall.text_step, text_wall.height);
	while (++wall.line < WINDOW_HEIGHT)
	{
		offset = (int)(((wall.line * sprite.frame.data.line_length)
					+ (wall.column * (sprite.frame.data.bits_per_pixel
							* 0.125))) * 0.25);
		if (wall.line < wall.draw_start)
			color_pixel(color[CEILING], sprite.frame.data, offset);
		else if (wall.line >= wall.draw_end)
			color_pixel(color[FLOOR], sprite.frame.data, offset);
		else if (wall.line >= wall.draw_start && wall.line < wall.draw_end)
			((int *)sprite.frame.data.mem)[offset] = ((int *)text_wall.data.mem)
			[(int)((((int)(wall.text_y + wall.text_step * (wall.line
									- wall.draw_start))
							*text_wall.data.line_length) + (wall.text_x
							* (text_wall.data.bits_per_pixel * 0.125)))
					* 0.25)];
	}
}

