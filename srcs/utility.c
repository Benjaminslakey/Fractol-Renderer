/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bslakey <benjaminslakey@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 00:51:57 by bslakey           #+#    #+#             */
/*   Updated: 2017/05/23 00:51:59 by bslakey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double		range_change(double range1[2], double range2[2], double to_scale)
{
	double	old_range;
	double	new_range;
	double	ratio;

	old_range = range1[1] - range1[0];
	new_range = range2[1] - range2[0];
	ratio = new_range / old_range;
	return (to_scale * ratio);
}

void		bzero_coords(double (*array)[2])
{
	int		i;

	i = -1;
	while (++i < 2)
		(*array)[i] = 0.0;
	return ;
}
