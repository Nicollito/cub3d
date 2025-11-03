/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:33:44 by lserodon          #+#    #+#             */
/*   Updated: 2025/11/03 14:20:00 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minimap.h"
#include "cube.h"
#include "mlx.h"

void	put_pixel(t_image *minimap, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || x >= minimap->width || y < 0 || y >= minimap->height)
		return ;
	offset = (y * minimap->data.line_length)
		+ (x * minimap->data.bits_per_pixel * 0.125);
	pixel = (char *)minimap->data.mem + offset;
	*(unsigned int *)pixel = color;
}

void	draw_square(t_minimap *minimap, float map_x, float map_y, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y < minimap->tile_size)
	{
		x = -1;
		while (++x < minimap->tile_size)
			put_pixel(&minimap->image, (int)(map_x * minimap->tile_size + x),
				(int)(map_y * minimap->tile_size + y), color);
	}
}

void	update_minimap_view(t_cube *cube, t_minimap *minimap)
{
	minimap->start_x = cube->character.x - minimap->radius;
	minimap->start_y = cube->character.y - minimap->radius;
	minimap->end_x = cube->character.x + minimap->radius;
	minimap->end_y = cube->character.y + cube->minimap.radius;
}

void	draw_minimap(t_cube *cube, t_minimap*minimap)
{
	int	color;
	int	y;
	int	x;

	update_minimap_view(cube, minimap);
	y = floor(minimap->start_y) - 1;
	while (++y < ceil(minimap->end_y))
	{
		x = floor(minimap->start_x) - 1;
		while (++x < ceil(minimap->end_x))
		{
			if (y < 0 || y >= cube->y_max || x < 0
				|| x >= cube->x_max
				|| cube->map[y][x] == ' '
				|| cube->map[y][x] == '\0')
				color = 0x000000;
			else if (cube->map[y][x] == '1')
				color = 0x333333;
			else
				color = 0xAAAAAA;
			draw_square(minimap, x - minimap->start_x,
				y - minimap->start_y, color);
		}
	}
	draw_player(minimap, cube, minimap->start_x, minimap->start_y);
}

void	draw_player(t_minimap *minimap, t_cube *cube,
		float start_x, float start_y)
{
	int		y;
	int		x;
	int		size;
	float	player_x;
	float	player_y;

	size = 5;
	player_x = (cube->character.x - start_x) * minimap->tile_size;
	player_y = (cube->character.y - start_y) * minimap->tile_size;
	y = -size;
	while (++y <= size)
	{
		x = -size;
		while (++x <= size)
			put_pixel(&minimap->image, player_x + x, player_y + y, 0xFF0000);
	}
}

