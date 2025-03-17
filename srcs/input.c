/* ************************************************************************** */
/*																			*/
/*														 ::::::::		   */
/*   input.c                                             :+:    :+:           */
/*													  +:+				   */
/*   By: makurek <marvin@42.fr>						+#+					*/
/*													+#+					 */
/*   Created: 2025/03/17 18:37:43 by makurek		#+#	#+#				*/
/*   Updated: 2025/03/17 18:43:43 by makurek        ########   odam.nl        */
/*																			*/
/* ************************************************************************** */

#include "fractol.h"

static void	zoom(t_fractol *min_max, double c_real,
				double c_comp, double zoom_factor)
{
	double	new_width;
	double	new_height;

	new_width = (min_max->x_max - min_max->x_min) * zoom_factor;
	new_height = (min_max->y_max - min_max->y_min) * zoom_factor;
	min_max->x_min = c_real - new_width / 2;
	min_max->x_max = c_real + new_width / 2;
	min_max->y_min = c_comp - new_height / 2;
	min_max->y_max = c_comp + new_height / 2;
}

int	mouse_hook(int button, int x, int y, t_fractol *min_max)
{
	double	c_real;
	double	c_comp;

	c_real = map_x_to_real(x, min_max->x_min, min_max->x_max);
	c_comp = map_y_to_comp(y, min_max->y_min, min_max->y_max);
	if (button == 4)
		zoom(min_max, c_real, c_comp, ZOOM_FACTOR);
	else if (button == 5)
		zoom(min_max, c_real, c_comp, 1.0 / ZOOM_FACTOR);
	else
		return (0);
	mlx_clear_window(min_max->mlx_ptr, min_max->win_ptr);
	render_fractal(min_max, &min_max->param);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	(void) param;
	if (keycode == 65307)
		exit(1);
	return (0);
}
