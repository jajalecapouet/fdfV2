/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_m_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:09:51 by njaros            #+#    #+#             */
/*   Updated: 2022/02/04 15:12:59 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	friteuse(t_all *michel)
{
	gordon_freeman(michel->data, michel->mlx);
	mlx_destroy_window(michel->mlx, michel->win);
	free(michel->mlx);
	free(michel);
}

void	gordon_freeman(t_data *data, void *mlx_ptr)
{
	mlx_destroy_image(mlx_ptr, data->img);
	free(data->addr);
	free(data);
}

void	freezbi(t_point **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}