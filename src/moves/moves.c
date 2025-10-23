#include "../moves/moves.h"
#include "parsing.h"
#include <math.h>
#include <stdio.h>
#include "mlx.h"

void	move_character(t_cube *cube, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = cube->character.x + dx;
	new_y = cube->character.y + dy;
	if (is_valid_position(cube, new_x, cube->character.y))
		cube->character.x = new_x;
	if (is_valid_position(cube, cube->character.x, new_y))
		cube->character.y = new_y;
}

void	move(t_cube *cube, int forward, double move_speed)
{
	double	dx;
	double	dy;

	dx = cos(cube->character.orientation) * move_speed * forward;
	dy = sin(cube->character.orientation) * move_speed * forward;
	move_character(cube, dx, dy);
}

void	strafe(t_cube *cube, int direction, double move_speed)
{
	double	dx;
	double	dy;

	dx = -sin(cube->character.orientation) * move_speed * direction;
	dy = cos(cube->character.orientation) * move_speed * direction;
	move_character(cube, dx, dy);
}

void	rotate(t_cube *cube, int direction, double rot_speed)
{
	cube->character.orientation += direction * rot_speed;
	if (cube->character.orientation <= PI * 0.5)
		cube->character.orientation += 2 * PI;
	else if (cube->character.orientation >= (2 * PI + PI * 0.5))
		cube->character.orientation -= 2 * PI;
}

int	update_moves(t_cube *cube)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.03;
	if (cube->keys.w == 1)
		move(cube, 1, move_speed);
	if (cube->keys.s == 1)
		move(cube, -1, move_speed);
	if (cube->keys.a == 1)
		strafe(cube, -1, move_speed);
	if (cube->keys.d == 1)
		strafe(cube, 1, move_speed);
	if (cube->keys.left == 1)
		rotate(cube, -1, rot_speed);
	if (cube->keys.right == 1)
		rotate(cube, 1, rot_speed);
	return (0);
}
