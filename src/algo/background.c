#include "cube.h"
#include "algo.h"

/**
 * @brief Sets a pixel in an image to a specified color.
 *
 * This function converts a color structure (RGB) into a 24-bit integer value
 * according to the image's endian format, then writes it into the image memory
 * at the given offset.
 *
 * @param color Pointer to the color structure containing RGB values.
 * @param image The image data structure where the pixel will be set.
 * @param offset The pixel index in the image memory array.
 */
static void	color_pixel(t_color *color, t_img_data image, int offset)
{
	int	rgba;

	if (image.endian == 1)
		rgba = (color->rgb[0] << 16) | (color->rgb[1] << 8) | color->rgb[2];
	else
		rgba = (color->rgb[2] << 16) | (color->rgb[1] << 8) | color->rgb[0];
	((int *)image.mem)[offset] = rgba;
}

void	fill_background(t_color *color, t_img_data image)
{
	int				x;
	int				y;
	double			offset;
	t_color_type	type;

	y = 0;
	type = CEILING;
	while (y <= WINDOW_HEIGHT)
	{
		x = 0;
		while (x <= WINDOW_WIDTH)
		{
			offset = (y * image.line_length + x
					* (image.bits_per_pixel / 8)) * 0.25;
			color_pixel(&color[type], image, (int)offset);
			++x;
		}
		if (type != FLOOR && y > WINDOW_HEIGHT / 2)
			type = FLOOR;
		++y;
	}
}
