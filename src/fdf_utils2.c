/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:15:56 by njaros            #+#    #+#             */
/*   Updated: 2022/02/10 15:17:57 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

//Cette fonction récupère et calibre le strict nécessaire a envoyer à la mlx
void	planeur(t_all *m)
{
	int	i;
	int	j;
	int	k = 0;

	i = -1;
	j = -1;
	while (m->tab[++j])
	{
		while (m->tab[j][++i].exist == 1)
		{
			m->plan[j][i].x = cal(m->tab[j][i].x, (double)m->lg, 1920.0);
			m->plan[j][i].y = cal(m->tab[j][i].y, (double)m->ht, 1080.0);
			//ft_printf("%d | %d \n", m->plan[j][i].x, m->plan[j][i].y);
			m->plan[j][i].couleur = m->tab[j][i].couleur;
			m->plan[j][i].exist = 42;
			k++;
		}
		i = -1;
	}
	ft_printf("nbr de points : %d \n", k);
}

//Cette fonction improbable permet de faire un dégradé de couleur
int	moy_col(int *pts, int dep, int arr, int pos)
{
	int		rouge;
	int		vert;
	int		bleu;
	double	ratio;

	ratio = (double)(pos - dep) / (double)(arr - dep);
	rouge = (double)(pts[2] / 65536) * (1.0 - ratio) + (double)(pts[5] / 65536) * ratio;
	vert = (double)((pts[2] << 8) / 65536) * (1.0 - ratio) + (double)((pts[5] << 8) / 65536) * ratio;
	bleu = (double)((pts[2] << 16) / 65536) * (1.0 - ratio) + (double)((pts[5] << 16) / 65536) * ratio;
	return ((rouge << 16) + (vert << 8) + bleu);
}

//Les 3 fonctions ci-dessous tracent les trait entre un point et ses 2 prédécesseurs
//Ces fonctions ne s'utilisent qu'avec un point de x et y entier
void	trace_trait_yy(int *pts, t_data *d)
{
	double	a;
	double	b;
	int		depart;

	depart = pts[1];
	if (pts[1] == pts[4])
		return ;
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

void	trace_trait_yx(int *pts, t_data *d)
{
	double	a;
	double	b;
	int		depart;

	depart = pts[0];
	if (pts[0] == pts[3])
		return ;
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

void	traiteur(int i, int j, t_all *m)
{
	int	mem[6];
	int	mem2[6];
	
	mem[0] = m->plan[j][i].x;
	mem[1] = m->plan[j][i].y;
	mem[2] = m->plan[j][i].couleur;
	mem2[0] = mem[0];
	mem2[1] = mem[1];
	mem2[2] = mem[2];
	if (j > 0)
	{
		mem[3] = m->plan[j - 1][i].x;
		mem[4] = m->plan[j - 1][i].y;
		mem[5] = m->plan[j - 1][i].couleur;
		if (abs(mem[1] - mem[4]) > abs(mem[0] - mem[3]))
			trace_trait_yy(mem, m->data);
		else
			trace_trait_yx(mem, m->data);
	}
	if (i > 0)
	{
		mem2[3] = m->plan[j][i - 1].x;
		mem2[4] = m->plan[j][i - 1].y;
		//ft_printf("coord du plan de travail : i : %d | j : %d \tdep : %d | %d \tarr : %d | %d\n", i, j, mem2[0], mem2[1], mem2[3], mem2[4]);
		mem2[5] = m->plan[j][i - 1].couleur;
		if (abs(mem2[1] - mem2[4]) > abs(mem2[0] - mem2[3]))
			trace_trait_yy(mem2, m->data);
		else
			trace_trait_yx(mem2, m->data);
	}
}