#include "cube.h"
#include "init.h"
#include "mlx.h"
#include "parsing.h"

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
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->sprites.image. mlx_ptr, 0, 0);
	mlx_loop(cube->mlx);
}