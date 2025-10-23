#include "../moves/moves.h"
#include "cleanup.h"

int	close_window(t_cube *cube)
{
	free_cube(cube);
	exit(0);
}

int	key_press(int keycode, t_cube *cube)
{
	if (keycode == KEY_W)
		cube->keys.w = 1;
	if (keycode == KEY_A)
		cube->keys.a = 1;
	if (keycode == KEY_LEFT)
		cube->keys.left = 1;
	if (keycode == KEY_S)
		cube->keys.s = 1;
	if (keycode == KEY_RIGHT)
		cube->keys.right = 1;
	if (keycode == KEY_D)
		cube->keys.d = 1;
	if (keycode == KEY_ESC)
		close_window(cube);
	return (0);
}

int	key_release(int keycode, t_cube *cube)
{
	if (keycode == KEY_W)
		cube->keys.w = 0;
	if (keycode == KEY_A)
		cube->keys.a = 0;
	if (keycode == KEY_LEFT)
		cube->keys.left = 0;
	if (keycode == KEY_S)
		cube->keys.s = 0;
	if (keycode == KEY_RIGHT)
		cube->keys.right = 0;
	if (keycode == KEY_D)
		cube->keys.d = 0;
	return (0);
}
