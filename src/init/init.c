#include "cube.h"
#include "init.h"
#include "get_next_line.h"
#include "mlx.h"

int	init_mlx(t_cube *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->sprites.wall_no = mlx_xpm_file_to_image(game->mlx, /*path_image*/, )
}
