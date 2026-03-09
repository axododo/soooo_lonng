
#include "ft_printf.h"

int	ft_unsinbr(unsigned int n)
{
	char	c;
	int		i;

	i = 0;
	if (n >= 10)
		i += ft_unsinbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
	i++;
	return (i);
}
