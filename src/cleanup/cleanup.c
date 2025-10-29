/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:32 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/29 14:56:33 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"
#include "mlx.h"
#include <unistd.h>
#include "libft.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tmp_map(t_list *tmp_map)
{
	t_list	*tmp;

	while (tmp_map)
	{
		tmp = tmp_map->next;
		free(tmp_map->content);
		free(tmp_map);
		tmp_map = tmp;
	}
}

static void	destroy_wall_textures(t_cube *cube)
{
	int	i;

	i = -1;
	while (++i < NB_TEXTURES)
	{
		mlx_destroy_image(cube->mlx, cube->sprites.text_wall[i].mlx_ptr);
		cube->sprites.text_wall[i].mlx_ptr = NULL;
	}
}

static void	clear_mlx(t_cube *cube)
{
	if (cube->sprites.text_wall[0].mlx_ptr)
		destroy_wall_textures(cube);
	if (cube->sprites.frame.mlx_ptr)
	{
		mlx_destroy_image(cube->mlx, cube->sprites.frame.mlx_ptr);
		cube->sprites.frame.mlx_ptr = NULL;
	}
	if (cube->mlx_window)
	{
		mlx_destroy_window(cube->mlx, cube->mlx_window);
		cube->mlx_window = NULL;
	}
	if (cube->mlx)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
		cube->mlx = NULL;
	}
}

void	free_cube(t_cube *cube)
{
	int	i;

	i = -1;
	if (!cube)
		return ;
	while (++i < 4)
		free(cube->config.textures[i]);
	i = -1;
	if (cube->map)
	{
		if (cube->map[i + 1])
		{
			while (++i < cube->y_max)
				free(cube->map[i]);
		}
		free(cube->map);
	}
	if (cube->mlx)
		clear_mlx(cube);
	close(cube->fd_file);
	free(cube);
}
