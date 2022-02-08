/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:15:56 by njaros            #+#    #+#             */
/*   Updated: 2022/02/08 15:37:19 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

//Cette fonction récupère et calibre le strict nécessaire a envoyer à la mlx
void	planeur(t_all *m)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (m->tab[++j])
	{
		while (m->tab[j][++i].dist_xy > 0.1)
		{
			m->plan[j][i].x = cal(m->tab[j][i].x, (double)m->lg, 1920.0);
			m->plan[j][i].y = cal(m->tab[j][i].y, (double)m->ht, 1080.0);
			m->plan[j][i].couleur = m->tab[j][i].couleur;
			m->plan[j][i].exist = 42;
		}
		i = -1;
	}
}

//Cette fonction improbable permet de faire un dégradé de couleur
int	moy_col(int *pts, int dep, int arr, int pos)
{
	int		rouge;
	int		vert;
	int		bleu;
	float	ratio;

	ratio = (float)(pos - dep) / (float)(arr - dep);
	rouge = (pts[2] / 65536) * (1 - ratio) + (pts[5] / 65536) * ratio;
	vert = ((pts[2] << 8) / 65536) * (1 - ratio) + ((pts[5] << 8) / 65536) * ratio;
	bleu = ((pts[2] << 16) / 65536) * (1 - ratio) + ((pts[5] << 16) / 65536) * ratio;
	return ((rouge << 16) + (vert << 8) + bleu);
}

//Les 3 fonctions ci-dessous tracent les trait entre un point et ses 2 prédécesseurs
//Ces fonctions ne s'utilisent qu'avec un point de x et y entier
void	trace_trait_y(int *pts, t_data *d)
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

void	trace_trait_x(int *pts, t_data *d)
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

void	traiteur(int x, int y, t_all *m)
{
	int	mem[6];
	
	mem[0] = x;
	mem[1] = y;
	mem[2] = m->plan[y][x].couleur;
	if (y > 0)
	{
		mem[3] = m->plan[y - 1][x].x;
		mem[4] = m->plan[y - 1][x].y;
		mem[5] = m->plan[y - 1][x].couleur;
		if (abs(mem[1] - mem[4]) > abs(mem[0] - mem[3]))
			trace_trait_y(mem, m->data);
		else
			trace_trait_x(mem, m->data);
	}
	if (x > 0)
	{
		mem[3] = m->plan[y][x - 1].x;
		mem[4] = m->plan[y][x - 1].y;
		mem[5] = m->plan[y][x - 1].couleur;
		if (abs(mem[1] - mem[4]) > abs(mem[0] - mem[3]))
			trace_trait_y(mem, m->data);
		else
			trace_trait_x(mem, m->data);
	}
}