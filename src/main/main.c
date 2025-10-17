#include "cube.h"
#include "init.h"
#include "../minilibx-linux/mlx.h"
#include "parsing.h"
#include <math.h>

int	close_window(t_cube *cube)
{
	free_cube(cube);
	exit(0);
}

void	move_character(t_cube *cube, int forward, double move_speed)
{
	cube->character.x += cos(cube->character.orientation) * move_speed * forward;
	cube->character.y += sin(cube->character.orientation) * move_speed * forward;
}

int	handle_keypress(int keycode, t_cube *cube)
{
	double move_speed;

	move_speed = 0.05;
	if (keycode == KEY_W || keycode == KEY_UP)
		move_character(cube, 1, move_speed);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		cube->character.orientation -= move_speed;
	else if (keycode == KEY_S|| keycode == KEY_DOWN)
		move_character(cube, -1, move_speed);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		cube->character.orientation += move_speed;
	else if (keycode == KEY_ESC)
		close_window(cube);
	raycasting(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->sprites.frame. mlx_ptr, 0, 0);
	return (0);
}

int main(int ac, char **av)
{
	t_cube	*cube;

	if (ac != 2)
	{
		print_error("Wrong number of arguments");
		return (1);
	}
	cube = parsing(av);
	init_mlx(cube);
	raycasting(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->sprites.frame. mlx_ptr, 0, 0);
	mlx_hook(cube->mlx_window, 2, 1L << 0, handle_keypress, cube);
	mlx_hook(cube->mlx_window, 17, 0, close_window, cube);
	mlx_loop(cube->mlx);
}
