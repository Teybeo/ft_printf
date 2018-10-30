/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:37:44 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/30 16:16:34 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

#include "libft.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

t_array	array_create(size_t elem_size, size_t count)
{
	t_array vec;

	vec.capacity = count * 2;
	vec.size = 0;
	vec.elem_size = elem_size;
	vec.data = malloc(vec.capacity * vec.elem_size);
	return (vec);
}

void	array_append(t_array *vec, void *data, size_t count)
{
//	assert(count > 0);
	if (count == 0)
		return ;
	if ((vec->size + count) > vec->capacity)
	{
		vec->data = ft_realloc(vec->data,
								vec->capacity * vec->elem_size,
								vec->capacity * vec->elem_size * 2);
		vec->capacity *= 2;
		return (array_append(vec, data, count));
	}
	ft_memcpy(vec->data + (vec->size * vec->elem_size), data,
			count * vec->elem_size);
	vec->size += count;
}

void	shrink_to_fit(t_array *vec)
{
	vec->data = ft_realloc(vec->data,
						vec->capacity * vec->elem_size,
						vec->size * vec->elem_size);
	vec->capacity = (size_t)vec->size;
}

void	print_stats(t_array arr, char *msg)
{
	printf("%s: %.2f KB,  %i / %zu * %zu B\n",
		msg,
		(arr.capacity * arr.elem_size) / 1024.f,
		arr.size, arr.capacity, arr.elem_size);
}
