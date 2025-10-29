/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:57:01 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/29 14:57:02 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "parsing.h"
#include "error.h"

static char	*safe_gnl(t_cube *cube, int fd, int *error)
{
	char	*line;

	line = get_next_line(fd, error);
	if (*error == -1)
		ft_error(cube, "Get next line failed");
	return (line);
}

void	validate_config_completeness(t_cube *cube, char *line)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cube->config.textures[i] == NULL)
		{
			free(line);
			ft_error(cube, "Missing texture");
		}
		i++;
	}
	if (cube->config.color[CEILING].is_set == 0
		|| cube->config.color[FLOOR].is_set == 0)
	{
		free(line);
		ft_error(cube, "Missing color");
	}
}

int	check_extension(char *path, char *ext)
{
	char	*current;

	current = ft_strrchr(path, '.');
	if (!current)
		return (-1);
	if (ft_strncmp(current, ext, 5))
		return (-1);
	return (0);
}

void	parse_cub_file(t_cube *cube, char *file)
{
	char	*line;
	int		error;

	error = 0;
	cube->fd_file = open(file, O_RDONLY);
	if (cube->fd_file == -1)
		ft_error(cube, "File doesn't exist");
	line = safe_gnl(cube, cube->fd_file, &error);
	while (line && !is_map_line(line))
	{
		parse_config(cube, line);
		free(line);
		line = safe_gnl(cube, cube->fd_file, &error);
	}
	if (!is_map_line(line))
		ft_error(cube, "The map seems empty");
	validate_config_completeness(cube, line);
	build_map(cube, line, cube->fd_file);
	if (validate_map_content(cube, cube->map) == 1)
		ft_error(cube, "Invalid character in map");
	if (cube->character.orientation == -1)
		ft_error(cube, "Character is not set");
	validate_map_content_closure(cube);
}

t_cube	*parse_cub(char **av)
{
	t_cube	*cube;

	cube = malloc(sizeof(t_cube));
	if (!cube)
		ft_error(cube, "Malloc failed");
	*cube = (t_cube){0};
	cube->character.orientation = -1;
	if (check_extension(av[1], ".cub") == -1)
		ft_error(cube, "Invalid name format");
	parse_cub_file(cube, av[1]);
	return (cube);
}
