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

size_t	find_max_len(t_list *tmp_map)
{
	size_t	len;

	len = 0;
	while(tmp_map)
	{
		if (ft_strlen(tmp_map->content) > len)
			len = ft_strlen(tmp_map->content);
		tmp_map = tmp_map->next;
	}
	return (len);
}

void	check_map(t_cube *cube)
{
	size_t	max_len;
	int i;

	i = 0;
	max_len = find_max_len(cube->map);
	//adjust_map(cube->map, max_len);
} 

void	fill_map(t_cube *cube, char *line, int fd)
{
	t_list	*tmp_map;
	int		max_len;
	int		count;
	int		i;

	tmp_map = ft_lstnew(line);
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&tmp_map, ft_lstnew(line));
		line = get_next_line(fd);
	}
	count = ft_lstsize(tmp_map);
	max_len = find_max_len(tmp_map);
	cube->map = malloc(sizeof(char *) * (count + 1));
	if (!cube->map)
		ft_error(cube, "Malloc failed");
	i = 0;
	while (tmp_map)
	{
		cube->map[i] = malloc(sizeof(char) * max_len);
		ft_memset(cube->map[i], ' ', max_len - 1);
		cube->map[i][max_len - 1] = '\0';
		ft_memmove(cube->map[i], tmp_map->content, ft_strlen(tmp_map->content) - 1);
		printf("%s\n", cube->map[i]);
		i++;
		tmp_map = tmp_map->next;
	}
	cube->map[i] = NULL;
	free(tmp_map);
}

/* 
int	check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0; 
	while(map && map[i])
	{
		while(map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0' && map[i][j])
			j++;
		}
	}
} */

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
	//check_map(cube);
	free(line);
}
