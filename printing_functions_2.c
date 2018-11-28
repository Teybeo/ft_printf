/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_functions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:22:10 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/28 15:22:10 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printing.h"

#include <limits.h>
#include <libft.h>

void	print_wchar(t_array *output, t_arg arg, wchar_t wc, int *error)
{
	static char	buffer[MB_LEN_MAX];
	int			blank_count;
	char		pad_char;
	int			byte_count;

	pad_char = (arg.pad_with_zero && !arg.left_adjust) ? '0' : ' ';
	byte_count = ft_wctomb(buffer, wc);
	if (byte_count == 0)
	{
		*error = true;
		return ;
	}
	blank_count = ft_max(arg.min_width - byte_count, 0);
	if (arg.left_adjust == false)
		append_n_chars(output, pad_char, blank_count);
	array_append(output, buffer, byte_count);
	if (arg.left_adjust)
		append_n_chars(output, pad_char, blank_count);
}

void	print_string(t_array *output, t_arg arg, char *string)
{
	int		i;
	int		written_char_count;
	size_t	str_len;
	int		blank_count;
	char	pad_char;

	pad_char = (arg.pad_with_zero && !arg.left_adjust) ? '0' : ' ';
	string = (string) ? string : "(null)";
	str_len = ft_strlen(string);
	written_char_count = str_len;
	if (arg.has_precision && arg.precision < str_len)
		written_char_count = arg.precision;
	blank_count = ft_max(arg.min_width - written_char_count, 0);
	if (arg.left_adjust == false)
		append_n_chars(output, pad_char, blank_count);
	i = 0;
	while (string[i] != 0 && i < written_char_count)
	{
		array_append(output, string + i, 1);
		i++;
	}
	if (arg.left_adjust)
		append_n_chars(output, pad_char, blank_count);
}

/*
** For wchar* strings, the precision and width are the max/min count of BYTES
** that can be written, not the actual character count
** If we reach an invalid sequence, dont print anything
*/

void	print_wstring(t_array *output, t_arg arg, wchar_t *string, int *error)
{
	int		i;
	size_t	max_written_byte_count;
	size_t	written_byte_count;
	int		blank_count;
	char	pad_char;
	char	buffer[MB_LEN_MAX];
	int		byte_count;

	pad_char = (arg.pad_with_zero && !arg.left_adjust) ? '0' : ' ';
	string = (string) ? string : L"(null)";
	if (arg.has_precision)
		max_written_byte_count = ft_get_fitting_mb_size(string, arg.precision, error);
	else
		max_written_byte_count = ft_get_mb_size(string, error);
	if (*error)
		return ;
	blank_count = ft_max(arg.min_width - max_written_byte_count, 0);
	if (arg.left_adjust == false)
		append_n_chars(output, pad_char, blank_count);
	i = 0;
	written_byte_count = 0;
	while (string[i] != 0 && written_byte_count < max_written_byte_count)
	{
		byte_count = ft_wctomb(buffer, string[i]);
		*error = (byte_count == 0);
		if (*error)
			return ;
		if (written_byte_count + byte_count > max_written_byte_count)
			break ;
		written_byte_count += byte_count;
		array_append(output, buffer, byte_count);
		i++;
	}
	if (arg.left_adjust)
		append_n_chars(output, pad_char, blank_count);
}

void	print_char(t_array *output, t_arg arg, unsigned char uc)
{
	int		blank_count;
	char	pad_char;

	pad_char = (arg.pad_with_zero && !arg.left_adjust) ? '0' : ' ';
	blank_count = ft_max(arg.min_width - 1, 0);
	if (arg.left_adjust == false)
		append_n_chars(output, pad_char, blank_count);
	array_append(output, &uc, 1);
	if (arg.left_adjust)
		append_n_chars(output, pad_char, blank_count);
}
