#ifndef CUBE_H
# define CUBE_H

typedef struct xpm
{
	void	*image;
	int		heig
}

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

typedef struct cube
{
	void		*mlx;
	t_char		character;
	t_sprites	sprites;
}				t_cube;

/*---------------------parsing/---------------------*/

// parsing.c

void	parsing(int ac, char **av);

#endif