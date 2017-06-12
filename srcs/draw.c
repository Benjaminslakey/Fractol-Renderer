/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <benjaminslakey@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 00:50:35 by bslakey           #+#    #+#             */
/*   Updated: 2017/05/23 00:50:42 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			draw_pixel(t_prog *f, int x, int y, int rgb)
{
	int			i;

	i = 0;
	if ((x < WIDTH && x > 0) && (y < HEIGHT && y > 0))
	{
		i = (x * 4) + (y * f->lsize);
		(f->map)[i] = rgb;
		(f->map)[++i] = rgb >> 8;
		(f->map)[++i] = rgb >> 16;
	}
}

int				get_color(t_prog *f, int iterations)
{
	int			color;

	color = 0xFFFFFF * iterations / f->n_iter;
	return (color);
}

void			*draw(void *thread)
{
	t_thread	*t;
	double		x;
	double		y;
	double		c[2];
	int			iters;

	t = (t_thread*)thread;
	y = t->y1;
	iters = 0;
	bzero_coords(&c);
	while (++y <= t->y2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			set_ranges(t->f);
			c[0] = scale_x(t->f, x);
			c[1] = scale_y(t->f, y);
			iters = (t->f->setf)(t->f, c[0], c[1]);
			draw_pixel(t->f, lround(x), lround(y), get_color(t->f, iters));
		}
	}
	return (NULL);
}
