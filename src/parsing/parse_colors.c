/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:51 by nimadela          #+#    #+#             */
/*   Updated: 2025/11/05 18:26:05 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cleanup.h"

static void	rgb_error(char **color, char *line, char *tmp)
{
	free(line);
	free_tab(color);
	free(tmp);
}

static	int	parse_value(t_cube *cube, char **color, char *line, char *comp)
{
	int		value;
	char	*tmp_trimmed;

	tmp_trimmed = ft_strtrim(comp, " \t\n");
	if (!tmp_trimmed
		|| ft_strncmp(tmp_trimmed, "\0", ft_strlen(tmp_trimmed)) == 0)
	{
		rgb_error(color, line, tmp_trimmed);
		ft_error(cube, "Invalid RGB component");
	}
	if (is_numeric_string(tmp_trimmed) == 1)
	{
		rgb_error(color, line, tmp_trimmed);
		ft_error(cube, "Invalid RGB component: must be digits only");
	}
	value = ft_atoi(tmp_trimmed);
	free(tmp_trimmed);
	if (value < 0 || value > 255)
	{
		rgb_error(color, line, NULL);
		ft_error(cube, "RGB value out of range (0-255)");
	}
	return (value);
}

void	parse_rgb(t_cube *cube, char **color, t_color_type type, char *line)
{
	int	i;

	i = 0;
	while (color[i])
	{
		cube->config.color[type].rgb[i]
			= parse_value(cube, color, line, color[i]);
		i++;
	}
	free_tab(color);
}

void	parse_color_line(t_cube *cube, char *line)
{
	char			**color;
	t_color_type	type;
	int				count;

	while (*line && *line == ' ')
		line++;
	type = identify_color_type(line);
	color = ft_split(line + 2, ',');
	if (!color)
	{
		free(line);
		ft_error(cube, "Malloc failed");
	}
	count = count_tokens(color);
	if (count != 3)
	{
		rgb_error(color, line, NULL);
		ft_error(cube, "Invalid color format: expected 3 values");
	}
	if (cube->config.color[type].is_set == 1)
	{
		rgb_error(color, line, NULL);
		ft_error(cube, "Color defined multiple times");
	}
	parse_rgb(cube, color, type, line);
	cube->config.color[type].is_set = 1;
}
