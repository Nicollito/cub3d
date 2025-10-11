#ifndef PARSE_CONGIG_H
# define PARSE_CONFIG_H

#include "parsing.h"

void	parse_config(t_cube *cube, char *line);
int		is_texture_line(char *line);
int		is_color_line(char *line);

#endif