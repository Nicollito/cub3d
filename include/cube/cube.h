#ifndef CUBE_H
# define CUBE_H

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

typedef struct cube
{
	void		*mlx;
	void		*mlx_window;
	t_char		character;
	t_sprites	sprites;
}				t_cube;

#endif