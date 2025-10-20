#include "parsing.h"

int	is_player_symbol(char c)
{
	if (c != 'W' && c != 'N' && c != 'S' && c != 'E')
		return (1);
	return (0);
}

int	is_texture_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	return (0);
}

int	is_color_line(char *line)
{
	if ((ft_strncmp(line, "C ", 2) == 0)
		|| ft_strncmp(line, "F ", 2) == 0)
		return (1);
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
