/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:24 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/29 14:56:25 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVES_H
# define MOVES_H

# include <stdlib.h>
# include "cube.h"

/* ----- MOVES.C ----- */
void	move_character(t_cube *cube, double dx, double dy);
void	move(t_cube *cube, int forward, double move_speed);
void	strafe(t_cube *cube, int direction, double move_speed);
void	rotate(t_cube *cube, int direction, double rot_speed);
int		update_moves(t_cube *cube);

/* ----- EVENTS.C ----- */
int		close_window(t_cube *cube);
int		key_press(int keycode, t_cube *cube);
int		key_release(int keycode, t_cube *cube);

/* ----- COLLISIONS.C ----- */
int		is_valid_position(t_cube *cube, double x, double y);

#endif