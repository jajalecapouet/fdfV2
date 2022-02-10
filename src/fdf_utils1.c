/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:51:40 by njaros            #+#    #+#             */
/*   Updated: 2022/02/10 15:07:53 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

//La fonction ci-dessous N'EST PAS mlx_pixel_put
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//Ci dessous fonction qui retourne un int qui est un arrondi d'un double
int	dtoi(double d)
{
	int		aprox;

	aprox = d;
	if ((d - aprox) * 10 >= 5)
		return (aprox + 1);
	return (aprox);
}

//La fonction ci-dessous met x ou y à l'échelle
int	cal(double d, double t, double s)
{
	int	cal;

	cal = dtoi(s * (1.0 / 2.0 + d / (t * 2 * M_SQRT2)));
	return (cal);
}

//La fonction ci-dessous retourne 1 si le point de coordonnées (x, y) n'est pas en dehors de l'écran
int	dans_le_cadre(int x, int y)
{
	if (x < 0 || x > 1920 || y < 0 || y > 1080)
		return (0);
	else
		return (1);
}

//La fonction ci-dessous remplit l'image de la data avant mlx_put_image_to_window
int	remplir_image(t_all *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	planeur(m);
	if (!m->plan)
		return (0);
	while (m->plan[j])
	{
		while (m->plan[j][i].exist)
		{
			if (dans_le_cadre(m->plan[j][i].x, m->plan[j][i].y))
			{
				my_mlx_pixel_put(m->data, m->plan[j][i].x, m->plan[j][i].y, m->plan[j][i].couleur);
				traiteur(i, j, m);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}