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
	
	mlx_loop(cube->mlx);
}