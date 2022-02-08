/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotato.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:03:37 by njaros            #+#    #+#             */
/*   Updated: 2022/02/08 15:35:34 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	rotato_x(t_point **tab, double angle)
{
	int		i;
	int		j;
	double	a;
	double	pre_y;

	i = -1;
	j = -1;
	while (tab[++j])
	{
		while (tab[j][++i].dist_xy > 0.1)
		{
			pre_y = tab[j][i].y;
			tab[j][i].angle_yz += angle;
			a = tab[j][i].angle_yz;
			tab[j][i].y = cos(a) * pre_y - sin(a) * tab[j][i].z;
			tab[j][i].z = sin(a) * pre_y + cos(a) * tab[j][i].z;
		}
		i = 0;
	}
}

void	rotato_y(t_point **tab, double angle)
{
	int		i;
	int		j;
	double	a;
	double	pre_x;

	i = -1;
	j = -1;
	while (tab[++j])
	{
		while (tab[j][++i].dist_xy > 0.1)
		{
			pre_x = tab[j][i].x;
			tab[j][i].angle_xz += angle;
			a = tab[j][i].angle_xz;
			tab[j][i].x = cos(a) * pre_x + sin(a) * tab[j][i].z;
			tab[j][i].z = cos(a) * tab[j][i].z - sin(a) * pre_x;
		}
		i = 0;
	}
}

void	rotato_z(t_point **tab, double angle)
{
	int		i;
	int		j;
	double	a;
	double	pre_x;

	i = -1;
	j = -1;
	while (tab[++j])
	{
		while (tab[j][++i].dist_xy > 0.1)
		{
			pre_x = tab[j][i].x;
			tab[j][i].angle_xy += angle;
			a = tab[j][i].angle_xy;
			tab[j][i].x = cos(a) * pre_x - sin(a) * tab[j][i].y;
			tab[j][i].y = sin(a) * pre_x + cos(a) * tab[j][i].y;
		}
		i = 0;
	}
}