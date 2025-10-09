#ifndef INIT_H
# define INIT_H

typedef struct color
{
	unsigned char	alpha;
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
}					t_color;

/*---------------------init/---------------------*/

int	init_mlx(t_cube *game);

#endif