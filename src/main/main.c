#include "cube.h"
#include "libft.h"
#include "error.h"

int main(int ac, char **av)
{
	t_cube	cube;

	if (ac != 2)
	{
		print_error("Wrong number of arguments");
		return (1);
	}
	init_cube(&cube, ac, av);
	parsing(&cube, ac, av);
}