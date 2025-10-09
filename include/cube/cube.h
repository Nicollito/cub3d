#ifndef CUBE_H
# define CUBE_H

#include <stdint.h>

typedef struct allocation
{
	void			*content;
	struct alloc	*next;
}					t_alloc;

typedef struct sprites
{
	void	*wall_no;
	void	*wall_so;
	void	*wall_ea;
	void	*wall_we;
	void	*ceiling;
	void	*floor;
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
	t_char		character;
	t_sprites	sprites;
	t_config	config;
	char		**map;
	char		**textures;
}				t_cube;

#endif