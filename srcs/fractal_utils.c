/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   fractal_utils.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/03/17 18:20:52 by makurek        #+#    #+#                */
/*   Updated: 2025/03/17 18:34:45 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	determin_iteration(double cr, double ci, double zr, double zi)
{
	double	temp;
	int		iter;

	iter = 0;
	while (iter < MAX_ITER && (zr * zr + zi * zi) < 4.0)
	{
		temp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp;
		iter++;
	}
	return (iter);
}

int	compute_fractal_color(double real, double comp,
			t_julia_param *param)
{
	int	r;
	int	g;
	int	b;
	int	iter;
	int	color;

	if (param->mode == MANDELBROT)
		iter = determin_iteration(real, comp, 0, 0);
	else
		iter = determin_iteration(-0.7 + (param->c_real / 100),
				0.27015 + (param->c_comp / 100), real, comp);
	if (iter == MAX_ITER)
		color = 0x00ff00;
	else
	{
		r = (iter * 14) % 256;
		g = (iter * 0) % 256;
		b = (iter * 0) % 256;
		color = (r << 16) | (g << 8) | b;
	}
	return (color);
}

double	map_x_to_real(double x, double x_min, double x_max)
{
	return (x_min + (x / WIDTH) * (x_max - x_min));
}

double	map_y_to_comp(double y, double y_min, double y_max)
{
	return (y_min + (y / HEIGHT) * (y_max - y_min));
}
