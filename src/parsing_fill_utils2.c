/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:24:00 by njaros            #+#    #+#             */
/*   Updated: 2022/02/10 14:00:19 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	calcul_poids(char c, char *base, int exp)
{
	int poids;
	int	i;

	i = 0;
	poids = 1;
	if (exp != 0)
	{
		while (exp != 0)
		{
			poids *= 16;
			exp--;
		}
	}
	while (c != base[i])
		i++;
	return (i * poids);
}

int	hexa_to_int(char *str)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	j = 0;
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\n')
	{
		str[i] = ft_tolower((int)str[i]);
		i++;
	}
	while (str[--i] != 'x')
	{
		nb += calcul_poids(str[i], "0123456789abcdef", j);
		j++;
	}
	return (nb);
}

int	ckoilacouleur(char *pixel)
{
	int	i;

	i = 0;
	while (pixel[i] == ' ')
		i++;
	if (pixel[i] == '-' || pixel[i] == '+')
		i++;
	while (ft_isdigit((int)pixel[i]))
		i++;
	if (pixel[i] == ' ' || pixel[i] == '\n' || pixel[i] == 0)
		return (0xffffff);
	else
		return (hexa_to_int(&pixel[i + 3]));
}

void	init_xy(t_point *p, int x, int y, t_all *michel)
{
	p->x_init = x - michel->lg / 2;
	p->y_init = y - michel->ht / 2;
	p->x = (double)p->x_init;
	p->y = (double)p->y_init;
	p->exist = 1;
}

t_plan	**malloc_plan(int ht, int lg)
{
	int	i;
	int	j;
	t_plan	**plan;
	
	plan = malloc(sizeof(t_plan *) * ht + 1);
	if (!plan)
		return (NULL);
	i = -1;
	while (++i < ht)
	{
		plan[i] = malloc(sizeof(t_plan) * lg + 1);
		if (!plan[i])
		{
			while (--i >= 0)
				free(plan[i]);
			free(plan);
			return (NULL);
		}
		plan[i][lg].exist = 0;
	}
	plan[i] = NULL;
	return (plan);
}
