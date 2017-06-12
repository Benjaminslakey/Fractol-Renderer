/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <benjaminslakey@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 00:51:51 by bslakey           #+#    #+#             */
/*   Updated: 2017/05/23 00:51:52 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int				expose_events(t_prog *f)
{
	f->dx = 0;
	f->dy = 0;
	f->zoom = 1;
	f->pause = 0;
	f->n_iter = 50;
	thread_fractol(f);
	return (EXIT_SUCCESS);
}

int				key_events(int keycode, t_prog *f)
{
	if (EXIT(keycode))
	{
		mlx_destroy_window(f->mlx, f->window);
		free(f);
		exit(EXIT_SUCCESS);
	}
	else if (MORE_ITER(keycode) || LESS_ITER(keycode))
	{
		if (MORE_ITER(keycode) && f->n_iter < 500)
			f->n_iter += 10;
		else if (LESS_ITER(keycode) && f->n_iter > 50)
			f->n_iter -= 10;
	}
	else if (TRANS_LEFT(keycode) || TRANS_RIGHT(keycode))
		f->dx += (TRANS_LEFT(keycode)) ? -5.0 : 5.0;
	else if (TRANS_UP(keycode) || TRANS_DOWN(keycode))
		f->dy += (TRANS_UP(keycode)) ? -5.0 : 5.0;
	else if (PAUSE(keycode))
		f->pause = (f->pause) ? 0 : 1;
	thread_fractol(f);
	return (EXIT_SUCCESS);
}

int				motion_events(int x, int y, t_prog *f)
{
	double		vrange[2];

	bzero_coords(&vrange);
	if (!f->pause)
	{
		vrange[1] = f->vdim[0];
		f->mouse_x = range_change(vrange, f->x_range, (double)x) - 2.0;
		vrange[1] = f->vdim[1];
		f->mouse_y = range_change(vrange, f->y_range, (double)y) - 2.0;
	}
	thread_fractol(f);
	return (EXIT_SUCCESS);
}

int				mouse_events(int code, int x, int y, t_prog *f)
{
	double		z;
	double		xr;
	double		yr;

	z = 1;
	xr = 0.0;
	yr = 0.0;
	if (ZOOM_IN(code) || ZOOM_OUT(code))
	{
		z = (ZOOM_IN(code)) ? (1.1) : (1 / 1.1);
		f->zoom *= (ZOOM_OUT(code) && f->zoom <= 1) ? 1 : z;
		xr = (f->x_range[1] - f->x_range[0]) / (WIDTH - 1);
		yr = (f->y_range[1] - f->y_range[0]) / (HEIGHT - 1);
		f->dx = (((f->x_range[0] + ((double)x + f->dx) * xr) * z)
			- f->x_range[0] - ((double)x * xr)) / xr;
		f->dy = (((f->y_range[0] + ((double)y + f->dy) * yr) * z)
			- f->y_range[0] - ((double)y * yr)) / yr;
	}
	thread_fractol(f);
	return (EXIT_SUCCESS);
}
