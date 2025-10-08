#include "libft.h"
#include "get_next_line.h"
#include "parsing.h"
#include "error.h"

static int	name_file(char *file)
{
	char	*current;

	current = ft_strrchr(file, '.');
	if (!current)
		return (1);
	if (ft_strncmp(current, ".cub", 5))
		return (1);
	return (0);
}

static int	check_file(t_cube *cube, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error("File doesn't exist");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	check_textures(t_cube *cube, char **av)
{

}

void	parsing(t_cube *cube, int ac, char **av)
{
	if (name_file(av[1]))
	{
		print_error("Invalid name format");
		exit(1);
	}
	check_file(cube, av[1]);
	check_file_infos
}
