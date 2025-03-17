/* ************************************************************************** */
/*																			*/
/*														 ::::::::		   */
/*   fractol.h                                           :+:    :+:           */
/*													  +:+				   */
/*   By: makurek <marvin@42.fr>						+#+					*/
/*													+#+					 */
/*   Created: 2025/03/17 18:44:26 by makurek		#+#	#+#				*/
/*   Updated: 2025/03/17 19:08:57 by makurek        ########   odam.nl        */
/*																			*/
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h> //debug
# include <stdlib.h> //malloc free
# include <unistd.h> //write
# include "mlx.h"
# include "libft.h"

# define ZOOM_FACTOR 0.6 
# define MAX_ITER 1000
# define HEIGHT 1600
# define WIDTH 1400 

typedef enum e_var {
	MANDELBROT,
	JULIA
}	t_var;

typedef struct s_julia_param
{
	double	c_real;
	double	c_comp;
	t_var	mode;
}	t_julia_param;

typedef struct s_fractol
{
	t_julia_param	param;
	double			x_min;
	double			x_max;
	double			y_min;
	double			y_max;
	void			*mlx_ptr;
	void			*win_ptr;
}	t_fractol;

//fractal_render.c
void	render_fractal(t_fractol *min_max, t_julia_param *param);

//fractal_utils.c
int		compute_fractal_color(double real, double comp, t_julia_param *param);
double	map_x_to_real(double x, double x_min, double x_max);
double	map_y_to_comp(double y, double y_min, double y_max);

//input.c
int		mouse_hook(int button, int x, int y, t_fractol *min_max);
int		key_hook(int keycode, void *param);

#endif
