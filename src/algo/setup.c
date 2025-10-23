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

static double	ray_len(t_calc *data, t_wall *wall, char **map)
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
		if (data->ray_dir_x < 0 && wall->side == HORIZONTAL && x > 0)
			x -= 1;
		else if (data->ray_dir_y < 0 && wall->side == VERTICAL && y > 0)
			y -= 1;
		if (map[y][x] == '1')
			break ;
	}
	set_texture_orientation(wall, *data);
	return (res);
}

static void	set_data(t_char character, t_calc *data, double ray_base_x)
{
	data->ray_x = character.x;
	data->ray_y = character.y;
	data->ray_dir_x = ray_base_x * cos(character.orientation) - RAY_BASE_Y * sin(character.orientation);
	data->ray_dir_y = ray_base_x * sin(character.orientation) + RAY_BASE_Y * cos(character.orientation);
}

void	get_write_value(t_cube *cube, t_wall *wall, t_calc *data, int column)
{
	double	len;

	set_data(cube->character, data, cube->ray_base_x[column]);
	len = ray_len(data, wall, cube->map);
	wall->height = (int)(cube->dist_proj / len);
	// wall->height = WINDOW_HEIGHT / len;
	wall->draw_start = (WINDOW_HEIGHT / 2) - (wall->height / 2);
	if (wall->draw_start < 0)
		wall->draw_start = 0;
}
