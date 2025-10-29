/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:56 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/29 14:56:57 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cleanup.h"

static char	*safe_gnl(t_cube *cube, int fd, int *error, t_list *tmp_map)
{
	char	*line;

	line = get_next_line(fd, error);
	if (*error == -1)
	{
		free_tmp_map(tmp_map);
		ft_error(cube, "Get next line failed");
	}
	return (line);
}

static void	fill_map(t_cube *cube, t_list *tmp_map)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (tmp_map)
	{
		tmp = tmp_map->next;
		fill_map_line(cube, tmp_map, i);
		free(tmp_map->content);
		free(tmp_map);
		i++;
		tmp_map = tmp;
	}
	cube->map[i] = NULL;
}

void	fill_map_line(t_cube *cube, t_list *tmp_map, int i)
{
	size_t	len;

	len = ft_strlen(tmp_map->content);
	if (((char *)tmp_map->content)[len - 1] == '\n')
		len--;
	cube->map[i] = malloc(sizeof(char) * cube->x_max);
	if (!cube->map[i])
	{
		free_tmp_map(tmp_map);
		ft_error(cube, "Malloc failed");
	}
	ft_memset(cube->map[i], ' ', cube->x_max);
	ft_memmove(cube->map[i], tmp_map->content, len);
	cube->map[i][cube->x_max - 1] = '\0';
}

void	build_map(t_cube *cube, char *line, int fd)
{
	int		error;
	t_list	*tmp_map;

	error = 0;
	tmp_map = ft_lstnew(line);
	line = safe_gnl(cube, fd, &error, tmp_map);
	while (line)
	{
		ft_lstadd_back(&tmp_map, ft_lstnew(line));
		line = safe_gnl(cube, fd, &error, tmp_map);
	}
	free(line);
	cube->y_max = ft_lstsize(tmp_map);
	cube->x_max = get_map_width(tmp_map);
	cube->map = malloc(sizeof(char *) * (cube->y_max + 1));
	if (!cube->map)
	{
		free_tmp_map(tmp_map);
		ft_error(cube, "Malloc failed");
	}
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
