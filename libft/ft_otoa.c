#include <stdlib.h>

static unsigned long	ft_power_8(int power)
{
	if (power <= 0)
		return (1);
	return (8 * ft_power_8(power - 1));
}

static void	*otoa_alloc_string(int *len, unsigned long nb)
{
	unsigned long	number;
	int				str_len;
	char			*temp;

	str_len = 0;
	number = nb;
	while (number != 0)
	{
		number /= 8;
		str_len++;
	}
	*len = str_len;
	if (nb == 0)
		str_len++;
	temp = malloc(sizeof(char) * (str_len + 1));
	if (temp == NULL)
		return (NULL);
	temp[str_len] = '\0';
	return (temp);
}

char		*ft_otoa(unsigned long nb)
{
	unsigned long	diviseur;
	int				len;
	char			*string;
	char			*tmp;

	string = otoa_alloc_string(&len, nb);
	if (string == NULL)
		return (NULL);
	tmp = string;
	if (nb == 0)
		*string = '0';
	diviseur = ft_power_8(len - 1);
	while (diviseur > 0)
	{
		*tmp++ = (char)('0' + (nb / diviseur));
		nb %= diviseur;
		diviseur /= 8;
	}
	return (string);
}
