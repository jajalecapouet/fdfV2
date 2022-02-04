/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:19:58 by njaros            #+#    #+#             */
/*   Updated: 2022/02/04 16:50:59 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <math.h>

// La structure s_data me permet de créer ma fonction put_pixel, car mlx_put_pixel bug et est interdite.

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}	t_data;

// La structure s_point m permet de contenir les coordonnées initiales et transformées de chaque t_point de la surface à afficher,
// Ainsi que d'autres infos utiles pour mes calculs de transformations.
// x_init, y_init, z_init sont les données fixes entrées par le fichier .fdf.
// dist_xy informe de la distance fixe réelle du t_point par rapport au centre du repère du plan xy (itou pour les plans xz et yz).
// angle_xy informe de l'angle variable réel du t_point par rapport au repère du plan xy (itou pour les plans xz et yz).
// x, y et z sont les valeur actuelles des points à afficher

typedef struct	s_point
{
	int		x_init;
	int		y_init;
	int		z_init;
	int		couleur;
	double	dist_xy;
	double	dist_xz;
	double	dist_yz;
	double	angle_xy;
	double	angle_xz;
	double	angle_yz;
	double	x;
	double	y;
	double	z;
}	t_point;

// La structure s_all contient tout, ce qui me permet de ne jamais avoir plus de 4 paramètres dans mes fonctions.

typedef struct	s_all
{
	t_data	*data;
	int		lg;
	int		ht;
	t_point	**tab;
	void	*mlx;
	void	*win;
}	t_all;

// Fonction de gestion de fin de programme

int	puterror(int error);

// Ici on free car on a tout compris

void	friteuse(t_all *michel);
void	gordon_freeman(t_data *data, void *mlx_ptr);
void	freezbi(t_point **tab);

// Fonctions de parsing et stockage des données

int		main(int ac, char **av);
int		is_fdf_file(char *str);
int		calcul_poids(char c, char *base, int exp);
int		hexa_to_int(char *str);
int		ckoilacouleur(char *pixel);
char	*pixel_suivant(char *ligne);
int		compteur_points_ligne(char *ligne);
double	donne_distance(int x, int y);
double	donne_angle(int x, int y, double dist);
void	ligne_suivante(t_list **lst);
t_list	*fill_lst(int fd, int *ht);
t_point	*fill_tab(char *pixel, t_all *michel, int y);
t_point	**tab_build(t_list **map, t_all *michel);
void	stock_info_tab(int fd, t_all *michel);

// !!!!! A SUPPRIMER AVANT RENDU !!!!!!!! Fonctions de tests

// 

int		fdf(t_all *michel);

#endif