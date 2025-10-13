#ifndef PARSING_H
# define PARSING_H

/* ----- LIBRARIES ----- */
#include <fcntl.h>
#include <stdio.h>
#include "cube.h"
#include "libft.h"
#include "get_next_line.h"
#include "error.h"

/* ----- PARSING.C ----- */
void	free_cube(t_cube *cube);
int		is_texture_line(char *line);
int		is_color_line(char *line);
int		is_map_line(char *line);
int		line_is_empty(char *line);
void	parse_config(t_cube *cube, char *line);
void	check_all_values(t_cube *cube);
t_cube	*parsing(char **av);

/* ----- PARSING_COLORS.C ----- */
t_color_type	get_color_type(char *line);
int				count_split(char **color);
int				str_isdigit(char *str);
void			parse_color(t_cube *cube, char *line);

/* ----- PARSING_FILENAME.C ----- */
int		name_file(char *file);
void	check_file(t_cube *cube, char *file);

/* ----- PARSING_TEXTURES.C ----- */
t_texture_type get_texture_type(char *line);
void	parse_texture(t_cube *cube, char *line);


#endif