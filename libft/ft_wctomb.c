/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctomb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:23:39 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/29 17:03:34 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

#define HEADER_4_BYTES (char)240
#define HEADER_3_BYTES (char)224
#define HEADER_2_BYTES (char)192
#define HEADER_1_BYTE (char)128

#define MASK_BIT_0_TO_5 63
#define MASK_BIT_6_TO_10 1984
#define MASK_BIT_6_TO_11 4032
#define MASK_BIT_12_TO_15 61440
#define MASK_BIT_12_TO_17 258048
#define MASK_BIT_18_TO_20 1835008

/*
** Wide char to multi-byte (utf-8)
** MB_CUR_MAX depends on the current locale
** 0  to 7  bits = 1 byte
** 8  to 11 bits = 2 bytes
** 12 to 17 bits = 3 bytes
** 17 to 21 bits = 4 bytes
** If MB_CUR_MAX == 1, the first byte can hold the full 0 to 8 bits range
** Return 0 if c < 0 (need separate test because negative wchar_t can overflow)
*/

char	ft_wctomb(char *buffer, wchar_t c)
{
	if (c <= 127 || (c <= 255 && MB_CUR_MAX == 1))
		return ((buffer[0] = (char)c) | 1) && (c >= 0);
	else if (c <= 2047)
	{
		buffer[0] = HEADER_2_BYTES | (c & MASK_BIT_6_TO_10) >> 6;
		buffer[1] = HEADER_1_BYTE | (c & MASK_BIT_0_TO_5);
		return (2 * (MB_CUR_MAX >= 2));
	}
	else if (c <= 65535)
	{
		buffer[0] = HEADER_3_BYTES | (c & MASK_BIT_12_TO_15) >> 12;
		buffer[1] = HEADER_1_BYTE | (c & MASK_BIT_6_TO_11) >> 6;
		buffer[2] = HEADER_1_BYTE | (c & MASK_BIT_0_TO_5);
		return (3 * (MB_CUR_MAX >= 3 && (c < 0xD800 || c > 0xDFFF)));
	}
	else if (c <= 0x10FFFF)
	{
		buffer[0] = HEADER_4_BYTES | (c & MASK_BIT_18_TO_20) >> 18;
		buffer[1] = HEADER_1_BYTE | (c & MASK_BIT_12_TO_17) >> 12;
		buffer[2] = HEADER_1_BYTE | (c & MASK_BIT_6_TO_11) >> 6;
		buffer[3] = HEADER_1_BYTE | (c & MASK_BIT_0_TO_5);
		return (4 * (MB_CUR_MAX >= 4));
	}
	return (0);
}
