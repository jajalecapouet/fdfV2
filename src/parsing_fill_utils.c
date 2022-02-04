/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:54:35 by njaros            #+#    #+#             */
/*   Updated: 2022/02/04 14:22:49 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

char	*pixel_suivant(char *ligne)
{
	int	i;

	i = 0;
	while (ligne[i] == ' ')
		i++;
	while (ligne[i] && ligne[i] != ' ' && ligne[i] != '\n')
		i++;
	while (ligne[i] == ' ')
		i++;
	if (!ligne[i] || ligne[i] == '\n')
		return (NULL);
	return (&ligne[i]);
}

int	compteur_points_ligne(char *ligne)
{
	int	cpt;
	int	i;

	cpt = 0;
	i = 0;
	while (ligne[i] == ' ' || ligne[i] == '\n')
		i++;
	ligne = &ligne[i];
	while (ligne)
	{
		ligne = pixel_suivant(ligne);
		cpt++;
	}
	return cpt;
}

double	donne_distance(int x, int y)
{
	return (sqrt(pow(x, 2) + pow(y, 2)));
}

double	donne_angle(int x, int y, double dist)
{
	double angle;

	if (dist == 0)
		return (0);
	angle = acos((double)x / dist);
	if (y < 0)
		angle = 2 * M_PI - angle;
	return (angle);
}

void	ligne_suivante(t_list **lst)
{
	t_list	*temp;

	temp = (*lst)->next;
	ft_lstdelone(*lst, free);
	*lst = temp;
}
