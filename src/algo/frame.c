/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:55:32 by nimadela          #+#    #+#             */
/*   Updated: 2025/11/03 13:53:00 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "algo.h"
#include "mlx.h"
#include "libft.h"
#include <sys/time.h>
#include <stdio.h>
#include "../moves/moves.h"
#include "minimap.h"

/**
 * @brief Checks if a new second has passed since the last check.
 *
 * This function uses `gettimeofday` to compare the current second with the
 * last recorded second. It returns 1 if a new second has started, otherwise 0.
 *
 * @return 1 if a second has passed, 0 otherwise.
 */
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

/**
 * @brief Counts frames and prints the FPS every second.
 *
 * This function increments a static frame counter and, when a new second is
 * detected, prints the number of frames rendered in the previous second to
 * the console. The counter is reset afterward.
 */
static void	print_fps(void)
{
	static int	frames = 0;

	frames++;
	if (second_past())
	{
		printf("FPS [%d]\n", frames);
		frames = 0;
	}
}

/**
 * @brief Initializes the raycasting algorithm structure from the cube data.
 *
 * This function copies relevant data such as character position, map,
 * projection distance, and ray base offsets from the main cube structure
 * into the `algo` structure for use in rendering.
 *
 * @param cube Pointer to the main cube structure.
 * @param algo Pointer to the algorithm structure to initialize.
 */
static void	set_algo(t_cube cube, t_algo *algo)
{
	algo->character = cube.character;
	algo->ray_base_x = cube.ray_base_x;
	algo->map = cube.map;
	algo->dist_proj = cube.dist_proj;
	algo->y_max = cube.y_max;
	algo->x_max = cube.x_max;
}

/**
 * @brief Performs the main raycasting loop to render the 3D scene.
 *
 * This function iterates over each vertical screen column, casts a ray from
 * the player's position, computes wall intersections, determines wall height
 * and texture, and draws the corresponding column in the frame buffer. The
 * ceiling and floor are rendered together with the wall in each column.
 *
 * @param color Array of colors used for ceiling and floor rendering.
 * @param sprites Structure containing all textures and the frame buffer.
 * @param algo Structure holding the map, character data, projection distance,
 * and precomputed ray base offsets.
 */
static void	raycasting(t_color *color, t_sprites sprites, t_algo algo)
{
	t_wall		wall;
	t_calc		data;

	ft_memset(&wall, 0, sizeof(t_wall));
	ft_memset(&data, 0, sizeof(t_calc));
	wall.column = -1;
	while (++wall.column < WINDOW_WIDTH)
	{
		get_write_value(algo, &wall, &data, wall.column);
		write_column(sprites, wall, data, color);
	}
}

int	render_frame(t_cube *cube)
{
	t_algo	algo;

	set_algo(*cube, &algo);
	update_moves(cube);
	draw_minimap(cube, &cube->minimap);
	raycasting(cube->config.color, cube->sprites, algo);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window,
		cube->sprites.frame.mlx_ptr, 0, 0);
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, 
			cube->minimap.image.mlx_ptr, (WINDOW_WIDTH - cube->minimap.image.width - 20), 
			(WINDOW_HEIGHT - cube->minimap.image.height - 20));
	print_fps();
	return (0);
}
