#include "cube.h"
#include "init.h"
#include "mlx.h"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_cube	cube;

	// parsing(ac, av);
	init_mlx(&cube);
	mlx_loop(cube.mlx);
}