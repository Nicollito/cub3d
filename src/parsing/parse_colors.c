/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:51 by nimadela          #+#    #+#             */
/*   Updated: 2025/11/13 13:40:25 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cleanup.h"

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

static void	parse_rgb(t_cube *cube, char **color, t_color_type type, char *line)
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

static void	count_tokens(t_cube *cube, char **color, char *line)
{
	int	i;

	i = 0;
	while (color[i])
		i++;
	if (i != 3)
	{
		rgb_error(color, line, NULL);
		ft_error(cube, "Invalid color format: expected 3 values");
	}
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

void	parse_color_line(t_cube *cube, char *line)
{
	char			**color;
	t_color_type	type;
	char			*line_trimmed;

	line_trimmed = trim_line(cube, line);
	type = identify_color_type(line_trimmed);
	color = ft_split(line_trimmed + 2, ',');
	free(line_trimmed);
	if (!color)
	{
		free(line);
		ft_error(cube, "Malloc failed");
	}
	count_tokens(cube, color, line);
	if (cube->config.color[type].is_set == 1)
	{
		rgb_error(color, line, NULL);
		ft_error(cube, "Color defined multiple times");
	}
	parse_rgb(cube, color, type, line);
	cube->config.color[type].is_set = 1;
}
