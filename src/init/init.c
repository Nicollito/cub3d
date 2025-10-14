#include "cube.h"
#include "init.h"
#include "get_next_line.h"
#include "mlx.h"

static void	color_pixel(t_color color, t_img_data background, int offset)
{
	if (background.endian == 1)
	{
		background.mem[offset + 0] = 0xFF;
		background.mem[offset + 1] = color.rgb[0];
		background.mem[offset + 2] = color.rgb[1];
		background.mem[offset + 3] = color.rgb[2];
	}
	else
	{
		background.mem[offset + 0] = color.rgb[2];
		background.mem[offset + 1] = color.rgb[1];
		background.mem[offset + 2] = color.rgb[0];
		background.mem[offset + 3] = 0xFF;
	}
}

static void	write_background(t_color *color, t_img_data background)
{
	int				x;
	int				y;
	int				offset;
	t_color_type	type;

	y = 0;
	type = CEILING;
	while (y <= WINDOW_HEIGHT)
	{
		x = 0;
		while (x <= WINDOW_WIDTH)
		{
			offset = y * background.line_length + x
				* (background.bits_per_pixel / 8);
			color_pixel(color[type], background, offset);
			++x;
		}
		if (y > WINDOW_HEIGHT / 2)
			type = FLOOR;
		++y;
	}
}

static int	create_background(t_cube *cube)
{
	t_img_data	background;

	cube->sprites.background.mlx_ptr = mlx_new_image(cube->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cube->sprites.background.mlx_ptr)
		return (1);
	background.mem = mlx_get_data_addr(cube->sprites.background.mlx_ptr,
			&background.bits_per_pixel, &background.line_length,
			&background.endian);
	write_background(cube->config.color, background);
	return (0);
}

static int	set_sprites(t_cube *cube)
{
	cube->sprites.wall[TEXT_NO].mlx_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->config.textures[TEXT_NO], &cube->sprites.wall[TEXT_NO].width,
			&cube->sprites.wall[TEXT_NO].height);
	cube->sprites.wall[TEXT_SO].mlx_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->config.textures[TEXT_SO], &cube->sprites.wall[TEXT_SO].width,
			&cube->sprites.wall[TEXT_SO].height);
	cube->sprites.wall[TEXT_WE].mlx_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->config.textures[TEXT_WE], &cube->sprites.wall[TEXT_WE].width,
			&cube->sprites.wall[TEXT_WE].height);
	cube->sprites.wall[TEXT_EA].mlx_ptr = mlx_xpm_file_to_image(cube->mlx,
			cube->config.textures[TEXT_EA], &cube->sprites.wall[TEXT_EA].width,
			&cube->sprites.wall[TEXT_EA].height);
	if (!cube->sprites.wall[TEXT_NO].mlx_ptr
		|| !cube->sprites.wall[TEXT_SO].mlx_ptr
		|| !cube->sprites.wall[TEXT_WE].mlx_ptr
		|| !cube->sprites.wall[TEXT_EA].mlx_ptr)
		return (1);
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
	if (create_background(cube))
		return (1);
	if (set_sprites(cube))
		return (1);
	return (0);
}
