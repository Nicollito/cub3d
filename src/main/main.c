#include "cube.h"
#include "init.h"
#include "../minilibx-linux/mlx.h"
#include "parsing.h"
#include "../moves/moves.h"
#include <math.h>

int	main(int ac, char **av)
{
	t_cube	*cube;

	if (ac != 2)
	{
		print_error("Wrong number of arguments");
		return (1);
	}
	cube = parse_cub(av);
	setup_mlx_context(cube);
	mlx_hook(cube->mlx_window, 2, 1L << 0, key_press, cube);
	mlx_hook(cube->mlx_window, 3, 1L << 1, key_release, cube);
	mlx_hook(cube->mlx_window, 17, 0, close_window, cube);
	mlx_loop_hook(cube->mlx, print_frame_to_window, cube);
	mlx_loop(cube->mlx);
}
