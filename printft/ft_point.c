/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:44:06 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/27 16:46:14 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_point(void *ptr)
{
	int				i;
	unsigned long	itr;

	i = 2;
	itr = (unsigned long)ptr;
	if (itr == 0)
	{
		i = 0;
		i += write(1, "(nil)", 5);
	}
	else
	{
		write(1, "0x", 2);
		i += ft_putnbrhexa(itr, "0123456789abcdef");
	}
	return (i);
}
