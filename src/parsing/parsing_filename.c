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
	int count;

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

void	fill_map(t_cube *cube, char *line, int fd)
{
	t_list	*tmp_map;
	size_t	len;
	int		max_len;
	int		i;

	tmp_map = ft_lstnew(line);
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&tmp_map, ft_lstnew(line));
		line = get_next_line(fd);
	}
	cube->y_max = ft_lstsize(tmp_map);
	max_len = find_max_len(tmp_map);
	cube->map = malloc(sizeof(char *) * (cube->y_max + 1));
	if (!cube->map)
		ft_error(cube, "Malloc failed");
	i = 0;
	while (tmp_map)
	{
		len = ft_strlen(tmp_map->content);
		if (((char *)tmp_map->content)[len - 1] == '\n')
			len--;
		cube->map[i] = malloc(sizeof(char) * max_len);
		ft_memset(cube->map[i], ' ', max_len);
		ft_memmove(cube->map[i], tmp_map->content, len);
		cube->map[i][max_len - 1] = '\0';
		printf("%s\n", cube->map[i]);
		i++;
		tmp_map = tmp_map->next;
	}
	cube->map[i] = NULL;
	free(tmp_map);
}

int	check_position(char c)
{
	if (c != 'W' && c != 'N' && c != 'S' && c != 'E')
		return (1);
	return (0);
}

int	check_map(t_cube *cube, char **map)
{
	int	i;
	int	j;

	i = 0;
	while(map && map[i])
	{
		j = 0; 
		while(map[i][j])
		{
			if ((map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0') && check_position(map[i][j]) == 1)
				return (1);
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
			{
				if (cube->character.orientation != 0)
					ft_error(cube, "Map must contain exactly one player position");
				else
				{
					cube->character.x = j;
					cube->character.y = i;
					cube->character.orientation = map[i][j];
				}
			}
			j++;
		}
		i++;
	}
	if (cube->character.orientation == 0)
		ft_error(cube, "Character is not set");
	return (0);
}

int check_first_and_last_walls(char *line)
{
	int	i;

	i = 0;
	while(line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\0')
	{
		if (line[i] != '1')
			return(1);
		i++;
	}
	return (0);
}

int	is_playable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	check_walls(t_cube *cube)
{
	int	y;
	int x;

	y = 0;
	while (cube->map[y])
	{
		x = 0;
		while (cube->map[y][x])
		{
			if (is_playable(cube->map[y][x]))
			{
				if (y == 0 || y == cube->y_max - 1 ||
					x == 0 || cube->map[y][x + 1] == '\0')
					ft_error(cube, "Map not closed");
				if (cube->map[y - 1][x] == ' ' || cube->map[y + 1][x] == ' ' || cube->map[y][x - 1] == ' ' || cube->map[y][x + 1] == ' '
					|| cube->map[y-1][x+1] == ' ' || cube->map[y-1][x-1] == ' ' || cube->map[y+1][x+1] == ' ' || cube->map[y+1][x-1] == ' ')
					ft_error(cube, "Map not closed");
			}
			x++;
		}
		y++;
	}
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
	if (!is_map_line(line))
		ft_error(cube, "The map seems empty");
	check_all_values(cube);
	fill_map(cube, line, fd);
	if (check_map(cube, cube->map) == 1)
		ft_error(cube, "Invalid character in map");
	check_walls(cube);
	free(line);
}


