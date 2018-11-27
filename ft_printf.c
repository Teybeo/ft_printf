#include <array.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "parsing.h"
#include "processing.h"

void consume_non_arg(const char *string, t_array *array, int *consumed);

int		ft_printf(const char *string, ...)
{
	va_list	list;
	t_array	output;
	t_arg	arg;
	int		consumed;
	int		error;

	error = 0;
	output = array_create(sizeof(char), 64);
	va_start(list, string);
	while (*string)
	{
		if (*string == '%')
		{
			string++;
			arg = get_next_arg(string, &consumed);
			string += consumed;
			process_arg2(&output, arg, list, &error);
			if (error)
			{
				free(output.data);
				return -1;
			}
		}
		else
		{
			consume_non_arg(string, &output, &consumed);
			string += consumed;
		}
	}
	va_end(list);
	write(1, output.data, (size_t)output.size);
	free(output.data);
	return output.size;
}

int		get_first_index(const char *string, char c)
{
	int	i;

	i = 0;
	while (string[i] != c && string[i] != '\0')
		i++;
	return (string[i] != '\0' ? i : -1);
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
