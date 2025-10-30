/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:56 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/30 09:45:04 by lserodon         ###   ########.fr       */
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

void	fill_map(t_cube *cube, t_list *tmp_map)
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

static void	append_map_line(t_cube *cube, int fd, t_list **tmp_map, int *error)
{
	char	*line;
	t_list	*tmp_node;

	line = safe_gnl(cube, fd, error, *tmp_map);
	while (line)
	{
		tmp_node = ft_lstnew(line);
		if (!tmp_node)
		{
			free(line);
			free_tmp_map(*tmp_map);
			ft_error(cube, "Malloc failed");
		}
		ft_lstadd_back(tmp_map, tmp_node);
		line = safe_gnl(cube, fd, error, *tmp_map);
	}
	free(line);
}

t_list	*read_map_lines(t_cube *cube, int fd, char *line)
{
	t_list	*tmp_map;
	int		error;

	error = 0;
	tmp_map = ft_lstnew(line);
	if (!tmp_map)
	{
		free(line);
		ft_error(cube, "Malloc failed");
	}
	append_map_line(cube, fd, &tmp_map, &error);
	return (tmp_map);
}
