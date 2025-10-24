#include "parsing.h"

double	get_orientation_angle( char c)
{
	if (c == 'E')
		return (PI * 0.5);
	else if (c == 'N')
		return (PI * 2);
	else if (c == 'W')
		return (PI * 1.5);
	else if (c == 'S')
		return (PI);
	return (-1);
}

void	validate_map_content_closure(t_cube *cube)
{
	int	y;
	int	x;

	y = 0;
	while (cube->map[y])
	{
		x = 0;
		while (cube->map[y][x])
		{
			if (cube->map[y][x] == '0'
			|| is_player_symbol(cube->map[y][x]) == 0)
			{
				if (y == 0 || y == cube->y_max - 1
					|| x == 0 || cube->map[y][x + 1] == '\0')
					ft_error(cube, "Map not closed");
				if (cube->map[y - 1][x] == ' ' || cube->map[y + 1][x] == ' '
					|| cube->map[y][x - 1] == ' ' || cube->map[y][x + 1] == ' ')
					ft_error(cube, "Map not closed");
			}
			x++;
		}
		y++;
	}
}

void	fill_character_position(t_cube *cube, char **map, int i, int j)
{
	cube->character.x = j + 0.5;
	cube->character.y = i + 0.5;
	cube->character.orientation = get_orientation_angle(map[i][j]);
}

int	validate_map_content(t_cube *cube, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0')
				&& is_player_symbol(map[i][j]) == 1)
				return (1);
			if (map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'W')
			{
				if (cube->character.orientation != -1)
					ft_error(cube, "Map must contain one player position");
				else
					fill_character_position(cube, map, i, j);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map_boundaries(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\0')
	{
		if (line[i] != '1')
			return (1);
		i++;
	}
	return (0);
}
