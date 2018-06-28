/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjalloul <kjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 18:13:22 by kjalloul          #+#    #+#             */
/*   Updated: 2018/01/15 18:40:54 by kjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_usage_manual(void)
{
	ft_putendl("+ - to change Max iterations");
	ft_putendl("1 - Manderlbrot\n2 - Julia\n3 - Multibro3");
	ft_putendl("T - Switch Julia transformation on and off");
	ft_putendl("AWSD to move");
	ft_putendl("UP and DOWN directions to modify Julia\nR to reset");
	ft_putendl("Mouse scroll to zoom in and out");
	ft_putendl("Space to swap color palette\nESC to exit");
}
