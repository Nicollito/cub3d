#include "parsing.h"

t_color_type get_color_type(char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
		return (CEILING);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (FLOOR);
	return (INVALID_COLOR);
}

int	count_split(char **color)
{
	int i;

	i = 0;
	while(color[i])
		i++;
	return (i);
}

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] < 0 || str[i] > 9)
			return (1); 
		i++;
	}
	return (0);
}

void	parse_color(t_cube *cube, char *line)
{
	char			**color;
	char			*tmp_trimmed;
	t_color_type 	type;
	int				i;
	int				count;
	int				value;

	i = 0;
	type = get_color_type(line);
	if (type == INVALID_COLOR)
		ft_error(cube, "Invalid color identifier");
	color = ft_split(line + 2, ',');
	count = count_split(color);
	if (count != 3)
		ft_error(cube, "Invalid color format: expected 3 values");
	if (cube->config.color[type].is_set == 1)
		ft_error(cube, "Color defined multiple times");
	while (color[i])
	{
		tmp_trimmed = ft_strtrim(color[i], " \t\n");
		if (!tmp_trimmed || ft_strncmp(tmp_trimmed, "\0", ft_strlen(tmp_trimmed)) == 0)
			ft_error(cube, "Invalid RGB component");
		if (str_isdigit(tmp_trimmed) == 0)
			ft_error(cube, "Invalid RGB component: must be digits only");
		value = ft_atoi(tmp_trimmed);
		free(tmp_trimmed);
		if (value < 0 || value > 255)
			ft_error(cube, "RGB value out of range (0-255)");
		cube->config.color[type].rgb[i] = value;
		free(color[i]);
		i++;
	}
	free(color);
	cube->config.color[type].is_set = 1;
}
