/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:24 by nimadela          #+#    #+#             */
/*   Updated: 2025/11/06 15:57:02 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVES_H
# define MOVES_H

# include <stdlib.h>
# include "cube.h"

/* ----- COLLISIONS.C ----- */
int		is_valid_position(t_cube *cube, double x, double y);

/* ----- EVENTS.C ----- */
int		close_window(t_cube *cube);
int		key_press(int keycode, t_cube *cube);
int		key_release(int keycode, t_cube *cube);

/* ----- MOVES.C ----- */
void	move_character(t_cube *cube, double dx, double dy);
void	move(t_cube *cube, int forward, double move_speed);
void	strafe(t_cube *cube, int direction, double move_speed);
void	rotate(t_cube *cube, int direction, double rot_speed);
int		update_moves(t_cube *cube);

/* ----- MOUSE_MOVES.C ----- */
int		mouse_motion_handler(int x, int y, t_cube *cube);

#endif