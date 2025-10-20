#ifndef MOVES_H
# define MOVES_H

#include "cube.h"
#include <stdlib.h>

int		close_window(t_cube *cube);
void	move_character(t_cube *cube, int forward, double move_speed);
int		handle_keypress(int keycode, t_cube *cube);

#endif