/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 10:42:04 by njaros            #+#    #+#             */
/*   Updated: 2021/11/20 10:42:04 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

void	ft_bzero(void *s, size_t n);
int		contain_return(char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_substr_free(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strjoin_free(char *s1, char *s2, int del);
char	*ft_return_and_keep(char **temp, char *line, int n);

#endif