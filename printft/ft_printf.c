/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:44:14 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/27 16:44:15 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	part2(const char *format, va_list(args))
{
	int	i;

	i = 0;
	format++;
	if (*format == 'c')
		i += ft_putchar(va_arg(args, int));
	else if (*format == 's')
		i += ft_putstr(va_arg(args, char *));
	else if (*format == 'i' || *format == 'd')
		i += ft_putnbr(va_arg(args, int));
	else if (*format == 'u')
		i += ft_unsinbr(va_arg(args, int));
	else if (*format == '%')
	{
		i++;
		write(1, "%", 1);
	}
	else if (*format == 'x')
		i += ft_putnbrhexa(va_arg(args, unsigned int), "0123456789abcdef");
	else if (*format == 'X')
		i += ft_putnbrhexa(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (*format == 'p')
		i += ft_point(va_arg(args, void *));
	return (i);
}

int	part(const char *format, va_list(args))
{
	int	i;

	i = 0;
	while (*format)
	{
		if (*format == '%')
		{
			i += part2(format, args);
			format++;
		}
		else
		{
			write(1, &*format, 1);
			i++;
		}
		format++;
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		size;

	va_start(args, format);
	size = part(format, args);
	va_end(args);
	return (size);
}
/*
int	main(int argc, char const *argv[]) {
	printf("len_>( %i ) \n", ft_printf("%s %i ", "hello", 15));
	printf("trueLen_>( %i ) ", printf("%s %i ", "hello", 15));

	return (0);
}

*/
/*
int	main(void) {
  printf("%i\n", ft_printf(" %p %p ", 0, 0));
  write(1, "\n", 1);
  printf("%i\n", printf(" %p %p ", 0, 0));

}*/
