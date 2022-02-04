#include "../includes/fdf.h"

int	fdf(t_all *michel)
{
	int	i;
	int j;

//	printf("sommes nous deja arrive ici ? \n");
	i = 0;
	j = 0;
	while (michel->tab[i])
	{
		//ft_putnbr_fd(i, 1);
		while (michel->tab[i][j].dist_xy > 0.1)
		{
			//printf(" %lf ", michel->tab[i][j].dist_xy);
			printf("x : %d | y : %d | z : %d | couleur : %d\t", michel->tab[i][j].x_init, michel->tab[i][j].y_init, michel->tab[i][j].z_init, michel->tab[i][j].couleur);
			printf("angles : %lf | %lf | %lf", michel->tab[i][j].angle_xy, michel->tab[i][j].angle_xz, michel->tab[i][j].angle_yz);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
	return (0);
}
