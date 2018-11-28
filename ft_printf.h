/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:26:41 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/28 17:54:32 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

typedef struct s_array	t_array;

int		ft_printf(const char *string, ...);
int		ft_sprintf(char *str, const char *format, ...);
int		ft_snprintf(char *str, size_t size, const char *format, ...);
int		ft_asprintf(char **str, const char *format, ...);
int		ft_dprintf(int fd, const char *string, ...);

int		ft_vprintf(const char *string, va_list list);
int		ft_vsprintf(char *str, const char *format, va_list list);
int		ft_vsnprintf(char *str, size_t size, const char *format, va_list list);
int		ft_vasprintf(char **str, const char *format, va_list list);
int		ft_vdprintf(int fd, const char *string, va_list list);

int		real_printf(t_array *output, const char *format, va_list list);

#endif
