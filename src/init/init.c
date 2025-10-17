#include "cube.h"
#include "init.h"
#include "get_next_line.h"
#include "mlx.h"
#include <math.h>

static int	create_layers(t_cube *cube)
{
	t_img_data	image;

	cube->sprites.frame.mlx_ptr = mlx_new_image(cube->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cube->sprites.frame.mlx_ptr)
		return (1);
	image.mem = mlx_get_data_addr(cube->sprites.frame.mlx_ptr,
			&image.bits_per_pixel, &image.line_length,
			&image.endian);
	cube->sprites.frame.data = image;
	return (0);
}

static int	set_sprites(t_cube *cube)
{
	cube->sprites.text_wall[TEXT_NO].mlx_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->config.textures[TEXT_NO], &cube->sprites.text_wall[TEXT_NO].width,
			&cube->sprites.text_wall[TEXT_NO].height);
	cube->sprites.text_wall[TEXT_SO].mlx_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->config.textures[TEXT_SO], &cube->sprites.text_wall[TEXT_SO].width,
			&cube->sprites.text_wall[TEXT_SO].height);
	cube->sprites.text_wall[TEXT_WE].mlx_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->config.textures[TEXT_WE], &cube->sprites.text_wall[TEXT_WE].width,
			&cube->sprites.text_wall[TEXT_WE].height);
	cube->sprites.text_wall[TEXT_EA].mlx_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->config.textures[TEXT_EA], &cube->sprites.text_wall[TEXT_EA].width,
			&cube->sprites.text_wall[TEXT_EA].height);
	if (!cube->sprites.text_wall[TEXT_NO].mlx_ptr
		|| !cube->sprites.text_wall[TEXT_SO].mlx_ptr
		|| !cube->sprites.text_wall[TEXT_WE].mlx_ptr
		|| !cube->sprites.text_wall[TEXT_EA].mlx_ptr)
		return (1);
	cube->sprites.text_wall[TEXT_NO].data.mem = mlx_get_data_addr(cube->sprites.text_wall[TEXT_NO].mlx_ptr, &cube->sprites.text_wall[TEXT_NO].data.bits_per_pixel, &cube->sprites.text_wall[TEXT_NO].data.line_length, &cube->sprites.text_wall[TEXT_NO].data.endian);
	cube->sprites.text_wall[TEXT_SO].data.mem = mlx_get_data_addr(cube->sprites.text_wall[TEXT_SO].mlx_ptr, &cube->sprites.text_wall[TEXT_SO].data.bits_per_pixel, &cube->sprites.text_wall[TEXT_SO].data.line_length, &cube->sprites.text_wall[TEXT_SO].data.endian);
	cube->sprites.text_wall[TEXT_EA].data.mem = mlx_get_data_addr(cube->sprites.text_wall[TEXT_EA].mlx_ptr, &cube->sprites.text_wall[TEXT_EA].data.bits_per_pixel, &cube->sprites.text_wall[TEXT_EA].data.line_length, &cube->sprites.text_wall[TEXT_EA].data.endian);
	cube->sprites.text_wall[TEXT_WE].data.mem = mlx_get_data_addr(cube->sprites.text_wall[TEXT_WE].mlx_ptr, &cube->sprites.text_wall[TEXT_WE].data.bits_per_pixel, &cube->sprites.text_wall[TEXT_WE].data.line_length, &cube->sprites.text_wall[TEXT_WE].data.endian);
	return (0);
}

int	init_mlx(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (!cube->mlx)
		return (1);
	cube->mlx_window = mlx_new_window(cube->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3D");
	if (!cube->mlx_window)
		return (1);
	if (create_layers(cube))
		return (1);
	if (set_sprites(cube))
		return (1);
	cube->fov = (FOV * PI / 180);
	cube->dist_proj = (WINDOW_WIDTH / 2) / tan(cube->fov / 2);
	return (0);
}
