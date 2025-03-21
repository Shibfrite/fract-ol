/* ************************************************************************** */
/*																			*/
/*														 ::::::::		   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*													  +:+				   */
/*   By: makurek <marvin@42.fr>						+#+					*/
/*													+#+					 */
/*   Created: 2025/03/17 18:44:26 by makurek		#+#	#+#				*/
/*   Updated: 2025/03/21 16:54:04 by makurek          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h> //debug
# include <stdlib.h> //malloc free
# include <unistd.h> //write
# include <X11/X.h> //cross closes the program
# include "mlx.h"
# include "libft.h"

# define ZOOM_FACTOR 0.6 
# define MAX_ITER 1000
# define HEIGHT 500
# define WIDTH 500 

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
int		key_hook(int keycode, t_fractol *min_max);

//main_support.c
void	init_min_max(t_fractol *min_max, void *mlx_ptr, void *win_ptr);
void	init_parameters(t_julia_param *param,
			int real, int comp, t_var mode);
int		is_str_num(const char *str);
void	close_program(t_fractol *min_max,
			int destroy_window, int destroy_display);

#endif
