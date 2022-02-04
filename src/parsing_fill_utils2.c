/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:24:00 by njaros            #+#    #+#             */
/*   Updated: 2022/02/04 14:26:14 by njaros           ###   ########lyon.fr   */
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
		return (0xfd6c9e);
	else
		return (hexa_to_int(&pixel[i + 3]));
}
