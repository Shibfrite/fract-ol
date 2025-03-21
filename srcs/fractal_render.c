/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   fractal_render.c                                    :+:    :+:           */
/*													+:+ +:+		 +:+	 */
/*   By: makurek <marvin@42.fr>					 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/13 18:48:35 by makurek		   #+#	#+#			 */
/*   Updated: 2025/03/21 13:59:39 by makurek        ########   odam.nl        */
/*																			*/
/* ************************************************************************** */

#include "fractol.h"

static char	*get_image_data(void *img)
{
	int	bpp;
	int	line_length;
	int	endian;

	return (mlx_get_data_addr(img, &bpp, &line_length, &endian));
}

static int	compute_pixel_color(int x, int y,
		t_fractol *fractol, t_julia_param *param)
{
	double	real;
	double	comp;

	real = map_x_to_real(x, fractol->x_min, fractol->x_max);
	comp = map_y_to_comp(y, fractol->y_min, fractol->y_max);
	return (compute_fractal_color(real, comp, param));
}

static void	render_pixels(char *data, t_fractol *fractol, t_julia_param *param)
{
	unsigned int	*pixels;
	int				x;
	int				y;

	pixels = (unsigned int *)data;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixels[y * WIDTH + x] = compute_pixel_color(x, y, fractol, param);
			x++;
		}
		y++;
	}
}

void	render_fractal(t_fractol *fractol, t_julia_param *param)
{
	void	*img;
	char	*data;

	img = mlx_new_image(fractol->mlx_ptr, WIDTH, HEIGHT);
	if (!img)
		close_program(fractol, 1, 1);
	data = get_image_data(img);
	render_pixels(data, fractol, param);
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, img, 0, 0);
	mlx_destroy_image(fractol->mlx_ptr, img);
}
