#include "cube.h"
#include "algo.h"
#include "libft.h"
#include "init.h"
#include <math.h>

static double	pos_y_texture(t_image text_wall, t_wall wall, double *step)
{
	double	text_y;

	*step = (double)text_wall.height / (double)wall.height;
	text_y = 0.0;
	if (wall.height > WINDOW_HEIGHT)
		text_y = ((wall.height * 0.5) - (WINDOW_HEIGHT * 0.5)) * *step;
	return (text_y);
}

static int	pos_x_texture(t_image text_wall, t_calc data, t_wall wall)
{
	int		text_x;
	double	wall_x;

	if (wall.side == HORIZONTAL)
		wall_x = data.ray_y - (long)data.ray_y;
	else
		wall_x = data.ray_x - (long)data.ray_x;
	text_x = (int)(wall_x * text_wall.width);
	return (text_x);
}

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
	text_x = pos_x_texture(text_wall, data, wall);
	text_y = pos_y_texture(text_wall, wall, &data.step);
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

void	raycasting(t_cube *cube)
{
	int			column;
	t_wall		wall;
	t_calc		data;
	t_sprites	sprites;

	column = -1;
	ft_memset(&wall, 0, sizeof(t_wall));
	ft_memset(&data, 0, sizeof(t_calc));
	sprites = cube->sprites;
	print_backgound(cube->config.color, cube->sprites.frame.data);
	while (++column < WINDOW_WIDTH)
	{
		get_write_value(cube, &wall, &data, column);
		write_column(sprites, wall, data, column);
	}
}
