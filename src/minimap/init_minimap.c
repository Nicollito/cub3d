/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:19:50 by lserodon          #+#    #+#             */
/*   Updated: 2025/11/13 13:35:32 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minimap.h"

int	init_minimap(t_cube *cube, t_image *image)
{
	image->width = 300;
	image->height = 300;
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
