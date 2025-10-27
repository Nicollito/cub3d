#include "../moves/moves.h"

int	is_valid_position(t_cube *cube, double x, double y)
{
	int	map_x;
	int	map_y;
	int	i;
	int	j;

	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			map_x = (int)(x + i * 0.1);
			map_y = (int)(y + j * 0.1);
			if (cube->map[map_y][map_x] == '1' || cube->map[map_y][map_x] == ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
