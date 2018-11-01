#include <stdlib.h>
#include <stdbool.h>

static unsigned long	ft_power_16(int power)
{
	if (power <= 0)
		return (1);
	return (16 * ft_power_16(power - 1));
}

static void	*hextoa_alloc_string(int *len, unsigned long nb)
{
	unsigned long	number;
	int				str_len;
	char			*temp;

	str_len = 0;
	number = nb;
	while (number != 0)
	{
		number /= 16;
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

char		*ft_hextoa(unsigned long nb, bool uppercase)
{
	unsigned long	diviseur;
	int				len;
	char			*string;
	char			*tmp;
	char			*charset;

	string = hextoa_alloc_string(&len, nb);
	if (string == NULL)
		return (NULL);
	charset = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
	tmp = string;
	if (nb == 0)
		*string = '0';
	diviseur = ft_power_16(len - 1);
	while (diviseur > 0)
	{
		*tmp++ = charset[nb / diviseur];
		nb %= diviseur;
		diviseur /= 16;
	}
	return (string);
}
