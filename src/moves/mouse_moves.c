/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:34:02 by lserodon          #+#    #+#             */
/*   Updated: 2025/11/04 16:19:56 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "moves.h"
#include <stdio.h>

int	mouse_motion_handler(int x, int y, t_cube *cube)
{
	(void)y;
	int			delta_x;
	static int	old_x = WINDOW_WIDTH * 0.5;

	delta_x = x - old_x;
	if (x == old_x)
		return (0);
	cube->character.orientation += delta_x * 0.002;
	mlx_mouse_move(cube->mlx, cube->mlx_window, WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);
	old_x = WINDOW_WIDTH * 0.5;
	return (0);
}