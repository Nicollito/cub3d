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

static void	set_step(t_calc *data, t_side *side)
{
	double	line;
	double	dist_x;
	double	dist_y;

	if (data->ray_dir_x > 0)
		line = floor(data->ray_x) + 1;
	else
		line = floor(data->ray_x - 0.0001);
	dist_x = (line - data->ray_x) / data->ray_dir_x;
	if (data->ray_dir_y > 0)
		line = floor(data->ray_y) + 1;
	else
		line = floor(data->ray_y - 0.0001);
	dist_y = (line - data->ray_y) / data->ray_dir_y;
	if (dist_y < dist_x)
	{
		*side = VERTICAL;
		data->step = dist_y;
	}
	else
	{
		*side = HORAZONTAL;
		data->step = dist_x;
	}
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

static double	ray_len(t_cube *cube, t_calc *data, t_wall *wall)
{
	int		x;
	int		y;
	double	res;

	res = 0;
	while (1)
	{
		set_step(data, &wall->side);
		data->ray_x += data->ray_dir_x * data->step;
		data->ray_y += data->ray_dir_y * data->step;
		res += data->step;
		x = (int)data->ray_x;
		y = (int)data->ray_y;
		if (data->ray_dir_x < 0 && wall->side == HORAZONTAL && x > 0)
			x = (int)data->ray_x - 1;
		else if (data->ray_dir_y < 0 && wall->side == VERTICAL && y > 0)
			y = (int)data->ray_y - 1;
		if (cube->map[y][x] == '1')
			break ;
	}
	set_texture_orientation(wall, *data);
	return (res);
}

static double	pos_y_texture(t_cube *cube, t_wall wall, double *step)
{
	double	text_y;

	*step = (double)cube->sprites.text_wall[wall.texture].height / (double)wall.height;
	text_y = 0.0;
	if (wall.height > WINDOW_HEIGHT)
		text_y = ((wall.height / 2) - (WINDOW_HEIGHT / 2)) * *step;
	if (text_y < 0)
		text_y = 0;
	if (text_y >= cube->sprites.text_wall[wall.texture].height)
		text_y = cube->sprites.text_wall[wall.texture].height - 1;
	return (text_y);
}

static int	pos_x_texture(t_cube *cube, t_calc data, t_wall wall)
{
	int		text_x;
	double	wall_x;

	if (wall.side == HORAZONTAL)
		wall_x = data.ray_y - floor(data.ray_y);
	else
		wall_x = data.ray_x - floor(data.ray_x);
	text_x = (int)(wall_x * cube->sprites.text_wall[wall.texture].width);
	return (text_x);
}

static void	write_column(t_cube *cube, t_wall wall, t_calc data, int column)
{
	int	i;
	int	text_x;
	int	text_y;
	int	offset_frame;
	int	offset_text;
	double	step;

	i = -1;
	text_x = pos_x_texture(cube, data, wall);
	text_y = pos_y_texture(cube, wall, &step);
	while (++i < wall.height && i + wall.draw_start < WINDOW_HEIGHT)
	{
		offset_frame = ((wall.draw_start + i) * cube->sprites.frame.data.line_length) + (column * (cube->sprites.frame.data.bits_per_pixel / 8));
		offset_text = ((int)(text_y + step * i) * cube->sprites.text_wall[wall.texture].data.line_length) + (text_x * (cube->sprites.text_wall[wall.texture].data.bits_per_pixel / 8));
		cube->sprites.frame.data.mem[offset_frame + 0] = cube->sprites.text_wall[wall.texture].data.mem[offset_text + 0];
		cube->sprites.frame.data.mem[offset_frame + 1] = cube->sprites.text_wall[wall.texture].data.mem[offset_text + 1];
		cube->sprites.frame.data.mem[offset_frame + 2] = cube->sprites.text_wall[wall.texture].data.mem[offset_text + 2];
		cube->sprites.frame.data.mem[offset_frame + 3] = cube->sprites.text_wall[wall.texture].data.mem[offset_text + 3];
	}
}

static void	get_write_value(t_cube *cube, t_wall *wall, t_calc *data, int column)
{
	double	angle;
	double	len;

	angle = cube->character.orientation - (cube->fov * 0.5) + (cube->fov * column / WINDOW_WIDTH);
	set_data(cube, data, angle);
	len = ray_len(cube, data, wall);
	data->dist = len; //tmp
	wall->height = (int)(cube->dist_proj / len);
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
		write_column(cube, wall, data, column);
	}
}
