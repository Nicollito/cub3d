#ifndef CUBE_H
# define CUBE_H

#include <stdint.h>

typedef struct image
{
	int		height;
	int		width;
	void	*mlx_ptr;
}			t_image;

typedef struct sprites
{
	t_image	wall_no;
	t_image	wall_so;
	t_image	wall_ea;
	t_image	wall_we;
	t_image	ceiling;
	t_image	floor;
}			t_sprites;

typedef struct character
{
	int	x;
	int	y;
	int	orientation;
}		t_char;

typedef struct s_config
{
	char		**map;
	char		*text_no;
	char		*text_so;
	char		*text_ea;
	char		*text_we;
	uint8_t		*floor_color[3];
	uint8_t		*ceiling_color[3];
}				t_config;

typedef struct cube
{
	void		*mlx;
	void		*mlx_window;
	t_char		character;
	t_sprites	sprites;
	t_config	config;
	char		**map;
	char		**textures;
}				t_cube;

#endif