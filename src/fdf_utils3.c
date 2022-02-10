/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:25:57 by njaros            #+#    #+#             */
/*   Updated: 2022/02/10 11:39:21 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	trace_trait_xx(int *pts, t_data *d)
{
	double	a;
	double	b;
	int		depart;

	depart = pts[0];	
	a = (double)(pts[1] - pts[4]) / (double)(pts[0] - pts[3]);
	b = a;
	while (pts[0] != pts[3])
	{
		if (pts[0] > pts[3])
		{
			if (--pts[0] != pts[3])
				my_mlx_pixel_put(d, pts[0], dtoi(pts[1] - a), moy_col(pts, depart, pts[3], pts[0]));
		}
		else
		{
			if (++pts[0] != pts[3])
				my_mlx_pixel_put(d, pts[0], dtoi(pts[1] + a), moy_col(pts, depart, pts[3], pts[0]));
		}
		a += b;
	}
}

void	trace_trait_xy(int *pts, t_data *d)
{
	double	a;
	double	b;
	int		depart;

	depart = pts[1];
	a = (double)(pts[0] - pts[3]) / (double)(pts[1] - pts[4]);
	b = a;
	while (pts[1] != pts[4])
	{
		if (pts[1] > pts[4])
		{
			if (--pts[1] != pts[4])
				my_mlx_pixel_put(d, dtoi(pts[0] - a), pts[1], moy_col(pts, depart, pts[4], pts[1]));
		}
		else
		{
			if (++pts[1] != pts[4])
				my_mlx_pixel_put(d, dtoi(pts[0] + a), pts[1], moy_col(pts, depart, pts[4], pts[1]));
		}
		a += b;
	}
}