
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
