/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:42:06 by njaros            #+#    #+#             */
/*   Updated: 2022/02/08 15:40:34 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	init_fdf(t_all *m)
{
	int	*a;
	int	*b;

	m->data = malloc(sizeof(t_data));
	a = &m->data->bits_per_pixel;
	b = &m->data->line_length;
	m->mlx = mlx_init();
	if (!m->mlx)
		return (0);
	m->win = mlx_new_window(m->mlx, 1920, 1080, "fdf V2");
	if (!m->win)
		return (0);
	m->data->img = mlx_new_image(m->mlx, 1920, 1080);
	if (!m->data->img)
		return (0);
	m->data->addr = mlx_get_data_addr(m->data->img, a, b, &(m->data->endian));
	return (1);
}

int	fdf(t_all *m)
{
	if (!init_fdf(m))
		return (11);
	remplir_image(m);
	mlx_put_image_to_window(m->mlx, m->win, m->data->img, 0, 0);
	mlx_loop(m->mlx);
	return (0);
}