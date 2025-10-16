#include "cube.h"
#include "init.h"
#include "mlx.h"
#include "parsing.h"

int	close_window(t_cube *cube)
{
	exit(0);
}



void	move_character(t_cube *cube, int x, int y)
{
	int	new_x;
	int	new_y;

	new_x = cube->character.x + x;
	new_y = cube->character.y + y;
	if (cube->map[new_y][new_x] == '1')
		return ;
	else
	{
		cube->character.x = new_x;
		cube->character.y = new_y;
	}
	
}

int	handle_keypress(int keycode, t_cube *cube)
{
	if (keycode == 119 || keycode == 65362)
		move_character(cube, 0, -1);
	else if (keycode == 97 || keycode == 65361)
		move_character(cube, -1, 0);
	else if (keycode == 115 || keycode == 65364)
		move_character(cube, 0, 1);
	else if (keycode == 100 || keycode == 65363)
		move_character(cube, 1, 0);
	else if (keycode == 65307)
		close_window(cube);
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
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->sprites.image[BACKGROUND]. mlx_ptr, 0, 0);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->sprites.image[FOREGROUND]. mlx_ptr, 0, 0);
	mlx_hook(cube->mlx_window, 2, 1L << 0, handle_keypress, cube);
	mlx_hook(cube->mlx_window, 17, 0, close_window, cube);
	mlx_loop(cube->mlx);
}