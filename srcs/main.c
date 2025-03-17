/* ************************************************************************** */
/*																			*/
/*														 ::::::::		   */
/*   main.c                                              :+:    :+:           */
/*													  +:+				   */
/*   By: makurek <marvin@42.fr>						+#+					*/
/*													+#+					 */
/*   Created: 2025/02/26 16:25:32 by makurek		#+#	#+#				*/
/*   Updated: 2025/03/17 19:10:39 by makurek        ########   odam.nl        */
/*																			*/
/* ************************************************************************** */

#include "fractol.h"

static void	init_min_max(t_fractol *min_max, void *mlx_ptr, void *win_ptr)
{
	min_max->x_min = -2;
	min_max->x_max = 1;
	min_max->y_min = -1.5;
	min_max->y_max = 1.5;
	min_max->mlx_ptr = mlx_ptr;
	min_max->win_ptr = win_ptr;
}

static void	init_parameters(t_julia_param *param,
		int real, int comp, t_var mode)
{
	param->c_real = real;
	param->c_comp = comp;
	param->mode = mode;
}

static int	is_str_num(const char *str)
{
	int	i;
	int	has_sign;

	if (!str)
		return (0);
	i = 0;
	has_sign = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		has_sign = 1;
		i++;
	}
	while (str[i])
	{
		if (!is_num(str[i]))
			return (0);
		i++;
	}
	if (has_sign && i == 1)
		return (0);
	return (1);
}

static void	initialize_and_render_fractal(char **av)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_fractol	min_max;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		exit(1);
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "test");
	init_min_max(&min_max, mlx_ptr, win_ptr);
	if (!ft_strncmp(av[1], "julia", 5))
	{
		if (is_str_num(av[2]) && is_str_num(av[3]))
			init_parameters(&min_max.param, ft_atoi(av[2]),
				ft_atoi(av[3]), JULIA);
		else
			exit(1);
	}
	else
		min_max.param.mode = MANDELBROT;
	render_fractal(&min_max, &min_max.param);
	mlx_key_hook(win_ptr, key_hook, &min_max);
	mlx_mouse_hook(win_ptr, mouse_hook, &min_max);
	mlx_loop(mlx_ptr);
}

int	main(int ac, char **av)
{
	if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
		|| (ac == 4 && !ft_strncmp(av[1], "julia", 5)))
	{
		initialize_and_render_fractal(av);
		return (0);
	}
	else
	{
		ft_putstr_fd("Usage: \"./fractol mandelbrot\" or \
\"./fractol julia " "<value1> <value2>\"", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
