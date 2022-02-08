/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:14:16 by njaros            #+#    #+#             */
/*   Updated: 2022/02/07 09:45:41 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "fdf.h"
# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *fmt, ...);
int	ft_read(const char *fmt, va_list ap);
//int	ft_putnbr_fd(int n, int fd);
int	ft_recuputnbr_fd(long n, int fd);
//int	ft_putchar_fd(char c, int fd);
int	ft_putunsignedint_fd(unsigned int n, int fd);
//int	ft_putstr_fd(char *s, int fd);
int	ft_puthexa_fd(unsigned int nb, char *base, int fd);
int	ft_putadr(unsigned long int adr, int fd);
int	recu_adr(unsigned long int nb, char *base, int fd);
int	ft_int(int ap, char type);
int	ft_unsignedint(unsigned int ap, char type);

#endif