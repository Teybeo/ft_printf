/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variants_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:03:36 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/28 18:03:36 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <array.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

int		ft_printf(const char *string, ...)
{
	t_array	output;
	va_list	list;
	int		ret;

	va_start(list, string);
	ret = real_printf(&output, string, list);
	va_end(list);
	write(1, output.data, (size_t)output.size);
	free(output.data);
	return (ret);
}

int		ft_sprintf(char *str, const char *format, ...)
{
	t_array	output;
	va_list	list;
	int		ret;

	va_start(list, format);
	ret = real_printf(&output, format, list);
	va_end(list);
	ft_memcpy(str, output.data, (size_t)output.size);
	free(output.data);
	return (ret);
}

int		ft_snprintf(char *str, size_t size, const char *format, ...)
{
	t_array	output;
	va_list	list;
	int		ret;

	va_start(list, format);
	ret = real_printf(&output, format, list);
	va_end(list);
	ft_memcpy(str, output.data, size);
	free(output.data);
	return (ret);
}

int		ft_asprintf(char **str, const char *format, ...)
{
	t_array	output;
	va_list	list;
	int		ret;

	va_start(list, format);
	ret = real_printf(&output, format, list);
	va_end(list);
	*str = output.data;
	return (ret);
}

int		ft_dprintf(int fd, const char *string, ...)
{
	t_array	output;
	va_list	list;
	int		ret;

	va_start(list, string);
	ret = real_printf(&output, string, list);
	va_end(list);
	write(fd, output.data, (size_t)output.size);
	free(output.data);
	return (ret);
}
