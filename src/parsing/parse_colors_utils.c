#include "parsing.h"

t_color_type	identify_color_type(char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
		return (CEILING);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (FLOOR);
	return (INVALID_COLOR);
}

int	count_tokens(char **color)
{
	int	i;

	i = 0;
	while (color[i])
		i++;
	return (i);
}

int	is_numeric_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
