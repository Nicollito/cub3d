#include "cube.h"
#include "algo.h"
#include "libft.h"
#include <math.h>

static void	set_data(t_cube *cube, t_calc *data, double angle)
{
	data->step = 0.1;
	data->ray_x = cube->character.x;
	data->ray_y = cube->character.y;
	data->ray_dir_x = cos(angle);
	data->ray_dir_y = sin(angle);
}

static double	ray_len(t_cube *cube, t_calc data)
{
	double	res;

	res = 0;
	while (1)
	{
		data.ray_x += data.ray_dir_x * data.step;
		data.ray_y += data.ray_dir_y * data.step;
		res += data.step;
		if (cube->map[(int)data.ray_y][(int)data.ray_x] == '1')
			break ;
	}
	return (res);
}

#include <stdio.h>

void	raycasting(t_cube *cube)
{
	int		i;
	int		j;
	int		height;
	int		offset;
	int		draw_start;
	double	len;
	double	angle;
	t_calc	data;

	i = -1;
	ft_memset(&data, 0, sizeof(t_calc));
	while (++i < WINDOW_WIDTH)
	{
		angle = cube->character.orientation - (cube->fov * 0.5) + (cube->fov * i / WINDOW_WIDTH);
		set_data(cube, &data, angle);
		len = ray_len(cube, data);
		height = 1 * cube->dist_proj / len;
		draw_start = (WINDOW_HEIGHT / 2) - (height / 2);
		j = -1;
		while (++j < height)
		{
			offset = (draw_start * cube->image.line_length) + (i * (cube->image.bits_per_pixel / 8));
			printf("[%d]\n", cube->image.endian);
			cube->image.mem[offset + 0] = (char)0;
			cube->image.mem[offset + 1] = (char)0;
			cube->image.mem[offset + 2] = (char)255;
			cube->image.mem[offset + 3] = 0xFF;
			draw_start++;
		}
	}
}
