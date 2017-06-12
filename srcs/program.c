/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <benjaminslakey@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 00:51:37 by bslakey           #+#    #+#             */
/*   Updated: 2017/05/23 00:51:40 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			choose_fractal(t_prog *f, char *in)
{
	if (!ft_strcmp(in, "Julia") || !ft_strcmp(in, "julia"))
	{
		f->type = 1;
		f->setf = &julia_set;
	}
	else if (!ft_strcmp(in, "Mandelbrot") || !ft_strcmp(in, "mandelbrot"))
	{
		f->type = 2;
		f->setf = &mandelbrot_set;
	}
	else if (!ft_strcmp(in, "Burning Ship") || !ft_strcmp(in, "burning ship"))
	{
		f->type = 3;
		f->setf = &burning_ship;
	}
	else
	{
		ft_putstr(RED"Not a valid Fractal\n\n"CRESET);
		print_usage();
		return (FAILURE);
	}
	return (SUCCESS);
}

void		print_usage(void)
{
	ft_putstr(YELLOW"The available Fractals to explore are\n");
	ft_putstr("1. Julia\n2. Mandelbrot\n3. Burning Ship\n\n");
	ft_putstr("Program usage is as follows: ./fractol fractal_name\n");
	ft_putstr("Ex. ./fractol Julia\n");
	ft_putstr("- You can zoom or out on the fractals with the mouse wheel\n");
	ft_putstr("- Fractal view can be translated with WASD\n");
	ft_putstr("- Press ESC to exit\n");
	ft_putstr("- SPACE, locks the julia seed to current mouse position\n");
	ft_putstr(""CRESET);
}

t_prog		*init_prog(char *input)
{
	t_prog	*f;

	f = (t_prog*)malloc(sizeof(t_prog));
	f->mlx = mlx_init();
	f->window = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fractal");
	(f->vdim)[0] = WIDTH;
	(f->vdim)[1] = HEIGHT;
	f->n_iter = 50;
	f->zoom = 1.0;
	f->pause = 0;
	f->err = choose_fractal(f, input);
	return (f);
}

void		free_program(t_prog *f)
{
	mlx_destroy_window(f->mlx, f->window);
	free(f);
}
