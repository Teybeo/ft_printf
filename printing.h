/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:08:22 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/29 16:08:22 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTING_H
# define PRINTING_H

# include "array.h"
# include "parsing.h"

# include <stdarg.h>

struct	s_format_result
{
	int		blank_count;
	int		zero_count;
	bool	left_adjust;
	char	*string;
	int		str_len;
	char	*prefix;
	int		prefix_len;
};
typedef struct s_format_result	t_format_result;

void	print_int(t_array *output, t_arg arg, long l);
void	print_octal(t_array *output, t_arg arg, unsigned long o);
void	print_hex(t_array *output, t_arg arg, unsigned long o);
void	print_uint(t_array *output, t_arg arg, unsigned long l);
void	print_address(t_array *output, t_arg arg, unsigned long ul);
void	print_char(t_array *output, t_arg arg, unsigned char uc);
void	print_wchar(t_array *output, t_arg arg, wchar_t wc, int *error);
void	print_string(t_array *output, t_arg arg, char *string);
void	print_wstring(t_array *output, t_arg arg, wchar_t *string, int *error);
void	print_float(t_array *output, t_arg arg, long double value);
void	print_invalid(t_array *output, t_arg arg, va_list list, int *error);
void	print_percent(t_array *output, t_arg arg, va_list list, int *error);

void	append_n_chars(t_array *array, char c, int i);
void	format_string(t_array *output, t_format_result format);

#endif
