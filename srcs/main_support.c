/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   main_support.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/03/19 18:09:31 by makurek        #+#    #+#                */
/*   Updated: 2025/03/19 19:14:06 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_min_max(t_fractol *min_max, void *mlx_ptr, void *win_ptr)
{
	double	original_y_range;
	double	x_center;
	double	new_x_range;

	original_y_range = 3.0;
	x_center = -0.5;
	new_x_range = (WIDTH / HEIGHT) * original_y_range;
	min_max->x_min = x_center - (new_x_range / 2);
	min_max->x_max = x_center + (new_x_range / 2);
	min_max->y_min = -original_y_range / 2;
	min_max->y_max = original_y_range / 2;
	min_max->mlx_ptr = mlx_ptr;
	min_max->win_ptr = win_ptr;
}

void	init_parameters(t_julia_param *param,
		int real, int comp, t_var mode)
{
	param->c_real = real;
	param->c_comp = comp;
	param->mode = mode;
}

void	close_program(t_fractol *min_max,
		int destroy_window, int destroy_display)
{
	if (min_max->win_ptr && destroy_window)
		mlx_destroy_window(min_max->mlx_ptr, min_max->win_ptr);
	if (min_max->mlx_ptr && destroy_display)
	{
		mlx_destroy_display(min_max->mlx_ptr);
		free(min_max->mlx_ptr);
	}
	exit(0);
}

int	is_str_num(const char *str)
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
