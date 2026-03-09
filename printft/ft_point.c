
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
