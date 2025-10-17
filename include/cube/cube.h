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

typedef enum e_image_layer
{
	BACKGROUND,
	FOREGROUND,
}	t_layer;

typedef struct image_data
{
	char	*mem;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img_data;

typedef struct image
{
	int			height;
	int			width;
	void		*mlx_ptr;
	t_img_data	data;
}				t_image;

typedef struct sprites
{
	t_image	text_wall[4];
	t_image	frame;
}			t_sprites;

typedef struct character
{
	double	x;
	double	y;
	double	orientation;
}			t_char;

typedef struct s_color
{
	uint8_t	rgb[3];
	bool	is_set;
}			t_color;

typedef struct s_config
{
	char		*textures[4];
	t_color		color[2];
}				t_config;

typedef struct cube
{
	void		*mlx;
	void		*mlx_window;
	t_char		character;
	t_sprites	sprites;
	t_config	config;
	int			y_max;
	int			x_max;
	char		**map;
	char		**textures;
	double		dist_proj;
	double		fov;
}				t_cube;

void	raycasting(t_cube *cube);

#endif