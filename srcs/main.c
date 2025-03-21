/* ************************************************************************** */
/*																			*/
/*														 ::::::::		   */
/*   main.c                                             :+:      :+:    :+:   */
/*													  +:+				   */
/*   By: makurek <marvin@42.fr>						+#+					*/
/*													+#+					 */
/*   Created: 2025/03/19 18:09:50 by makurek		#+#	#+#				*/
/*   Updated: 2025/03/21 16:53:31 by makurek          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "fractol.h"

static void	initialize_mlx_resources(void **mlx_ptr, void **win_ptr)
{
	*mlx_ptr = mlx_init();
	if (!(*mlx_ptr))
		exit(1);
	*win_ptr = mlx_new_window(*mlx_ptr, WIDTH, HEIGHT, "test");
	if (!(*win_ptr))
	{
		mlx_destroy_display(*mlx_ptr);
		free(*mlx_ptr);
		exit(1);
	}
}

static void	parse_julia_parameters(t_fractol *min_max, char **av)
{
	if (is_str_num(av[2]) && is_str_num(av[3]))
		init_parameters(&min_max->param, ft_atoi(av[2]), ft_atoi(av[3]), JULIA);
	else
		close_program(min_max, 1, 1);
}

int	close_window(t_fractol *min_max)
{
	close_program(min_max, 1, 1);
	return (0);
}

static void	initialize_and_render_fractal(char **av)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_fractol	min_max;

	initialize_mlx_resources(&mlx_ptr, &win_ptr);
	init_min_max(&min_max, mlx_ptr, win_ptr);
	if (!ft_strncmp(av[1], "julia", 6))
		parse_julia_parameters(&min_max, av);
	else
		min_max.param.mode = MANDELBROT;
	render_fractal(&min_max, &min_max.param);
	mlx_key_hook(win_ptr, key_hook, &min_max);
	mlx_mouse_hook(win_ptr, mouse_hook, &min_max);
	mlx_hook(win_ptr, DestroyNotify, StructureNotifyMask,
		close_window, &min_max);
	mlx_loop(mlx_ptr);
	close_program(&min_max, 1, 1);
}

int	main(int ac, char **av)
{
	if (!((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 11))
			|| (ac == 4 && !ft_strncmp(av[1], "julia", 6))))
	{
		ft_putstr_fd("Usage: \"./fractol mandelbrot\" or \
\"./fractol julia " "<value1> <value2>\"", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	initialize_and_render_fractal(av);
	return (0);
}
