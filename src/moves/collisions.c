/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:40 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/29 14:56:41 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../moves/moves.h"

int	is_valid_position(t_cube *cube, double x, double y)
{
	int	map_x;
	int	map_y;
	int	i;
	int	j;

	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			map_x = (int)(x + i * 0.1);
			map_y = (int)(y + j * 0.1);
			if (cube->map[map_y][map_x] == '1'
				|| cube->map[map_y][map_x] == ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
