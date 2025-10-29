/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:58 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/29 14:56:59 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	textures_error(t_cube *cube, char *line, char *path, char *msg)
{
	free(line);
	free(path);
	ft_error(cube, msg);
}

t_texture_type	identify_texture_type(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (TEXT_NO);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (TEXT_EA);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (TEXT_SO);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (TEXT_WE);
	return (INVALID_TEXTURE);
}

void	parse_texture(t_cube *cube, char *line)
{
	t_texture_type	type;
	char			*path;
	int				fd;

	type = identify_texture_type(line);
	path = ft_strtrim(line + 2, " \n");
	if (!path)
	{
		free(line);
		ft_error(cube, "Texture path missing");
	}
	if (check_extension(path, ".xpm") == -1)
		textures_error(cube, line, path, "Invalid texture name format");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		textures_error(cube, line, path, "Texture path doesn't exist");
	close(fd);
	if (cube->config.textures[type] != NULL)
		textures_error(cube, line, path, "Texture defined multiple times");
	cube->config.textures[type] = path;
}
