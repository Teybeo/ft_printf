/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:53:46 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/28 15:25:51 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSING_H
# define PROCESSING_H

# include "array.h"
# include "parsing.h"

# include <stdarg.h>

void	process_arg2(t_array *output, t_arg arg, va_list list, int *error);

void	print_d(t_array *output, t_arg arg, va_list list, int *error);
void	print_u(t_array *output, t_arg arg, va_list list, int *error);
void	print_o(t_array *output, t_arg arg, va_list list, int *error);
void	print_x(t_array *output, t_arg arg, va_list list, int *error);
void	print_p(t_array *output, t_arg arg, va_list list, int *error);

void	print_c(t_array *output, t_arg arg, va_list list, int *error);
void	print_wc(t_array *output, t_arg arg, va_list list, int *error);
void	print_s(t_array *output, t_arg arg, va_list list, int *error);
void	print_ws(t_array *output, t_arg arg, va_list list, int *error);
void	print_f(t_array *output, t_arg arg, va_list list, int *error);

#endif
