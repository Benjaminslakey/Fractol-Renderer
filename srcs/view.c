/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <benjaminslakey@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 00:51:44 by bslakey           #+#    #+#             */
/*   Updated: 2017/05/23 00:51:46 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			set_ranges(t_prog *f)
{
	double		inter;

	inter = 1 / f->zoom;
	if (f->type == 1)
	{
		(f->x_range)[0] = 0 * inter;
		(f->x_range)[1] = 4 * inter;
		(f->y_range)[0] = 0 * inter;
		(f->y_range)[1] = 4 * inter;
	}
	else if (f->type == 2)
	{
		(f->x_range)[0] = 0 * inter;
		(f->x_range)[1] = 3.5 * inter;
		(f->y_range)[0] = 0 * inter;
		(f->y_range)[1] = 2 * inter;
	}
	else if (f->type == 3)
	{
		(f->x_range)[0] = 0 * inter;
		(f->x_range)[1] = 4 * inter;
		(f->y_range)[0] = 0 * inter;
		(f->y_range)[1] = 4 * inter;
	}
}

double			scale_x(t_prog *f, double x)
{
	double		dx0;
	double		vrange[2];
	double		scaled_dx;
	double		scaled_x;

	dx0 = 0;
	if (f->type == 1)
		dx0 = 2;
	else if (f->type == 2)
		dx0 = 2;
	else if (f->type == 3)
		dx0 = 1.5;
	vrange[0] = 0;
	vrange[1] = f->vdim[0];
	scaled_x = range_change(vrange, f->x_range, x);
	scaled_dx = range_change(vrange, f->x_range, f->dx) - dx0;
	return (scaled_x + scaled_dx);
}

double			scale_y(t_prog *f, double y)
{
	double		dy0;
	double		vrange[2];
	double		scaled_dy;
	double		scaled_y;

	dy0 = 0;
	if (f->type == 1)
		dy0 = 2;
	else if (f->type == 2)
		dy0 = 1;
	else if (f->type == 3)
		dy0 = 2;
	vrange[0] = 0;
	vrange[1] = f->vdim[1];
	scaled_y = range_change(vrange, f->y_range, y);
	scaled_dy = range_change(vrange, f->y_range, f->dy) - dy0;
	return (scaled_y + scaled_dy);
}
