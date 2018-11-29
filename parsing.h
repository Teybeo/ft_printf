/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:08:22 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/26 20:35:45 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# include <stdbool.h>

struct	s_arg
{
	bool	alternat_form;
	bool	left_adjust;
	bool	pad_with_zero;
	bool	short_modifier;
	bool	double_short_modifier;
	bool	long_modifier;
	bool	has_precision;
	bool	uppercase_prefix;
	char	token;
	char	plus_sign;
	size_t	min_width;
	size_t	precision;
};

typedef	struct s_arg	t_arg;

t_arg	get_next_arg(const char *string, int *consumed);

bool	simple_token(t_arg *arg, const char **ptr);
bool	integer_tokens(t_arg *arg, const char **ptr);
bool	char_string_tokens(t_arg *arg, const char **ptr);
bool	modifiers_tokens(t_arg *arg, const char **ptr);
bool	zero_tokens(t_arg *arg, const char **ptr);
bool	positive_prefix(t_arg *arg, const char **ptr);
bool	hashtag_token(t_arg *arg, const char **ptr);
bool	precision_parsing(t_arg *arg, const char **ptr);
bool	field_width_parsing(t_arg *arg, const char **ptr);
bool	left_adjust_token(t_arg *arg, const char **ptr);

#endif
