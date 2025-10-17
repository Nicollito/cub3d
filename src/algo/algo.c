#include "cube.h"
#include "algo.h"
#include "libft.h"
#include "init.h"
#include <math.h>

static void	color_pixel(t_color *color, t_img_data image, int offset)
{
	if (image.endian == 1)
	{
		image.mem[offset + 1] = color->rgb[0];
		image.mem[offset + 2] = color->rgb[1];
		image.mem[offset + 3] = color->rgb[2];
	}
	else
	{
		image.mem[offset + 0] = color->rgb[2];
		image.mem[offset + 1] = color->rgb[1];
		image.mem[offset + 2] = color->rgb[0];
	}
}

static void	set_backgound(t_color *color, t_img_data image)
{
	int				x;
	int				y;
	int				offset;
	t_color_type	type;

	y = 0;
	type = CEILING;
	while (y <= WINDOW_HEIGHT)
	{
		x = 0;
		while (x <= WINDOW_WIDTH)
		{
			offset = y * image.line_length + x
				* (image.bits_per_pixel / 8);
			color_pixel(&color[type], image, offset);
			++x;
		}
		if (y > WINDOW_HEIGHT / 2)
			type = FLOOR;
		++y;
	}
}

static void	set_data(t_cube *cube, t_calc *data, double angle)
{
	data->ray_x = cube->character.x;
	data->ray_y = cube->character.y;
	data->ray_dir_x = cos(angle);
	data->ray_dir_y = sin(angle);
}

static double	set_step(t_calc data, t_side *side)
{
	double	line;
	double	dist_x;
	double	dist_y;

	if (data.ray_dir_x > 0)
		line = floor(data.ray_x) + 1;
	else
		line = floor(data.ray_x - 0.0001);
	dist_x = (line - data.ray_x) / data.ray_dir_x;
	if (data.ray_dir_y > 0)
		line = floor(data.ray_y) + 1;
	else
		line = floor(data.ray_y - 0.0001);
	dist_y = (line - data.ray_y) / data.ray_dir_y;
	if (dist_y < dist_x)
	{
		*side = VERTICAL;
		data.step = dist_y;
	}
	else
	{
		*side = HORAZONTAL;
		data.step = dist_x;
	}
	return (data.step);
}

static void	set_texture_orientation(t_wall *wall, t_calc data)
{
	if (wall->side == VERTICAL)
	{
		if (data.ray_dir_y < 0)
			wall->texture = TEXT_NO;
		else
			wall->texture = TEXT_SO;
	}
	if (wall->side == HORAZONTAL)
	{
		if (data.ray_dir_x < 0)
			wall->texture = TEXT_EA;
		else
			wall->texture = TEXT_WE;
	}
}

static double	ray_len(t_cube *cube, t_calc data, t_wall *wall)
{
	int		x;
	int		y;
	double	res;

	res = 0;
	while (1)
	{
		data.step = set_step(data, &wall->side);
		data.ray_x += data.ray_dir_x * data.step;
		data.ray_y += data.ray_dir_y * data.step;
		res += data.step;
		x = (int)data.ray_x;
		y = (int)data.ray_y;
		if (data.ray_dir_x < 0 && wall->side == HORAZONTAL && x > 0)
			x = (int)data.ray_x - 1;
		else if (data.ray_dir_y < 0 && wall->side == VERTICAL && y > 0)
			y = (int)data.ray_y - 1;
		if (cube->map[y][x] == '1')
			break ;
	}
	set_texture_orientation(wall, data);
	return (res);
}

static void	write_column(t_cube *cube, t_wall wall, int column)
{
	int	i;
	int	offset;

	i = -1;
	while (++i < wall.height && i < WINDOW_HEIGHT)
	{
		offset = (wall.draw_start * cube->sprites.frame.data.line_length) + (column * (cube->sprites.frame.data.bits_per_pixel / 8));
		cube->sprites.frame.data.mem[offset + 0] = (char)0;
		cube->sprites.frame.data.mem[offset + 1] = (char)0;
		cube->sprites.frame.data.mem[offset + 2] = (char)255;
		cube->sprites.frame.data.mem[offset + 3] = 0xFF;
		wall.draw_start++;
	}
}

static void	get_write_value(t_cube *cube, t_wall *wall, t_calc *data, int column)
{
	double	angle;
	double	len;

	angle = cube->character.orientation - (cube->fov * 0.5) + (cube->fov * column / WINDOW_WIDTH);
	set_data(cube, data, angle);
	len = ray_len(cube, *data, wall);
	wall->height = 1 * cube->dist_proj / len;
	wall->draw_start = (WINDOW_HEIGHT / 2) - (wall->height / 2);
	if (wall->draw_start < 0)
		wall->draw_start = 0;
}

void	raycasting(t_cube *cube)
{
	int		column;
	t_wall	wall;
	t_calc	data;

	column = -1;
	ft_memset(&wall, 0, sizeof(t_wall));
	ft_memset(&data, 0, sizeof(t_calc));
	set_backgound(cube->config.color, cube->sprites.frame.data);
	while (++column < WINDOW_WIDTH)
	{
		get_write_value(cube, &wall, &data, column);
		write_column(cube, wall, column);
	}
}
