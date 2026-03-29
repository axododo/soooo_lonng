/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:50:18 by mguilber          #+#    #+#             */
/*   Updated: 2025/11/07 15:52:36 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrhexa(unsigned long n, char *hex)
{
	int	i;

	i = 0;
	if (n >= 16)
		i += ft_putnbrhexa(n / 16, hex);
	ft_putchar(hex[n % 16]);
	i++;
	return (i);
}
