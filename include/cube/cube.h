#ifndef CUBE_H
# define CUBE_H

#include <stdint.h>
#include <stdbool.h>

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

typedef struct s_color
{
	uint8_t rgb[3];
	bool	is_set;
}			t_color;

typedef struct s_config
{
	char		**map;
	char		*textures[4];
	t_color		color[2];
}				t_config;

typedef struct s_map
{
	char	**map;
}			t_map;


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