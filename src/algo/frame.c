#include "cube.h"
#include "algo.h"
#include "mlx.h"

int	print_frame_to_window(t_cube *cube)
{
	raycasting(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->sprites.frame.mlx_ptr, 0, 0);
	return (0);
}
