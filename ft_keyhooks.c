/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjalloul <kjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 08:36:44 by kjalloul          #+#    #+#             */
/*   Updated: 2018/01/16 12:04:25 by kjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int			ft_key_hook_transform(int keycode, t_param *param)
{
	if (keycode == UP_KEY)
	{
		if (param->fract->ftype == 2)
		{
			param->fract->xh = param->fract->xh + 0.001;
			ft_draw_fract(param->mlxenv, param->fract);
			mlx_put_image_to_window(param->mlxenv->mlxptr,
							param->mlxenv->win, param->mlxenv->img.ptr, 0, 0);
		}
	}
	else if (keycode == DOWN_KEY)
	{
		if (param->fract->ftype == 2)
		{
			param->fract->xh = param->fract->xh - 0.001;
			ft_draw_fract(param->mlxenv, param->fract);
			mlx_put_image_to_window(param->mlxenv->mlxptr,
				param->mlxenv->win, param->mlxenv->img.ptr, 0, 0);
		}
	}
	return (keycode);
}

static int			ft_key_hook_exit(int keycode)
{
	if (keycode == ESC_KEY)
		exit(0);
	return (keycode);
}

static void			ft_swap_colors(t_param *param)
{
	if (param->fract->palette == 2)
		param->fract->palette = 0;
	else
		param->fract->palette++;
	ft_draw_fract(param->mlxenv, param->fract);
	mlx_put_image_to_window(param->mlxenv->mlxptr,
							param->mlxenv->win, param->mlxenv->img.ptr, 0, 0);
}

static void			ft_move_key(int keycode, t_param *param)
{
	if (keycode == LEFTAWSD_KEY)
		param->fract->cenx = param->fract->cenx + 5 / param->fract->xzoom;
	if (keycode == RIGHTAWSD_KEY)
		param->fract->cenx = param->fract->cenx - 5 / param->fract->xzoom;
	if (keycode == UPAWSD_KEY)
		param->fract->ceny = param->fract->ceny + 5 / param->fract->yzoom;
	if (keycode == DOWNAWSD_KEY)
		param->fract->ceny = param->fract->ceny - 5 / param->fract->yzoom;
	ft_draw_fract(param->mlxenv, param->fract);
	mlx_put_image_to_window(param->mlxenv->mlxptr,
							param->mlxenv->win, param->mlxenv->img.ptr, 0, 0);
}

int					ft_keyhook(int keycode, void *param)
{
	if (keycode == ESC_KEY)
		ft_key_hook_exit(keycode);
	else if (keycode == UP_KEY || keycode == DOWN_KEY)
		ft_key_hook_transform(keycode, param);
	else if (keycode == SPACE_KEY)
		ft_swap_colors(param);
	else if (keycode == MINUS_KEY || keycode == PLUS_KEY)
		ft_change_max_iter(keycode, param);
	else if (keycode == R_KEY)
		ft_reset_key(param);
	else if (keycode == ONE_KEY || keycode == TWO_KEY || keycode == THREE_KEY)
		ft_change_fract(keycode, param);
	else if (keycode == T_KEY)
		ft_transform_julia(param);
	else if (keycode == LEFTAWSD_KEY || keycode == RIGHTAWSD_KEY ||
						keycode == UPAWSD_KEY || keycode == DOWNAWSD_KEY)
		ft_move_key(keycode, param);
	return (keycode);
}
