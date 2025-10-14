#ifndef CUBE_H
# define CUBE_H

# include <stdint.h>
# include <stdbool.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define PI 3.1415926535
# define FOV 60

typedef enum e_texture_type
{
	INVALID_TEXTURE = -1,
	TEXT_NO,
	TEXT_EA,
	TEXT_SO,
	TEXT_WE
}	t_texture_type;

typedef enum e_color_type
{
	INVALID_COLOR = -1,
	FLOOR,
	CEILING
}	t_color_type;

typedef struct image
{
	int		height;
	int		width;
	void	*mlx_ptr;
}			t_image;

typedef struct sprites
{
	t_image	wall[4];
	t_image	background;
}			t_sprites;

typedef struct character
{
	double	x;
	double	y;
	double	orientation;
	double	ray[WINDOW_WIDTH];
}			t_char;

typedef struct s_color
{
	uint8_t	rgb[3];
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
	void		*mlx_window;
	t_char		character;
	t_sprites	sprites;
	t_config	config;
	char		**map;
	char		**textures;
}				t_cube;

#endif