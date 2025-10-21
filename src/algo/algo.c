#include "cube.h"
#include "algo.h"
#include "libft.h"
#include "init.h"
#include <math.h>

#include <stdio.h>
static double	pos_y_texture(t_cube *cube, t_wall wall, double *step)
{
	double	text_y;

	*step = (double)cube->sprites.text_wall[wall.texture].height
			/ (double)wall.height;
	text_y = 0.0;
	if (wall.height > WINDOW_HEIGHT)
		text_y = ((wall.height / 2) - (WINDOW_HEIGHT / 2)) * *step;
	return (text_y);
}

static int	pos_x_texture(t_cube *cube, t_calc data, t_wall wall)
{
	int		text_x;
	double	wall_x;

	if (wall.side == HORIZONTAL)
		wall_x = data.ray_y - floor(data.ray_y);
	else
		wall_x = data.ray_x - floor(data.ray_x);
	text_x = (int)(wall_x * cube->sprites.text_wall[wall.texture].width);
	return (text_x);
}

static void	write_column(t_cube *cube, t_wall wall, t_calc data, int column)
{
	int		i;
	int		text_x;
	double	text_y;
	int		offset_frame;
	int		offset_text;

	i = -1;
	text_x = pos_x_texture(cube, data, wall);
	text_y = pos_y_texture(cube, wall, &data.step);
	while (++i < wall.height && i + wall.draw_start < WINDOW_HEIGHT)
	{
		offset_frame = ((wall.draw_start + i)
				* cube->sprites.frame.data.line_length) + (column
				* (cube->sprites.frame.data.bits_per_pixel / 8));
		offset_text = ((int)(text_y + data.step * i)
				* cube->sprites.text_wall[wall.texture].data.line_length)
				+ (text_x * (cube->sprites.text_wall[wall.texture].data.bits_per_pixel / 8));
		cube->sprites.frame.data.mem[offset_frame + 0] = cube->sprites.text_wall[wall.texture].data.mem[offset_text + 0];
		cube->sprites.frame.data.mem[offset_frame + 1] = cube->sprites.text_wall[wall.texture].data.mem[offset_text + 1];
		cube->sprites.frame.data.mem[offset_frame + 2] = cube->sprites.text_wall[wall.texture].data.mem[offset_text + 2];
		cube->sprites.frame.data.mem[offset_frame + 3] = cube->sprites.text_wall[wall.texture].data.mem[offset_text + 3];
	}
}

void	raycasting(t_cube *cube)
{
	int		column;
	t_wall	wall;
	t_calc	data;

	column = -1;
	ft_memset(&wall, 0, sizeof(t_wall));
	ft_memset(&data, 0, sizeof(t_calc));
	print_backgound(cube->config.color, cube->sprites.frame.data);
	while (++column < WINDOW_WIDTH)
	{
		get_write_value(cube, &wall, &data, column);
		write_column(cube, wall, data, column);
	}
}
