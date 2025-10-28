#include "cube.h"
#include "algo.h"
#include <math.h>

#include <stdio.h>
/**
 * @brief Computes the next step along a ray for DDA traversal.
 *
 * This function calculates the distance to the next vertical or horizontal
 * grid line along the ray and determines which side will be hit first. The
 * step size along the ray is stored in `data->step`, and the hit side is
 * returned through `side`.
 *
 * @param data Pointer to the calculation structure with ray position and
 * direction.
 * @param side Pointer to the side variable to store whether the next hit is
 * HORIZONTAL or VERTICAL.
 */
static void	set_step(t_calc *data, t_side *side)
{
	double	line;
	double	dist_x;
	double	dist_y;

	if (data->ray_dir_x > 0)
		line = (int)(data->ray_x) + 1;
	else
		line = (int)(data->ray_x - 0.0001);
	dist_x = (line - data->ray_x) / data->ray_dir_x;
	if (data->ray_dir_y > 0)
		line = (int)(data->ray_y) + 1;
	else
		line = (int)(data->ray_y - 0.0001);
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

/**
 * @brief Determines the wall texture to use based on the ray direction and
 * wall side.
 *
 * This function sets the `texture` field of a wall depending on whether the
 * wall was hit on a vertical or horizontal side, and the direction of the
 * ray that hit it.
 *
 * @param wall Pointer to the wall structure to update.
 * @param data Pointer to calculation data containing ray start and direction.
 */
static void	set_texture_orientation(t_wall *wall, t_calc *data)
{
	if (wall->side == VERTICAL)
	{
		if (data->ray_dir_y < 0)
			wall->texture = TEXT_NO;
		else
			wall->texture = TEXT_SO;
	}
	else if (wall->side == HORIZONTAL)
	{
		if (data->ray_dir_x < 0)
			wall->texture = TEXT_WE;
		else
			wall->texture = TEXT_EA;
	}
}

/**
 * @brief Casts a ray and computes its length until it hits a wall.
 *
 * This function performs DDA stepping along a ray until it intersects a wall
 * tile in the map. It also sets the texture orientation of the wall based on
 * the ray direction and returns the total distance traveled by the ray.
 *
 * @param data Pointer to calculation data containing ray start and direction.
 * @param wall Pointer to the wall structure to update side and texture info.
 * @param algo Structure containing the map, its size, and other raycasting
 * parameters.
 * @return Distance from the ray origin to the wall hit.
 */
static double	ray_len(t_calc *data, t_wall *wall, t_algo algo)
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
		if (y < 0 || x < 0)
			break ;
		if (x < algo.x_max && y < algo.y_max && algo.map[y][x] == '1')
			break ;
	}
	set_texture_orientation(wall, data);
	return (res);
}

/**
 * @brief Initializes ray data for a character and a given column.
 *
 * This function sets the starting position and direction of a ray based on
 * the character's position and orientation. The horizontal base offset
 * determines the direction within the field of view.
 *
 * @param character The character structure with position and orientation.
 * @param data Pointer to the calculation structure to fill.
 * @param ray_base_x The horizontal base offset for this ray.
 */
static void	set_data(t_char character, t_calc *data, double ray_base_x)
{
	double	cos_char;
	double	sin_char;

	cos_char = cos(character.orientation);
	sin_char = sin(character.orientation);
	data->ray_x = character.x;
	data->ray_y = character.y;
	data->ray_dir_x = ray_base_x * cos_char
		- RAY_BASE_Y * sin_char;
	data->ray_dir_y = ray_base_x * sin_char
		+ RAY_BASE_Y * cos_char;
}

void	get_write_value(t_algo algo, t_wall *wall, t_calc *data, int column)
{
	double	len;

	set_data(algo.character, data, algo.ray_base_x[column]);
	len = ray_len(data, wall, algo);
	wall->height = (int)(algo.dist_proj / len);
	wall->draw_start = (WINDOW_HEIGHT * 0.5) - (wall->height * 0.5);
	wall->draw_end = wall->draw_start + wall->height;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
}
