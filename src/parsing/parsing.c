#include "libft.h"
#include "get_next_line.h"
#include "parsing.h"
#include "error.h"

void	free_cube(t_cube *cube)
{
	free(cube);
}

int	is_texture_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 ||
		ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "EA ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0)
			return (0);
	return (1);
}

int	is_color_line(char *line)
{
	if ((ft_strncmp(line, "C ", 2) == 0) ||
		ft_strncmp(line, "F ", 2) == 0)
			return (0);
	return (1);
}

int	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while(line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	is_map_line(char *line)
{
	int	i;
	int	is_line_map;

	i = 0;
	is_line_map = 0;
	while (line && line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			is_line_map = 1;
		else if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0); 
		i++;
	}
	return (is_line_map);
}


void	parse_config(t_cube *cube, char *line)
{
	if (line_is_empty(line) == 0)
		return ;
	else if (is_texture_line(line) == 0)
		parse_texture(cube, line);
	else if (is_color_line(line) == 0)
		parse_color(cube, line);
	else
	{
		ft_error(cube, "Invalid line in .cub file");
		printf("%s\n", line);
	}
}

void	check_all_values(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cube->config.textures[i] == NULL)
			ft_error(cube, "Missing texture");
		i++;
	}
	if (cube->config.color[CEILING].is_set == 0 || cube->config.color[FLOOR].is_set == 0)
		ft_error(cube, "Missing color");
}



t_cube	*parsing(char **av)
{
	t_cube	*cube;

	cube = malloc(sizeof(t_cube));
	if (!cube)
		ft_error(cube, "Malloc failed");
	*cube = (t_cube){0};
	if (name_file(av[1]))
		ft_error(cube, "Invalid name format");
	check_file(cube, av[1]);
	return (cube);
}
