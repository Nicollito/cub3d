#include "libft.h"
#include "get_next_line.h"
#include "parsing.h"
#include "error.h"

void	free_cube(t_cube *cube)
{
	free(cube);
}

void	validate_config_completeness(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cube->config.textures[i] == NULL)
			ft_error(cube, "Missing texture");
		i++;
	}
	if (cube->config.color[CEILING].is_set == 0
		|| cube->config.color[FLOOR].is_set == 0)
		ft_error(cube, "Missing color");
}

int	check_cub_extension(char *file)
{
	char	*current;

	current = ft_strrchr(file, '.');
	if (!current)
		return (1);
	if (ft_strncmp(current, ".cub", 5))
		return (1);
	return (0);
}

void	parse_cub_file(t_cube *cube, char *file)
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
	validate_config_completeness(cube);
	build_map(cube, line, fd);
	if (validate_map_content(cube, cube->map) == 1)
		ft_error(cube, "Invalid character in map");
	if (cube->character.orientation == -1)
		ft_error(cube, "Character is not set");
	validate_map_content_closure(cube);
	free(line);
}

t_cube	*parse_cub(char **av)
{
	t_cube	*cube;

	cube = malloc(sizeof(t_cube));
	if (!cube)
		ft_error(cube, "Malloc failed");
	*cube = (t_cube){0};
	cube->character.orientation = -1;
	if (check_cub_extension(av[1]))
		ft_error(cube, "Invalid name format");
	parse_cub_file(cube, av[1]);
	return (cube);
}
