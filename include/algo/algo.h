/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:55:01 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/29 14:55:02 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

typedef enum e_side
{
	VERTICAL,
	HORIZONTAL,
}	t_side;

typedef struct wall
{
	int				column;
	int				line;
	int				text_x;
	double			text_y;
	double			text_step;
	int				height;
	int				draw_start;
	int				draw_end;
	t_side			side;
	t_texture_type	texture;
}					t_wall;

typedef struct calculator
{
	double	step;
	double	ray_x;
	double	ray_y;
	double	ray_dir_x;
	double	ray_dir_y;
}			t_calc;

typedef struct algo
{
	t_char		character;
	double		*ray_base_x;
	char		**map;
	double		dist_proj;
	int			y_max;
	int			x_max;
}				t_algo;

/* ------------------algo/------------------ */

// render.c

/**
 * @brief Renders a full column (wall, ceiling, and floor) into the frame.
 *
 * This function draws a complete vertical column on the screen, including the
 * ceiling, wall, and floor. Wall pixels are taken from the corresponding wall
 * texture, while ceiling and floor pixels use their solid colors. Texture
 * coordinates are calculated to match wall height and perspective.
 *
 * @param sprite The sprite structure containing textures and the frame
 * buffer.
 * @param wall The wall structure containing texture coordinates, draw limits,
 * and height.
 * @param data Calculation data containing ray intersection info and step
 * values.
 * @param color The color array containing ceiling and floor RGB values.
 */
void	write_column(t_sprites sprite, t_wall wall, t_calc data,
			t_color *color);

// setup.c

/**
 * @brief Calculates ray intersection and wall projection for a screen column.
 *
 * This function initializes ray data, casts the ray to find the wall hit,
 * computes the wall's projected height, and determines the starting Y
 * position to draw the wall column on screen.
 *
 * @param algo Structure containing the map, character, projection distance,
 * and precomputed ray base offsets.
 * @param wall Pointer to the wall structure to update height, draw start,
 * side, and texture.
 * @param data Pointer to the calculation structure for ray traversal.
 * @param column Screen column index where the wall slice will be rendered.
 */
void	get_write_value(t_algo algo, t_wall *wall, t_calc *data, int column);

#endif