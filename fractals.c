/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjalloul <kjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:56:44 by kjalloul          #+#    #+#             */
/*   Updated: 2018/01/15 17:37:14 by kjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		ft_fract_julia(t_seq *e, t_param *param, t_2dpoint *p)
{
	int		i;
	double	tmp;

	e->c.r = 0.285 + param->fract->xh;
	e->c.i = 0.01 + param->fract->yh;
	e->z.r = param->fract->cenx - param->fract->spanx + ((double)p->x)
					/ param->fract->xzoom;
	e->z.i = param->fract->ceny - param->fract->spany + ((double)p->y)
					/ param->fract->yzoom;
	i = 0;
	while (SQR(e->z.r) + SQR(e->z.i) < 4 && i < param->fract->imax)
	{
		tmp = e->z.r;
		e->z.r = SQR(e->z.r) - SQR(e->z.i) + e->c.r;
		e->z.i = 2 * e->z.i * tmp + e->c.i;
		i = i + 1;
	}
	ft_fill_img(param->mlxenv->img, p->x, p->y,
					ft_color_palette(i, param->fract));
}

static void		ft_fract_mandelbrot3(t_seq *e, t_param *param, t_2dpoint *p)
{
	int		i;
	double	tmp;

	e->c.r = param->fract->cenx - param->fract->spanx + ((double)p->x)
				/ param->fract->xzoom;
	e->c.i = param->fract->ceny - param->fract->spany + ((double)p->y)
				/ param->fract->yzoom;
	e->z.r = 0;
	e->z.i = 0;
	i = 0;
	while ((CUBE(e->z.r) - 3 * e->z.r * SQR(e->z.i)) < 4
										&& i < param->fract->imax)
	{
		tmp = e->z.r;
		e->z.r = (CUBE(e->z.r) - 3 * e->z.r * SQR(e->z.i)) + e->c.r;
		e->z.i = 3 * SQR(tmp) * e->z.i - CUBE(e->z.i) + e->c.i;
		i = i + 1;
	}
	ft_fill_img(param->mlxenv->img, p->x, p->y,
			ft_color_palette(i, param->fract));
}

static void		ft_fract_mandel(t_seq *e, t_param *param, t_2dpoint *p)
{
	int		i;
	double	tmp;

	e->c.r = param->fract->cenx - param->fract->spanx + ((double)p->x)
				/ param->fract->xzoom;
	e->c.i = param->fract->ceny - param->fract->spany + ((double)p->y)
				/ param->fract->yzoom;
	e->z.r = 0;
	e->z.i = 0;
	i = -1;
	while (SQR(e->z.r) + SQR(e->z.i) < 4 && ++i < param->fract->imax)
	{
		tmp = e->z.r;
		e->z.r = SQR(e->z.r) - SQR(e->z.i) + e->c.r;
		e->z.i = 2 * e->z.i * tmp + e->c.i;
	}
	ft_fill_img(param->mlxenv->img, p->x, p->y,
			ft_color_palette(i, param->fract));
}

static void		*ft_fract_thrd(void *paramtmp)
{
	t_2dpoint	p;
	t_seq		e;
	t_param		*param;

	param = (t_param*)paramtmp;
	p.x = param->i;
	while (p.x < (param->i + param->mlxenv->img.length / NTHREAD))
	{
		p.y = -1;
		while (++p.y < param->mlxenv->img.height)
		{
			if (param->fract->ftype == 1)
				ft_fract_mandel(&e, param, &p);
			else if (param->fract->ftype == 2)
				ft_fract_julia(&e, param, &p);
			else if (param->fract->ftype == 3)
				ft_fract_mandelbrot3(&e, param, &p);
		}
		p.x++;
	}
	return (NULL);
}

void			ft_fract_thread_init(t_winenv *mlxenv, t_fract *fract)
{
	t_param		param[NTHREAD];
	pthread_t	tab[NTHREAD];
	int			parts;
	int			t;

	t = -1;
	parts = 0;
	while (++t < NTHREAD)
	{
		param[t].fract = fract;
		param[t].mlxenv = mlxenv;
		param[t].i = parts;
		parts = parts + mlxenv->img.length / (NTHREAD);
	}
	fract->xzoom = ((double)mlxenv->img.length / 2 / (fract->spanx));
	fract->yzoom = ((double)mlxenv->img.height / 2 / (fract->spany));
	t = -1;
	while (++t < NTHREAD)
		if (pthread_create(&(tab[t]), NULL, ft_fract_thrd, (void*)&(param[t])))
			ft_error(TERROR);
	t = -1;
	while (++t < NTHREAD)
		if (pthread_join(tab[t], NULL))
			ft_error(TERROR);
}
