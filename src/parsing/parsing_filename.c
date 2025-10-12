#include "parsing.h"

int	name_file(char *file)
{
	char	*current;

	current = ft_strrchr(file, '.');
	if (!current)
		return (1);
	if (ft_strncmp(current, ".cub", 5))
		return (1);
	return (0);
}

int		count_lines(char *line, int fd)
{
	int		count;

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

void	fill_map(t_cube *cube, char *line, int fd)
{
	t_list	*tmp_map;
	int		count;
	int		i;

	tmp_map = ft_lstnew(ft_strdup(line));
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&tmp_map, ft_lstnew(ft_strdup(line)));
		free(line);
		line = get_next_line(fd);
	}
	count = ft_lstsize(tmp_map);
	cube->map = malloc(sizeof(char *) * count);
	if (!cube->map)
		ft_error(cube, "Malloc failed");
	i = 0;
	while (tmp_map)
	{
		cube->map[i] = ft_strdup(tmp_map->content);
		i++;
		tmp_map = tmp_map->next;
	}
	free(tmp_map);
}

void	check_file(t_cube *cube, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(cube, "File doesn't exist");
	line = get_next_line(fd);
	while (line && !is_map_line(line))
	{
		parse_config(cube, line);
		free(line);
		line = get_next_line(fd);
	}
	check_all_values(cube);
	fill_map(cube, line, fd);
	free(line);
}
