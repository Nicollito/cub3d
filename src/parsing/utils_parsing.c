/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:57:08 by nimadela          #+#    #+#             */
/*   Updated: 2025/11/06 16:00:28 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_player_symbol(char c)
{
	if (c != 'W' && c != 'N' && c != 'S' && c != 'E')
		return (1);
	return (0);
}

int	is_texture_line(char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, " \t");
	if (ft_strncmp(tmp, "NO ", 3) == 0
		|| ft_strncmp(tmp, "SO ", 3) == 0
		|| ft_strncmp(tmp, "EA ", 3) == 0
		|| ft_strncmp(tmp, "WE ", 3) == 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	is_color_line(char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, " \t");
	if ((ft_strncmp(tmp, "C ", 2) == 0)
		|| ft_strncmp(tmp, "F ", 2) == 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
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
