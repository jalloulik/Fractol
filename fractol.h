/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjalloul <kjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 07:42:42 by kjalloul          #+#    #+#             */
/*   Updated: 2018/01/15 18:14:15 by kjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libgraph.h"
# include <pthread.h>

# define NTHREAD 900

typedef struct	s_cplx
{
	double r;
	double i;
}				t_cplx;

typedef struct	s_seq
{
	t_cplx z;
	t_cplx c;
}				t_seq;

typedef struct	s_fract
{
	int		ftype;
	int		palette;
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
	double	imax;
	double	xzoom;
	double	yzoom;
	double	xh;
	double	yh;
	double	scale;
	double	spanx;
	double	spany;
	double	cenx;
	double	ceny;
	double	length;
	double	height;
	int		transform;
}				t_fract;

typedef struct	s_2dpoint
{
	int x;
	int y;
}				t_2dpoint;

typedef struct	s_param
{
	t_winenv	*mlxenv;
	t_fract		*fract;
	int			(*f)(int, t_fract*);
	int			i;
}				t_param;

int				ft_keyhook(int keycode, void *param);
int				ft_mouse_hook(int button, int x, int y, t_param *param);
void			ft_fract_thread_init(t_winenv *mlxenv, t_fract *fract);
void			ft_draw_fract(t_winenv *mlxenv, t_fract *fract);
void			ft_reset_type(t_fract *fract);
int				ft_mouse_motion(int x, int y, void *param);
void			ft_fract_thread_init(t_winenv *mlxenv, t_fract *fract);
int				ft_color_palette(int i, t_fract *fract);
void			ft_change_max_iter(int keycode, t_param *param);
void			ft_reset_key(t_param *param);
void			ft_change_fract(int keycode, t_param *param);
void			ft_transform_julia(t_param *param);
void			ft_usage_manual(void);

#endif
