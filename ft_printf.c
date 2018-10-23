#include "ft_printf.h"
#include "libft.h"

#include "array.h"

#include <stdio.h>
#include <zconf.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

/*
 * sS p dD i oO uU xX cC
 * #
 * 0
 * -
 * +
 * ' '
 *
 * hh, h, l, ll, j, et .
 */

typedef struct s_arg t_arg;

typedef void (*ft_token)(t_arg arg);

struct s_arg
{
	bool alternate_form;
	bool left_adjust; // Default to right adjust
	bool zero_padding; // Default to blank-padding
	bool positive_sign;
	bool space_positive;
	int field_width;
	int precision;
//	ft_token fn;
	char token;
};

void consume_non_arg(const char *string, t_array *array, int *consumed);

void process_arg(t_array *pArray, t_arg arg, va_list list);


int		get_first_index(const char *string, char c)
{
	int	i;

	i = 0;
	while (string[i] != c && string[i] != '\0')
		i++;
	return (string[i] != '\0' ? i : -1);
}

bool get_next_arg(const char *string, t_arg *arg, int *consumed)
{
	const char	*ptr;

	ptr = string;
	while (*ptr != '\0')
	{
		if (*ptr == 'd')
		{
			arg->token = 'd';
			break;
		}
		ptr++;
	}
	*consumed = (int)(ptr - string) + 1;
	return true;
}

int		ft_printf(const char *string, ...)
{
	va_list	list;
	t_array	output;
	t_arg	arg;
	int		consumed;

	output = array_create(sizeof(char), 64);
	va_start(list, string);
	while (*string)
	{
		if (*string == '%')
		{
			get_next_arg(string, &arg, &consumed);
			string += consumed;
			process_arg(&output, arg, list);
		}
		else
		{
			consume_non_arg(string, &output, &consumed);
			string += consumed;
		}
	}
	va_end(list);
	write(1, output.data, (size_t)output.size);
	return output.size;
}

void process_arg(t_array *output, t_arg arg, va_list list)
{
	if (arg.token == 'd')
	{
		int d = va_arg(list, int);
		char *new = ft_itoa(d);
		array_append(output, new, ft_strlen(new));
	}
}

void consume_non_arg(const char *string, t_array *array, int *consumed)
{
	int	start_idx;

	start_idx = get_first_index(string, '%');
	if (start_idx == -1)
	{
		start_idx = (int)ft_strlen(string);
	}
	array_append(array, (void *)string, (size_t)start_idx);
	*consumed = start_idx;
}
