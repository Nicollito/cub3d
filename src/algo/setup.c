#include "cube.h"
#include "algo.h"
#include <math.h>

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
		*side = HORIZONTAL;
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
	if (wall->side == HORIZONTAL)
	{
		if (data.ray_dir_x < 0)
			wall->texture = TEXT_WE;
		else
			wall->texture = TEXT_EA;
	}
}

static double	ray_len(t_cube *cube, t_calc *data, t_wall *wall, double angle)
{
	int		x;
	int		y;
	//int		way;
	double	res;

	//way = 1;
	res = 0;
	while (1)
	{
		set_step(data, &wall->side);
		data->ray_x += data->ray_dir_x * data->step;
		data->ray_y += data->ray_dir_y * data->step;
		res += data->step;
		x = (int)data->ray_x;
		y = (int)data->ray_y;
		if (data->ray_dir_x < 0 && wall->side == HORIZONTAL && x > 0)
			x -= 1;
		else if (data->ray_dir_y < 0 && wall->side == VERTICAL && y > 0)
			y -= 1;
		if (cube->map[y][x] == '1')
			break ;
	}
	set_texture_orientation(wall, *data);
/* 	if (wall->texture == TEXT_NO || wall->texture == TEXT_WE)
		way = -1;
	if (wall->side == VERTICAL)
		res = (data->ray_x - cube->character.x + (1 - way) / 2) / data->ray_dir_x;
	if (wall->side == HORIZONTAL)
		res = (data->ray_y - cube->character.y + (1 - way) / 2) / data->ray_dir_y; */
	res = res * cos(cube->character.orientation - angle);
	return (res);
}

static void	set_data(t_cube *cube, t_calc *data, double angle)
{
	data->ray_x = cube->character.x;
	data->ray_y = cube->character.y;
	data->ray_dir_x = cos(angle);
	data->ray_dir_y = sin(angle);
}

void	get_write_value(t_cube *cube, t_wall *wall, t_calc *data, int column)
{
	double	angle;
	double	len;

	angle = cube->character.orientation - (cube->fov * 0.5) + (cube->fov
			* column / WINDOW_WIDTH);
	set_data(cube, data, angle);
	len = ray_len(cube, data, wall, angle);
	wall->height = (int)(cube->dist_proj / len);
	wall->draw_start = (WINDOW_HEIGHT / 2) - (wall->height / 2);
	if (wall->draw_start < 0)
		wall->draw_start = 0;
}
