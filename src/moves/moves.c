#include "moves.h"
#include <math.h>
#include <stdio.h>
#include "mlx.h"

int	close_window(t_cube *cube)
{
	free(cube);
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
	if (cube->map[(int)new_y][(int)new_x] != '1')
	{
		cube->character.x = new_x;
		cube->character.y = new_y;
	}
}

int	handle_keypress(int keycode, t_cube *cube)
{
	double	move_speed;

	move_speed = 0.05;
	if (keycode == KEY_W || keycode == KEY_UP)
		move_character(cube, 1, move_speed);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		cube->character.orientation -= move_speed;
		if (cube->character.orientation < 0)
			cube->character.orientation += 2 * PI;
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_character(cube, -1, move_speed);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		cube->character.orientation += move_speed;
		if (cube->character.orientation >= 2 * PI)
			cube->character.orientation -= 2 * PI;
	}
	else if (keycode == KEY_ESC)
		close_window(cube);
	printf("x:[%f] - y:[%f] - orientation[%f]\n", cube->character.x,
		cube->character.y, cube->character.orientation);
	raycasting(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window,
		cube->sprites.frame. mlx_ptr, 0, 0);
	return (0);
}
