/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:21 by nimadela          #+#    #+#             */
/*   Updated: 2025/11/04 16:18:07 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdint.h>
# include <stdbool.h>

# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 540
# define PI 3.14159265358979323846
# define FOV 60
# define NB_TEXTURES 4
# define RAY_BASE_Y -1

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_ESC 65307
/*
# define KEY_W 122
# define KEY_A 113
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_ESC 65307
*/
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

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}		t_keys;

typedef struct s_minimap
{
	t_image image;
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;
	float	tile_size;
	float	radius;
}			t_minimap;

typedef struct cube
{
	void		*mlx;
	void		*mlx_window;
	t_char		character;
	t_sprites	sprites;
	t_config	config;
	t_minimap	minimap;
	int			y_max;
	int			x_max;
	char		**map;
	char		**textures;
	double		dist_proj;
	double		fov;
	t_keys		keys;
	int			fd_file;
	double		ray_base_x[WINDOW_WIDTH];
}				t_cube;

/**
 * @brief Updates the game state and renders a frame to the window.
 *
 * This function updates the character movement, performs raycasting to
 * generate the 3D scene in the frame buffer, and then displays the frame
 * in the MiniLibX window. It also prints the frames per second to the console.
 *
 * @param cube Pointer to the main cube structure containing all game data.
 * @return Always returns 0.
 */
int	render_frame(t_cube *cube);

#endif