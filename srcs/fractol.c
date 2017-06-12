/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <benjaminslakey@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 00:52:06 by bslakey           #+#    #+#             */
/*   Updated: 2017/05/23 00:52:08 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			thread_fractol(t_prog *f)
{
	int			i;
	t_thread	*threads;

	i = -1;
	threads = (t_thread*)malloc(sizeof(t_thread) * THREAD_COUNT);
	mlx_clear_window(f->mlx, f->window);
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	f->map = mlx_get_data_addr(f->img, &(f->bpp), &(f->lsize), &(f->endian));
	while (++i < THREAD_COUNT)
	{
		threads[i].f = f;
		threads[i].y1 = i * (HEIGHT / THREAD_COUNT);
		threads[i].y2 = (i + 1) * (HEIGHT / THREAD_COUNT);
		pthread_create(&(threads[i].thread), NULL, draw, (void*)&(threads[i]));
	}
	i = -1;
	while (++i < THREAD_COUNT)
		pthread_join(threads[i].thread, NULL);
	mlx_put_image_to_window(f->mlx, f->window, f->img, 0, 0);
	mlx_destroy_image(f->mlx, f->img);
	free(threads);
}

int				main(int argc, char **argv)
{
	t_prog		*f;

	f = NULL;
	if (argc == 2)
	{
		f = init_prog(argv[1]);
		if (f->err)
		{
			free_program(f);
			return (EXIT_FAILURE);
		}
		thread_fractol(f);
		mlx_expose_hook(f->window, expose_events, f);
		mlx_hook(f->window, 6, 64, motion_events, f);
		mlx_hook(f->window, 2, 3, key_events, f);
		mlx_mouse_hook(f->window, mouse_events, f);
		mlx_loop(f->mlx);
	}
	else
	{
		ft_putstr(RED"Only one arguments allowed\n"CRESET);
		print_usage();
	}
	return (EXIT_SUCCESS);
}
