/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:58:33 by njaros            #+#    #+#             */
/*   Updated: 2022/02/04 15:40:46 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	puterror(int error)
{
	if (error)
		ft_putstr_fd(strerror(error), 2);
	else
		ft_putendl_fd("bon déroulement du processus", 1);
	return (error);
}

int	main(int ac, char **av)
{
	int		fd;
	t_all	*michel;

	if (ac != 2)
		return (puterror(5));
	if (!is_fdf_file(av[1]))
		return (puterror(9));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (puterror(9));
	michel = malloc(sizeof(t_all));
	if (!michel)
		return (puterror(11));
	stock_info_tab(fd, michel);
	if (!michel->tab)
	{
		free(michel);
		return (puterror(11));
	}
	return (puterror(fdf(michel)));
}
