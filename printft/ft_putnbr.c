
#include "ft_printf.h"

int	ft_putnbr(int n)
{
	char	c;
	int		i;

	i = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		i++;
	}
	if (n >= 10)
		i += ft_putnbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
	i++;
	return (i);
}
