#include "cube.h"
#include "algo.h"

static void	color_pixel(t_color *color, t_img_data image, int offset)
{
	if (image.endian == 1)
	{
		image.mem[offset + 1] = color->rgb[0];
		image.mem[offset + 2] = color->rgb[1];
		image.mem[offset + 3] = color->rgb[2];
	}
	else
	{
		image.mem[offset + 0] = color->rgb[2];
		image.mem[offset + 1] = color->rgb[1];
		image.mem[offset + 2] = color->rgb[0];
	}
}

void	print_backgound(t_color *color, t_img_data image)
{
	int				x;
	int				y;
	int				offset;
	t_color_type	type;

	y = 0;
	type = CEILING;
	while (y <= WINDOW_HEIGHT)
	{
		x = 0;
		while (x <= WINDOW_WIDTH)
		{
			offset = y * image.line_length + x
				* (image.bits_per_pixel / 8);
			color_pixel(&color[type], image, offset);
			++x;
		}
		if (y > WINDOW_HEIGHT / 2)
			type = FLOOR;
		++y;
	}
}
