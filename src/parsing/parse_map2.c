/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:38:36 by lserodon          #+#    #+#             */
/*   Updated: 2025/10/30 09:45:09 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cleanup.h"

void	build_map(t_cube *cube, char *line, int fd)
{
	t_list	*tmp_map;

	tmp_map = read_map_lines(cube, fd, line);
	cube->y_max = ft_lstsize(tmp_map);
	cube->x_max = get_map_width(tmp_map);
	cube->map = malloc(sizeof(char *) * (cube->y_max + 1));
	if (!cube->map)
	{
		free_tmp_map(tmp_map);
		ft_error(cube, "Malloc failed");
	}
	ft_bzero(cube->map, sizeof(char *) * (cube->y_max + 1));
	fill_map(cube, tmp_map);
}

size_t	get_map_width(t_list *tmp_map)
{
	size_t	len;

	len = 0;
	while (tmp_map)
	{
		if (ft_strlen(tmp_map->content) > len)
			len = ft_strlen(tmp_map->content);
		tmp_map = tmp_map->next;
	}
	return (len);
}
