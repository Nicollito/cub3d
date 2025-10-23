#include "cleanup.h"

void	free_cube(t_cube *cube)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(cube->config.textures[i]);
	i = -1;
	while (++i < cube->y_max)
		free(cube->map[i]);
	free(cube->map);
	free(cube);
}
