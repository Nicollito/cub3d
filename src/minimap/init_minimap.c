/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:19:50 by lserodon          #+#    #+#             */
/*   Updated: 2025/11/06 15:57:52 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minimap.h"

int	init_minimap(t_cube *cube, t_image *image)
{
	int	ratio;

	ratio = WINDOW_WIDTH * 0.15;
	image->width = ratio;
	image->height = ratio;
	image->mlx_ptr = mlx_new_image(cube->mlx, image->width,
			image->height);
	if (!image->mlx_ptr)
		return (1);
	image->data.mem = mlx_get_data_addr(image->mlx_ptr,
			&image->data.bits_per_pixel,
			&image->data.line_length, &image->data.endian);
	cube->minimap.radius = 5.0f;
	cube->minimap.tile_size = image->width / 10;
	return (0);
}
