/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:58 by nimadela          #+#    #+#             */
/*   Updated: 2025/11/14 11:31:38 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	textures_error(t_cube *cube, char *line, char *path, char *msg)
{
	free(line);
	free(path);
	ft_error(cube, msg);
}

static t_texture_type	identify_texture_type(t_cube *cube, char *line)
{
	char			*tmp;
	t_texture_type	res;

	res = INVALID_TEXTURE;
	tmp = ft_strtrim(line, " \t\n");
	if (!tmp)
	{
		free(line);
		ft_error(cube, "ft_strtrim failed");
	}
	if (ft_strncmp(tmp, "NO ", 3) == 0)
		res = TEXT_NO;
	else if (ft_strncmp(tmp, "EA ", 3) == 0)
		res = TEXT_EA;
	else if (ft_strncmp(tmp, "SO ", 3) == 0)
		res = TEXT_SO;
	else if (ft_strncmp(tmp, "WE ", 3) == 0)
		res = TEXT_WE;
	free (tmp);
	return (res);
}

static char	*trim_line(t_cube *cube, char *line)
{
	char	*line_trimmed;

	line_trimmed = ft_strtrim(line, " \t");
	if (!line_trimmed)
	{
		free(line);
		ft_error(cube, "ft_strtrim failed");
	}
	return (line_trimmed);
}

void	parse_texture(t_cube *cube, char *line)
{
	t_texture_type	type;
	char			*path;
	int				fd;
	char			*line_trimmed;

	line_trimmed = trim_line(cube, line);
	type = identify_texture_type(cube, line_trimmed);
	path = ft_strtrim(line_trimmed + 2, " \n");
	free(line_trimmed);
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
