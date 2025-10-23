#include "cube.h"
#include "algo.h"
#include "mlx.h"
#include <sys/time.h>
#include <stdio.h>
#include "../moves/moves.h"
/* 
static int	second_past(void)
{
	static int		last_second = 0;
	struct timeval	tv;

	gettimeofday(&tv, (void *)0);
	if (tv.tv_sec != last_second)
	{
		last_second = tv.tv_sec;
		return (1);
	}
	return (0);
}

static void	frame_per_second(void)
{
	static int	frames = 0;

	frames++;
	if (second_past())
	{
		printf("FPS [%d]\n", frames);
		frames = 0;
	}
} */

int	print_frame_to_window(t_cube *cube)
{
	update_moves(cube);
	raycasting(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window,
		cube->sprites.frame.mlx_ptr, 0, 0);
	//frame_per_second();
	return (0);
}
