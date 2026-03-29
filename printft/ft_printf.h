/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:44:19 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/27 16:46:19 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putstr(char *str);
int	ft_putchar(char c);
int	ft_putnbr(int n);
int	ft_unsinbr(unsigned int n);
int	ft_putnbrhexa(unsigned long n, char *hex);
int	ft_point(void *ptr);

#endif
