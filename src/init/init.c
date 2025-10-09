#include "cube.h"
#include "init.h"
#include "get_next_line.h"
#include "mlx.h"

static void	fill_color(t_color *color)
{
	
}

static void	*create_background(t_cube *cube)
{
	
}

int	init_mlx(t_cube *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	// game->sprites.wall_no.mlx_ptr = mlx_xpm_file_to_image(game->mlx, /*path_image*/, game->sprites.wall_no.width, game->sprites.wall_no.height);
	// game->sprites.wall_so.mlx_ptr = mlx_xpm_file_to_image(game->mlx, /*path_image*/, game->sprites.wall_so.width, game->sprites.wall_so.height);
	// game->sprites.wall_ea.mlx_ptr = mlx_xpm_file_to_image(game->mlx, /*path_image*/, game->sprites.wall_ea.width, game->sprites.wall_ea.height);
	// game->sprites.wall_we.mlx_ptr = mlx_xpm_file_to_image(game->mlx, /*path_image*/, game->sprites.wall_we.width, game->sprites.wall_we.height);
	game->mlx_window = mlx_new_window(game->mlx, 1920, 1080, "cub3D");
	if (!game->mlx_window)
		return (1);
	return (0);
}
