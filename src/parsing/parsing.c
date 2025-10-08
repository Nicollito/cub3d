#include "libft.h"
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

void	parsing(int ac, char **av)
{
	if (ac != 2)
	{
		print_error("Invalid number of arguments");
		exit(1);
	}
	if (name_file(av[1]))
	{
		print_error("Invalid name format");
		exit(1);
	}
}
