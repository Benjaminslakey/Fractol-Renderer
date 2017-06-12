/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <benjaminslakey@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 00:52:13 by bslakey           #+#    #+#             */
/*   Updated: 2017/05/23 00:52:14 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int				burning_ship(t_prog *f, double x0, double y0)
{
	int			i;
	double		x[2];
	double		y[2];

	i = -1;
	bzero_coords(&x);
	bzero_coords(&y);
	while (++i < f->n_iter && (x[0] * x[0] + y[0] * y[0]) < 10)
	{
		x[0] = (x[1] * x[1]) - (y[1] * y[1]) - x0;
		y[0] = 2 * fabs(x[1] * y[1]) - y0;
		x[1] = x[0];
		y[1] = y[0];
	}
	return (i);
}

int				julia_set(t_prog *f, double x0, double y0)
{
	int			i;
	double		x[2];
	double		y[2];

	i = -1;
	bzero_coords(&x);
	bzero_coords(&y);
	x[0] = x0;
	y[0] = y0;
	while (++i < f->n_iter && (x[0] * x[0] + y[0] * y[0]) < 4.0)
	{
		x[1] = (x[0] * x[0]) - (y[0] * y[0]) + f->mouse_x;
		y[1] = (2 * x[0] * y[0]) + f->mouse_y;
		if (x[0] == x[1] && y[0] == y[1])
			return (f->n_iter);
		x[0] = x[1];
		y[0] = y[1];
	}
	return (i);
}

int				mandelbrot_set(t_prog *f, double x0, double y0)
{
	int			i;
	double		x[2];
	double		y[2];

	i = -1;
	bzero_coords(&x);
	bzero_coords(&y);
	while (++i < f->n_iter && ((x[0] * x[0]) + (y[0] * y[0])) < 4.0)
	{
		x[1] = (x[0] * x[0]) - (y[0] * y[0]) + x0;
		y[1] = 2 * x[0] * y[0] + y0;
		if (x[0] == x[1] && y[0] == y[1])
			return (f->n_iter);
		x[0] = x[1];
		y[0] = y[1];
	}
	return (i);
}
