#include "cube.h"
#include "algo.h"
#include "libft.h"
#include "init.h"
#include <math.h>

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

/**
 * @brief Renders a single vertical wall column into the frame image.
 *
 * This function draws a vertical slice of a wall on the screen by copying
 * pixels from the appropriate wall texture to the frame buffer. The column
 * index specifies which vertical line on the frame to draw. Texture coordinates
 * are calculated to match the wall's height and position.
 *
 * @param sprite The sprite structure containing textures and the frame buffer.
 * @param wall The wall structure containing height, draw start, and texture info.
 * @param data Calculation data containing ray intersection info and step size.
 * @param column The column index in the frame where the wall slice will be drawn.
 */
static void	write_column(t_sprites sprite, t_wall wall, t_calc data, int column)
{
	int		i;
	int		text_x;
	double	text_y;
	t_image	text_wall;
	t_image	frame;

	i = -1;
	text_wall = sprite.text_wall[wall.texture];
	frame = sprite.frame;
	text_x = texture_coord_x(data, wall.side, text_wall.width);
	text_y = texture_start_y(wall, &data.step, text_wall.height);
	while (++i < wall.height && i + wall.draw_start < WINDOW_HEIGHT)
	{
		((int *)frame.data.mem)
		[(((wall.draw_start + i) * frame.data.line_length)
				+ (column * (frame.data.bits_per_pixel / 8))) / 4]
			= ((int *)text_wall.data.mem)
		[(((int)(text_y + data.step * i) *text_wall.data.line_length)
				+ (text_x * (text_wall.data.bits_per_pixel / 8))) / 4];
	}
}

void	raycasting(t_color *color, t_sprites sprites, t_algo algo)
{
	int			column;
	t_wall		wall;
	t_calc		data;

	column = -1;
	ft_memset(&wall, 0, sizeof(t_wall));
	ft_memset(&data, 0, sizeof(t_calc));
	fill_background(color, sprites.frame.data);
	while (++column < WINDOW_WIDTH)
	{
		get_write_value(algo, &wall, &data, column);
		write_column(sprites, wall, data, column);
	}
}
