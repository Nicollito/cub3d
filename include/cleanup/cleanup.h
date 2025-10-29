#ifndef CLEANUP_H
# define CLEANUP_H

# include <stdlib.h>
# include "cube.h"
# include "libft.h"

void	free_tab(char **tab);
void	free_tmp_map(t_list *tmp_map);
void	free_cube(t_cube *cube);

#endif