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
	bool long_modifier;
	size_t min_width;
	size_t precision;
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

t_arg get_next_arg(const char *string, int *consumed)
{
	const char	*ptr;
	t_arg		arg;

	arg = (t_arg){};
	ptr = string;
	while (*ptr != '\0')
	{
		if (*ptr == 'd' || *ptr == 'i')
		{
			arg.token = 'd';
			break;
		}
		else if (*ptr == 'D')
		{
			arg.token = 'd';
			arg.long_modifier = true;
			break;
		}
		else if (*ptr == ' ')
		{
			if (arg.positive_sign == false)
				arg.space_positive = true;
		}
		else if (*ptr == '+')
		{
			arg.positive_sign = true;
			arg.space_positive = false;
		}
		else if (*ptr == 'l')
		{
			arg.long_modifier = true;
		}
		else if (*ptr == '.')
		{
			ptr++;
			arg.precision = ft_atoi(ptr);
			while (ft_isdigit(*ptr) && *ptr != '\0')
				ptr++;
			ptr--;
		}
		else if (*ptr == '0')
		{
			arg.zero_padding = true;
			while (*ptr == '0')
				ptr++;
			ptr--;
		}
		else if (ft_isdigit(*ptr))
		{
			arg.min_width = ft_atoi(ptr);
			while (ft_isdigit(*ptr) && *ptr != '\0')
				ptr++;
			ptr--;
		}
		ptr++;
	}
	*consumed = (int)(ptr - string) + 1;
	return (arg);
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
			arg = get_next_arg(string, &consumed);
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

void	append_n_chars(t_array *array, char c, size_t count)
{
	while (count-- != 0)
		array_append(array, &c, 1);
}

void process_arg(t_array *output, t_arg arg, va_list list)
{
	size_t	conversion_length;
	char	*new;
	char	*temp;

	if (arg.token == 'd')
	{
		if (arg.long_modifier)
		{
			long l = va_arg(list, long);
			if (arg.space_positive && l >= 0)
				array_append(output, " ", 1);
			if (arg.positive_sign && l >= 0)
				array_append(output, "+", 1);
			new = ft_ltoa(l);
			conversion_length = ft_strlen(new);
			if (arg.precision > conversion_length)
				append_n_chars(output, '0', arg.precision - conversion_length);
			array_append(output, new, conversion_length);
			free(new);
		}
		else
		{
#if 1
			int d = va_arg(list, int);
			new = ft_itoa(d);
			int is_neg = d < 0;
			int has_sign_char = d < 0 || arg.space_positive || arg.positive_sign;
			size_t itoa_len = ft_strlen(new);
			size_t digit_count = itoa_len - is_neg;
			ft_memcpy(new, new + (is_neg), digit_count); // Remove - in string
			size_t core_length = ft_max(arg.precision, digit_count) + has_sign_char;
			size_t final_length = ft_max(arg.min_width, core_length);
			temp = malloc(sizeof(char) * final_length);
			if (digit_count < arg.precision)
				ft_memset(temp + (final_length - core_length), '0', final_length - digit_count);
			if (has_sign_char)
			{
				if (arg.space_positive && !is_neg)
					temp[(final_length - core_length)] = ' ';
				else if (arg.positive_sign && !is_neg)
					temp[(final_length - core_length)] = '+';
				else if (is_neg)
					temp[(final_length - core_length)] = '-';
			}
			ft_memcpy(temp + (final_length - digit_count), new, digit_count);
			ft_memset(temp, ' ', final_length - core_length);
			array_append(output, temp, final_length);
#else
			int d = va_arg(list, int);
			if (arg.space_positive && d >= 0)
				array_append(output, " ", 1);
			if (arg.positive_sign && d >= 0)
				array_append(output, "+", 1);
			new = ft_itoa(d);
			if (new[0] == '-')
				array_append(output, "-", 1);
			conversion_length = (size_t)ft_max(ft_strlen(new), arg.min_width);
			if (arg.precision > conversion_length)
				append_n_chars(output, '0', arg.precision - conversion_length);
			array_append(output, new, ft_strlen(new));
			free(new);
#endif
		}
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
