#ifndef INIT_H
# define INIT_H

typedef struct image_data
{
	char	*mem;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img_data;

/*---------------------init/---------------------*/

int	init_mlx(t_cube *game);

#endif