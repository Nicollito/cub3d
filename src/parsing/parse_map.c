#include "parsing.h"

void	free_tmp_stack(t_list *list)
{
	t_list	*tmp_list;

	while (list)
	{
		tmp_list = list->next;
		printf("%s\n", (char *)list->content);
		free(list);
		list = tmp_list;
	}
	free(list);
}

void	fill_map_line(t_cube *cube, t_list *tmp_map, int i)
{
	size_t	len;

	len = ft_strlen(tmp_map->content);
	if (((char *)tmp_map->content)[len - 1] == '\n')
		len--;
	cube->map[i] = malloc(sizeof(char) * cube->x_max);
	if (!cube->map[i])
		ft_error(cube, "Malloc failed");
	ft_memset(cube->map[i], ' ', cube->x_max);
	ft_memmove(cube->map[i], tmp_map->content, len);
	cube->map[i][cube->x_max - 1] = '\0';
	printf("%s\n", cube->map[i]);
}

void	build_map(t_cube *cube, char *line, int fd)
{
	t_list	*tmp_map;
	t_list	*tmp;
	int		i;

	tmp_map = ft_lstnew(line);
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&tmp_map, ft_lstnew(line));
		line = get_next_line(fd);
	}
	cube->y_max = ft_lstsize(tmp_map);
	cube->x_max = get_map_width(tmp_map);
	cube->map = malloc(sizeof(char *) * (cube->y_max + 1));
	if (!cube->map)
		ft_error(cube, "Malloc failed");
	i = 0;
	while (tmp_map)
	{
		tmp = tmp_map->next;
		fill_map_line(cube, tmp_map, i);
		i++;
		free(tmp_map->content);
		free(tmp_map);
		tmp_map = tmp;
	}
	cube->map[i] = NULL;
}

int	count_map_line(char *line, int fd)
{
	int	count;

	count = 1;
	while (line)
	{
		if (is_map_line(line))
		{
			printf("%s\n", line);
			count++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	return (count);
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
