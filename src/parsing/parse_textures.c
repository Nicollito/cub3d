#include "parsing.h"

t_texture_type	identify_texture_type(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (TEXT_NO);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (TEXT_EA);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (TEXT_SO);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (TEXT_WE);
	return (INVALID_TEXTURE);
}

void	parse_texture(t_cube *cube, char *line)
{
	t_texture_type	type;
	char			*path;
	int				fd;

	type = identify_texture_type(line);
	if (type == INVALID_TEXTURE)
		ft_error(cube, "Invalid texture identifier");
	path = ft_strtrim(line + 2, " \n");
	if (!path)
		ft_error(cube, "Texture path missing");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error(cube, "Texture path doesn't exist");
	if (cube->config.textures[type] != NULL)
		ft_error(cube, "Texture defined multiple times");
	cube->config.textures[type] = path;
}
