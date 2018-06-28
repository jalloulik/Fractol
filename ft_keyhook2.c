/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjalloul <kjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 18:06:11 by kjalloul          #+#    #+#             */
/*   Updated: 2018/01/16 11:40:25 by kjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_change_max_iter(int keycode, t_param *param)
{
	if (keycode == MINUS_KEY && param->fract->imax > 50)
	{
		param->fract->imax = param->fract->imax / 1.5;
		ft_draw_fract(param->mlxenv, param->fract);
		mlx_put_image_to_window(param->mlxenv->mlxptr, param->mlxenv->win,
									param->mlxenv->img.ptr, 0, 0);
	}
	else if (keycode == PLUS_KEY && param->fract->imax < 3000)
	{
		param->fract->imax = param->fract->imax * 1.5;
		ft_draw_fract(param->mlxenv, param->fract);
		mlx_put_image_to_window(param->mlxenv->mlxptr, param->mlxenv->win,
									param->mlxenv->img.ptr, 0, 0);
	}
}

void			ft_reset_key(t_param *param)
{
	ft_reset_type(param->fract);
	ft_draw_fract(param->mlxenv, param->fract);
	mlx_put_image_to_window(param->mlxenv->mlxptr, param->mlxenv->win,
								param->mlxenv->img.ptr, 0, 0);
}

void			ft_change_fract(int keycode, t_param *param)
{
	if (keycode == ONE_KEY && param->fract->ftype != 1)
		param->fract->ftype = 1;
	else if (keycode == TWO_KEY && param->fract->ftype != 2)
		param->fract->ftype = 2;
	else if (keycode == THREE_KEY && param->fract->ftype != 3)
		param->fract->ftype = 3;
	else
		return ;
	ft_reset_type(param->fract);
	ft_draw_fract(param->mlxenv, param->fract);
	mlx_put_image_to_window(param->mlxenv->mlxptr, param->mlxenv->win,
								param->mlxenv->img.ptr, 0, 0);
}

void			ft_transform_julia(t_param *param)
{
	if (param->fract->transform == 0)
		param->fract->transform = 1;
	else
		param->fract->transform = 0;
}
