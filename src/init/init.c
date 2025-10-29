/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:07 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/29 14:56:08 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "init.h"
#include "get_next_line.h"
#include "mlx.h"
#include <math.h>

/**
 * @brief Creates a new image frame for rendering and stores it in the cube
 * structure.
 *
 * This function allocates a new image using the MiniLibX library with the
 * window's width and height. It then retrieves the image data address and
 * stores the related info (memory address, bits per pixel, line length,
 * endian) inside the cube's frame structure.
 *
 * @param cube Pointer to the main cube structure containing rendering data.
 * @return 0 on success, or 1 if the image allocation failed.
 */
static int	create_frame(t_cube *cube)
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

/**
 * @brief Loads a texture from an XPM file and stores its data in the texture
 * structure.
 *
 * This function uses MiniLibX to load an image from the given file path, then
 * retrieves its data address and related info (bits per pixel, line length,
 * endian) to store in the texture structure.
 *
 * @param texture Pointer to the texture structure to initialize.
 * @param mlx_ptr Pointer to the MiniLibX instance.
 * @param path Path to the XPM file to load.
 * @return 0 on success, or 1 if the texture could not be loaded.
 */
static int	load_texture(t_image *texture, void *mlx_ptr, char *path)
{
	texture->mlx_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &texture->width,
			&texture->height);
	if (!texture->mlx_ptr)
		return (1);
	texture->data.mem = mlx_get_data_addr(texture->mlx_ptr,
			&texture->data.bits_per_pixel, &texture->data.line_length,
			&texture->data.endian);
	return (0);
}

/**
 * @brief Loads all wall textures defined in the configuration and stores them
 * in the cube structure.
 *
 * This function iterates through all texture paths listed in the cube
 * configuration and loads each texture using the MiniLibX library. Each loaded
 * texture is stored in the cube's sprite array for later rendering.
 *
 * @param cube Pointer to the main cube structure containing configuration and
 * texture data.
 * @return 0 on success, or 1 if any texture failed to load.
 */
static int	init_wall_textures(t_cube *cube)
{
	int	i;

	i = -1;
	while (++i < NB_TEXTURES)
	{
		if (load_texture(&cube->sprites.text_wall[i], cube->mlx,
				cube->config.textures[i]))
		{
			while (--i >= 0)
			{
				mlx_destroy_image(cube->mlx,
					cube->sprites.text_wall[i].mlx_ptr);
				cube->sprites.text_wall[i].mlx_ptr = NULL;
			}
			return (1);
		}
	}
	return (0);
}

/**
 * @brief Precomputes the horizontal base offsets for ray directions.
 *
 * This function fills an array with the X offsets for each column of the screen
 * so that rays are evenly spaced according to the field of view. The formula
 * centers the rays around zero and applies a scaling factor based on the FOV.
 *
 * @param fov The field of view in radians.
 * @param ray_base_x Array to store the precomputed X offsets for each column.
 */
static void	set_base_x(double fov, double *ray_base_x)
{
	int		i;
	double	ratio_hor;

	i = -1;
	ratio_hor = 2 * tan(fov * 0.5) / WINDOW_WIDTH;
	while (++i < WINDOW_WIDTH)
		ray_base_x[i] = (i - WINDOW_WIDTH * 0.5) * ratio_hor;
}

int	setup_mlx_context(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (!cube->mlx)
		return (1);
	cube->mlx_window = mlx_new_window(cube->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3D");
	if (!cube->mlx_window)
		return (1);
	if (create_frame(cube))
		return (1);
	if (init_wall_textures(cube))
		return (1);
	cube->fov = (FOV * PI / 180);
	cube->dist_proj = (WINDOW_WIDTH * 0.5) / tan(cube->fov * 0.5);
	set_base_x(cube->fov, cube->ray_base_x);
	return (0);
}
