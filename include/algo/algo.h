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
	int			y_max;
	int			x_max;
}				t_algo;

/* ------------------algo/------------------ */

// algo.c

/**
 * @brief Performs the main raycasting loop to render the 3D scene.
 *
 * This function iterates over each vertical screen column, casts a ray from
 * the player's position, computes wall intersections, determines wall height
 * and texture, and draws the corresponding column in the frame buffer. The
 * background (ceiling and floor) is filled before rendering walls.
 *
 * @param color Array of colors for ceiling and floor.
 * @param sprites Structure containing textures and the frame buffer.
 * @param algo Structure containing the map, character, projection distance,
 * and precomputed ray base offsets.
 */
void	raycasting(t_color *color, t_sprites sprites, t_algo algo);

// background.c

/**
 * @brief Fills the entire frame with a background color for ceiling and floor.
 *
 * This function iterates over all pixels of the frame. The top half of the
 * screen is filled with the ceiling color and the bottom half with the floor
 * color. It uses `color_pixel` to set each individual pixel.
 *
 * @param color Array of colors, where CEILING and FLOOR indices define the
 * background colors.
 * @param image The image data structure to be filled with background colors.
 */
void	fill_background(t_color *color, t_img_data image);

// setup.c

/**
 * @brief Calculates ray intersection and wall projection for a screen column.
 *
 * This function initializes ray data, casts the ray to find the wall hit,
 * computes the wall's projected height, and determines the starting Y
 * position to draw the wall column on screen.
 *
 * @param algo Structure containing the map, character, projection distance,
 * and precomputed ray base offsets.
 * @param wall Pointer to the wall structure to update height, draw start,
 * side, and texture.
 * @param data Pointer to the calculation structure for ray traversal.
 * @param column Screen column index where the wall slice will be rendered.
 */
void	get_write_value(t_algo algo, t_wall *wall, t_calc *data, int column);

#endif