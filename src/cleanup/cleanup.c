#include "cleanup.h"
#include "mlx.h"

static void	destroy_wall_textures(t_cube *cube)
{
	int	i;

	i = -1;
	while (++i < NB_TEXTURES)
		mlx_destroy_image(cube->mlx, cube->sprites.text_wall[i].mlx_ptr);
}

static void	clear_mlx(t_cube *cube)
{
	destroy_wall_textures(cube);
	mlx_destroy_image(cube->mlx, cube->sprites.frame.mlx_ptr);
	mlx_destroy_window(cube->mlx, cube->mlx_window);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
}

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
	clear_mlx(cube);
	free(cube);
}
