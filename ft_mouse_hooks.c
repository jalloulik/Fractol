/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjalloul <kjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:59:03 by kjalloul          #+#    #+#             */
/*   Updated: 2018/01/15 18:03:05 by kjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			ft_mouse_zoom(int button, int x, int y, t_param *param)
{
	param->fract->cenx = param->fract->cenx + (2 * param->fract->spanx
			* (double)x / param->fract->length) - param->fract->spanx;
	param->fract->ceny = param->fract->ceny + (2 * param->fract->spany
			* (double)y / param->fract->height) - param->fract->spany;
	if (button == SCROLL_UP)
		param->fract->scale = 1.3;
	else if (button == SCROLL_DOWN)
		param->fract->scale = 0.7;
	param->fract->spanx = param->fract->spanx / param->fract->scale;
	param->fract->spany = param->fract->spany / param->fract->scale;
	param->fract->cenx = param->fract->cenx - (2 * param->fract->spanx
			* (double)x / param->fract->length) + param->fract->spanx;
	param->fract->ceny = param->fract->ceny - (2 * param->fract->spany
			* (double)y / param->fract->height) + param->fract->spany;
	ft_draw_fract(param->mlxenv, param->fract);
	mlx_put_image_to_window(param->mlxenv->mlxptr, param->mlxenv->win,
								param->mlxenv->img.ptr, 0, 0);
}

int					ft_mouse_hook(int button, int x, int y, t_param *param)
{
	param->fract->length = (double)param->mlxenv->img.length;
	param->fract->height = (double)param->mlxenv->img.height;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
		ft_mouse_zoom(button, x, y, param);
	return (button);
}

int					ft_mouse_motion(int x, int y, void *params)
{
	static int	old_x = 0;
	static int	old_y = 0;
	t_param		*param;

	param = (t_param*)params;
	if (param->fract->ftype == 2 && param->fract->transform == 1)
	{
		if (old_x < x)
			param->fract->xh += 0.001;
		if (old_x > x)
			param->fract->xh -= 0.001;
		if (old_y < y)
			param->fract->yh += 0.001;
		if (old_y > y)
			param->fract->yh -= 0.001;
		ft_draw_fract(param->mlxenv, param->fract);
		mlx_put_image_to_window(param->mlxenv->mlxptr, param->mlxenv->win,
									param->mlxenv->img.ptr, 0, 0);
		old_x = x;
		old_y = y;
	}
	return (0);
}
