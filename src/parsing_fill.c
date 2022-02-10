/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:42:21 by njaros            #+#    #+#             */
/*   Updated: 2022/02/10 13:07:04 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	is_fdf_file(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i < 4 || ft_strncmp(".fdf", &str[i - 4], 4) == 0)
		return (1);
	return (0);
}

t_list	*fill_lst(int fd, int *ht)
{
	t_list	*map;
	t_list	*secure;
	int		compt;
	char	*ligne;

	compt = 0;
	map = NULL;
	ligne = get_next_line(fd);
	while (ligne)
	{
		secure = ft_lstnew(ligne);
		if (!secure)
		{
			ft_lstclear(&map, free);
			return (NULL);
		}
		ft_lstadd_back(&map, secure);
		ligne = get_next_line(fd);
		compt++;
	}
	*ht = compt;
	return (map);
}

t_point	*fill_tab(char *pixel, t_all *michel, int y)
{
	t_point	*pouet;
	int		i;

	pouet = malloc(sizeof(t_point) * michel->lg + 1);
	if (!pouet)
		return (NULL);
	i = 0;
	while (pixel)
	{
		init_xy(&pouet[i], i, y, michel);
		pouet[i].z_init = ft_atoi(pixel);
		pouet[i].z = (double)pouet[i].z_init;
		pouet[i].couleur = ckoilacouleur(pixel);
		pouet[i].dist_xy = donne_distance(pouet[i].x_init, pouet[i].y_init);
		pouet[i].dist_xz = donne_distance(pouet[i].x_init, pouet[i].z_init);
		pouet[i].dist_yz = donne_distance(pouet[i].y_init, pouet[i].z_init);
		pouet[i].angle_xy = donne_angle(pouet[i].x_init, pouet[i].y_init, pouet[i].dist_xy);
		pouet[i].angle_xz = donne_angle(pouet[i].x_init, pouet[i].z_init, pouet[i].dist_xz);
		pouet[i].angle_yz = donne_angle(pouet[i].y_init, pouet[i].z_init, pouet[i].dist_yz);
		i++;
		pixel = pixel_suivant(pixel);
	}
	pouet[i].exist = 0;
	return (pouet);
}

t_point	**tab_build(t_list **map, t_all *michel)
{
	t_point	**tab;
	int		i;

	tab = malloc(sizeof(t_point *) * michel->ht + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (*map)
	{
		tab[i] = fill_tab((*map)->content, michel, i);
		if (!tab[i])
		{
			freezbi(tab);
			return (NULL);
		}
		ligne_suivante(map);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	stock_info_tab(int fd, t_all *michel)
{
	t_list	*lst_lignes;
	char	*ligne;

	lst_lignes = fill_lst(fd, &(michel->ht));
	if (!lst_lignes)
	{
		michel->plan = NULL;
		michel->tab = NULL;
	}
	else
	{
		michel->lg = compteur_points_ligne(lst_lignes->content);
		michel->plan = malloc_plan(michel->ht, michel->lg);
		if (!michel->plan)
		{
			freezbi(michel->tab);
			michel->tab = NULL;
		}
		else
			michel->tab = tab_build(&lst_lignes, michel);
		if (!michel->tab)
			ft_lstclear(&lst_lignes, free);
	}
}
