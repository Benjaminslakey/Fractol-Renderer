/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <benjaminslakey@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 00:51:01 by bslakey           #+#    #+#             */
/*   Updated: 2017/05/23 00:51:04 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include "libft.h"
# include "mlx.h"

# define TRANS_LEFT(keycode) (keycode == 0)
# define TRANS_RIGHT(keycode) (keycode == 2)
# define TRANS_UP(keycode) (keycode == 13)
# define TRANS_DOWN(keycode) (keycode == 1)
# define MORE_ITER(keycode) (keycode == 24)
# define LESS_ITER(keycode) (keycode == 27)
# define ZOOM_IN(keycode) (keycode == 4)
# define ZOOM_OUT(keycode) (keycode == 5)
# define PAUSE(keycode) (keycode == 49)
# define EXIT(keycode) (keycode == 53)

# define HEIGHT 800
# define WIDTH 800
# define THREAD_COUNT 16

# define SUCCESS 0
# define FAILURE 1

struct s_prog;

typedef int		(*t_fract)(struct s_prog *f, double x, double y);

typedef struct	s_prog
{
	void		*window;
	void		*mlx;
	void		*img;
	char		*map;
	int			lsize;
	int			bpp;
	int			endian;
	int			err;
	int			n_iter;
	double		zoom;
	double		vdim[2];
	double		x_range[2];
	double		y_range[2];
	double		dx;
	double		dy;
	double		mouse_x;
	double		mouse_y;
	int			pause;
	int			type;
	t_fract		setf;
}				t_prog;

typedef struct	s_thread
{
	double		y1;
	double		y2;
	t_prog		*f;
	pthread_t	thread;
}				t_thread;

double			range_change(double range1[2], double range2[2], double scale);
void			bzero_coords(double (*array)[2]);
int				expose_events(t_prog *f);
int				motion_events(int x, int y, t_prog *f);
int				mouse_events(int code, int x, int y, t_prog *f);
int				key_events(int code, t_prog *f);
void			*draw(void *thread);
void			draw_pixel(t_prog *f, int x, int y, int rgb);
int				get_color(t_prog *f, int iterations);
int				burning_ship(t_prog *f, double x, double y);
int				julia_set(t_prog *f, double x, double y);
int				mandelbrot_set(t_prog *f, double x, double y);
void			zoom(t_prog *f);
void			set_ranges(t_prog *f);
double			scale_x(t_prog *f, double x);
double			scale_y(t_prog *f, double y);
void			print_usage(void);
int				chose_fractol(t_prog *f, char *input);
t_prog			*init_prog(char *input);
void			free_program(t_prog *f);
void			thread_fractol(t_prog *f);

#endif
