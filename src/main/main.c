/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:36 by nimadela          #+#    #+#             */
/*   Updated: 2025/11/04 15:35:03 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "init.h"
#include "parsing.h"
#include "cleanup.h"
#include "error.h"
#include "../moves/moves.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>

int	main(int ac, char **av)
{
	t_cube	*cube;

	if (ac != 2)
	{
		print_error("Wrong number of arguments");
		return (1);
	}
	cube = parse_cub(av);
	if (setup_mlx_context(cube))
		ft_error(cube, "Init mlx failed");
	mlx_hook(cube->mlx_window, 2, 1L << 0, key_press, cube);
	mlx_hook(cube->mlx_window, 3, 1L << 1, key_release, cube);
	mlx_hook(cube->mlx_window, 17, 0, close_window, cube);
	mlx_hook(cube->mlx_window, 6, 1L << 6, mouse_motion_handler, cube);
	mlx_loop_hook(cube->mlx, render_frame, cube);
	mlx_loop(cube->mlx);
}
