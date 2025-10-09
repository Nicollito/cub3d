#include "libft.h"
#include "get_next_line.h"
#include "parsing.h"
#include "error.h"
#include <stdio.h>

int	name_file(char *file)
{
	char	*current;

	if (ft_strlen(file) < 5)
		return (1);
	current = ft_strrchr(file, '.');
	if (!current)
		return (1);
	if (ft_strncmp(current, ".cub", 5))
		return (1);
	return (0);
}

void	parse_texture(t_cube *cube, char *line)
{
	if (ft_strncmp(line, "NO", 3) == 0)
	{
		cube->config.text_no = line;
		printf("%s\n", cube->config.text_no);
	}
	else if (ft_strncmp(line, "SO", 3) == 0)
	{
		cube->config.text_so = line;
		printf("%s\n", cube->config.text_so);
	}
	else if (ft_strncmp(line, "EA", 3) == 0)
	{
		cube->config.text_ea = line;
		printf("%s\n", cube->config.text_ea);
	}
	else if (ft_strncmp(line, "WE", 3) == 0)
	{
		cube->config.text_we = line;
		printf("%s\n", cube->config.text_we);
	}
}

int		is_texture_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 ||
		ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "EA ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0)
			return (0);
	return (1);
}

void	parse_line(t_cube *cube, char *line)
{
	if (is_texture_line(line) == 0)
		parse_texture(cube, line);
	/* else if (is_color_line(line))
		parse_color(&cube->config, line);
	else if (is_map_line(line))
		add_map_line(&cube->config, line);
	else if (line_is_empty(line))
		return; */
	else
		print_error("Invalid line in .cub file");
}

void	check_file(t_cube *cube, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error("File doesn't exist");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		parse_line(cube, line);
		free(line);
		line = get_next_line(fd);
	}
}

void	parsing(t_cube *cube, int ac, char **av)
{
	(void)ac;
	if (name_file(av[1]))
	{
		print_error("Invalid name format");
		exit(1);
	}
	check_file(cube, av[1]);
}
