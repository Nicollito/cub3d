#include "parsing.h"

void	parse_config(t_cube *cube, char *line)
{
	if (is_empty_line(line))
		return ;
	else if (is_texture_line(line))
		parse_texture(cube, line);
	else if (is_color_line(line))
		parse_color_line(cube, line);
	else
	{
		ft_error(cube, "Invalid line in .cub file");
		printf("%s\n", line);
	}
}
