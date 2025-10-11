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

void	check_file(t_cube *cube, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(cube, "File doesn't exist");
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line) == 0)
		{
			free (line);
			break;
		}
		parse_config(cube, line);
		free(line);
		line = get_next_line(fd);
	}
	check_all_values(cube);
}