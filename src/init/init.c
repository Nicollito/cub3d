#include "cube.h"
#include "init.h"
#include "get_next_line.h"
#include "mlx.h"
#include <math.h>

static void	color_pixel(t_color *color, t_img_data image, int offset)
{
	if (image.endian == 1)
	{
		image.mem[offset + 0] = 0x00;
		if (color)
		{
			image.mem[offset + 0] = 0xFF;
			image.mem[offset + 1] = color->rgb[0];
			image.mem[offset + 2] = color->rgb[1];
			image.mem[offset + 3] = color->rgb[2];
		}
	}
	else
	{
		image.mem[offset + 3] = 0x00;
		if (color)
		{
			image.mem[offset + 0] = color->rgb[2];
			image.mem[offset + 1] = color->rgb[1];
			image.mem[offset + 2] = color->rgb[0];
			image.mem[offset + 3] = 0xFF;
		}
	}
}

static void	set_opacity(t_color *color, t_img_data image)
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
			offset = y * image.line_length + x
				* (image.bits_per_pixel / 8);
			if (color)
				color_pixel(&color[type], image, offset);
			else
				color_pixel(NULL, image, offset);
			++x;
		}
		if (y > WINDOW_HEIGHT / 2)
			type = FLOOR;
		++y;
	}
}

static int	create_layers(t_cube *cube)
{
	t_img_data	image[2];

	cube->sprites.image[BACKGROUND].mlx_ptr = mlx_new_image(cube->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	cube->sprites.image[FOREGROUND].mlx_ptr = mlx_new_image(cube->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cube->sprites.image[BACKGROUND].mlx_ptr || !cube->sprites.image[FOREGROUND].mlx_ptr)
		return (1);
	image[BACKGROUND].mem = mlx_get_data_addr(cube->sprites.image[BACKGROUND].mlx_ptr,
			&image[BACKGROUND].bits_per_pixel, &image[BACKGROUND].line_length,
			&image[BACKGROUND].endian);
	image[FOREGROUND].mem = mlx_get_data_addr(cube->sprites.image[FOREGROUND].mlx_ptr,
			&image[FOREGROUND].bits_per_pixel, &image[FOREGROUND].line_length,
			&image[FOREGROUND].endian);
	set_opacity(cube->config.color, image[FOREGROUND]);
	// set_opacity(NULL, image[FOREGROUND]);
	cube->image = image[FOREGROUND];
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
	cube->dist_proj = (WINDOW_HEIGHT / 2) / tan(cube->fov / 2);
	return (0);
}
