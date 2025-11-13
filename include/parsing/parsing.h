/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:27 by nimadela          #+#    #+#             */
/*   Updated: 2025/11/13 13:43:37 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* ----- LIBRARIES ----- */
# include <fcntl.h>
# include <stdio.h>
# include "cube.h"
# include "libft.h"
# include "get_next_line.h"
# include "error.h"

/* ----- PARSING.C ----- */
void			free_cube(t_cube *cube);
int				check_extension(char *path, char *ext);
t_cube			*parse_cub(char **av);

/* ----- PARSE_COLORS.C ----- */
t_color_type	identify_color_type(char *line);
int				is_numeric_string(char *str);
void			parse_color_line(t_cube *cube, char *line);

/* ----- PARSE_CONFIG.C ----- */
void			parse_config(t_cube *cube, char *line);

/* ----- PARSE_MAP.C ----- */
void			fill_map_line(t_cube *cube, t_list *tmp_map, int i);
void			build_map(t_cube *cube, char *line, int fd);
size_t			get_map_width(t_list *tmp_map);
t_list			*read_map_lines(t_cube *cube, int fd, char *line);
void			fill_map(t_cube *cube, t_list *tmp_map);

/* ----- PARSE_TEXTURES.C ----- */
void			parse_texture(t_cube *cube, char *line);

/* ----- UTILS_PARSING.C ----- */
int				is_player_symbol(char c);
int				is_texture_line(char *line);
int				is_color_line(char *line);
int				is_empty_line(char *line);
int				is_map_line(char *line);

/* ----- VALIDATE_MAP.C ----- */
void			validate_map_content_closure(t_cube *cube);
void			fill_character_position(t_cube *cube, char **map, int i, int j);
int				validate_map_content(t_cube *cube, char **map);
int				validate_map_boundaries(char *line);
void			free_cube(t_cube *cube);

#endif