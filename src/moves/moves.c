#include "moves.h"
#include "parsing.h"
#include <math.h>
#include <stdio.h>
#include "mlx.h"

int	close_window(t_cube *cube)
{
	free_cube(cube);
	exit(0);
}

void	move_character(t_cube *cube, int forward, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = cube->character.x + cos(cube->character.orientation)
		* move_speed * forward;
	new_y = cube->character.y + sin(cube->character.orientation)
		* move_speed * forward;
	if (cube->map[(int)(new_y + 0.1)][(int)cube->character.x] != '1' &&
		cube->map[(int)(new_y - 0.1)][(int)cube->character.x] != '1')
		cube->character.y = new_y;
	if (cube->map[(int)cube->character.y][(int)(new_x + 0.1)] != '1' &&
		cube->map[(int)cube->character.y][(int)(new_x - 0.1)] != '1')
		cube->character.x = new_x;
}

void	strafe_character(t_cube *cube, int direction, double move_speed)
{
	double	strafe_x;
	double	strafe_y;

	strafe_x = cube->character.x - sin(cube->character.orientation) * move_speed * direction;
	strafe_y = cube->character.y + cos(cube->character.orientation) * move_speed * direction;
	
	if (cube->map[(int)(strafe_y + 0.1)][(int)cube->character.x] != '1' &&
		cube->map[(int)(strafe_y - 0.1)][(int)cube->character.x] != '1')
		cube->character.y = strafe_y;
	if (cube->map[(int)cube->character.y][(int)(strafe_x + 0.1)] != '1' &&
		cube->map[(int)cube->character.y][(int)(strafe_x - 0.1)] != '1')
		cube->character.x = strafe_x;
}

int	handle_keypress(int keycode, t_cube *cube)
{
	double	move_speed;

	move_speed = 0.05;
	if (keycode == KEY_W)
		move_character(cube, 1, move_speed);
	if (keycode == KEY_A)
		strafe_character(cube, -1, move_speed);
	if (keycode == KEY_LEFT)
	{
		cube->character.orientation -= move_speed;
		if (cube->character.orientation <= PI * 0.5)
			cube->character.orientation += (2 * PI);
	}
	if (keycode == KEY_S)
		move_character(cube, -1, move_speed);
	if (keycode == KEY_RIGHT)
	{
		cube->character.orientation += move_speed;
		if (cube->character.orientation >= (2 * PI + PI * 0.5))
			cube->character.orientation -= (2 * PI);
	}
	if (keycode == KEY_D)
		strafe_character(cube, 1, move_speed);
	else if (keycode == KEY_ESC)
		close_window(cube);
/* 	printf("x:[%f] - y:[%f] - orientation[%f]\n", cube->character.x,
		cube->character.y, cube->character.orientation); */
/* 	raycasting(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->sprites.frame.mlx_ptr, 0, 0); */
	return (0);
}
