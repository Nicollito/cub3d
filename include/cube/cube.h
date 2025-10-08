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

typedef struct map_data
{
	char	**map;
	char	*textures[4];
	uint8_t *floor[3];
	uint8_t *ceiling[3];
}			t_map_data;

typedef struct cube
{
	void		*mlx;
	t_char		character;
	t_sprites	sprites;
	t_map_data	map_data;
	char		**map;
	char		**textures;
}				t_cube;

#endif