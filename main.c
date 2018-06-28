/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjalloul <kjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 07:41:50 by kjalloul          #+#    #+#             */
/*   Updated: 2018/01/16 13:51:21 by kjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_color_palette(int i, t_fract *fract)
{
	if (fract->palette == 0)
		return (BLUE * i / 255);
	else if (fract->palette == 1)
		return (RED * i / 254);
	else if (fract->palette == 2)
		return (GREEN * i / fract->imax);
	else
		return (0);
}

void	ft_draw_fract(t_winenv *mlxenv, t_fract *fract)
{
	mlx_clear_window(mlxenv->mlxptr, mlxenv->win);
	ft_fract_thread_init(mlxenv, fract);
}

void	ft_reset_type(t_fract *fract)
{
	fract->xh = 0;
	fract->yh = 0;
	if (fract->ftype == 1)
	{
		fract->xmin = -2.1;
		fract->xmax = 0.6;
		fract->ymin = -1.2;
		fract->ymax = 1.2;
	}
	else if (fract->ftype == 2 || fract->ftype == 3)
	{
		fract->xmin = -1.2;
		fract->xmax = 1.2;
		fract->ymin = -1.2;
		fract->ymax = 1.2;
	}
	fract->cenx = (fract->xmin + fract->xmax) / 2;
	fract->spanx = fract->xmax - fract->xmin;
	fract->ceny = (fract->ymin + fract->ymax) / 2;
	fract->spany = fract->ymax - fract->ymin;
	fract->imax = 200;
}

void	ft_fract_start(int type)
{
	t_winenv	mlxenv;
	t_fract		fract;
	t_param		param;

	if (type < 1 || type > 3)
		ft_error("Usage : ./fractol [1-3]\n1 Manderlbrot\n2 Julia\n3 Multi3");
	ft_usage_manual();
	fract.ftype = type;
	ft_reset_type(&fract);
	fract.scale = 1;
	fract.palette = 0;
	fract.imax = 200;
	fract.transform = 0;
	param.mlxenv = &mlxenv;
	param.fract = &fract;
	ft_mlx_init(&mlxenv);
	ft_create_window(&mlxenv, 900, 900, "fractol");
	ft_create_img(&mlxenv, 900, 900);
	ft_draw_fract(&mlxenv, &fract);
	mlx_put_image_to_window(mlxenv.mlxptr, mlxenv.win, mlxenv.img.ptr, 0, 0);
	mlx_key_hook(mlxenv.win, &ft_keyhook, &param);
	mlx_mouse_hook(mlxenv.win, &ft_mouse_hook, &param);
	mlx_hook(mlxenv.win, 6, 1L << 6, &ft_mouse_motion, &param);
	mlx_loop(mlxenv.mlxptr);
}

int		main(int ac, char **av)
{
	if (ac != 2)
		ft_error("Usage : ./fractol [1-3]\n1 Manderlbrot\n2 Julia\n3 Multi3");
	if (ft_strequ(av[1], "1") == 1 || ft_strequ(av[1], "2") == 1 ||
											ft_strequ(av[1], "3") == 1)
		ft_fract_start(ft_atoi(av[1]));
	else
		ft_error("Usage : ./fractol [1-3]\n1 Manderlbrot\n2 Julia\n3 Multi3");
	return (0);
}
