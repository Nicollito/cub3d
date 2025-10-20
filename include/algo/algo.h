#ifndef ALGO_H
# define ALGO_H

typedef enum e_side
{
	VERTICAL,
	HORAZONTAL,
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

/* ------------------algo/------------------ */

// algo.c
void	raycasting(t_cube *cube);

// background.c
void	print_backgound(t_color *color, t_img_data image);

// setup.c
void	get_write_value(t_cube *cube, t_wall *wall, t_calc *data, int column);

#endif