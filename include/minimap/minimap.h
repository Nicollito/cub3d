/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:33:59 by lserodon          #+#    #+#             */
/*   Updated: 2025/11/06 15:56:40 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cube.h"

void	draw_minimap(t_cube *cube, t_minimap *minimap);
void	draw_player(t_minimap *minimap, t_cube *cube, float start_x,
			float start_y);
void	put_pixel(t_image *minimap, int x, int y, int color);
int		init_minimap(t_cube *cube, t_image *minimap);

#endif