#ifndef ALGO_H
# define ALGO_H

typedef enum e_side
{
	VERTICAL,
	HORIZONTAL,
}	t_side;

typedef struct wall
{
	int				height;
	int				draw_start;
	t_side			side;
	t_texture_type	texture;
}					t_wall;

typedef struct calculator
{
	double	step;
	double	ray_x;
	double	ray_y;
	double	ray_dir_x;
	double	ray_dir_y;
}			t_calc;

typedef struct algo
{
	t_char		character;
	double		*ray_base_x;
	char		**map;
	double		dist_proj;
}				t_algo;

/* ------------------algo/------------------ */

// algo.c
void	raycasting(t_color *color, t_sprites sprites, t_algo algo);

// background.c
void	print_backgound(t_color *color, t_img_data image);

// setup.c
void	get_write_value(t_algo algo, t_wall *wall, t_calc *data, int column);

#endif