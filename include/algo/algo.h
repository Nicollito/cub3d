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

#endif