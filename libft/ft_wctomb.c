#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

#define HEADER_4_BYTES 240
#define HEADER_3_BYTES 224
#define HEADER_2_BYTES 192
#define HEADER_1_BYTE 128

#define MASK_BIT_0_TO_5 63
#define MASK_BIT_6_TO_10 1984
#define MASK_BIT_6_TO_11 4032
#define MASK_BIT_12_TO_15 61440
#define MASK_BIT_12_TO_17 258048
#define MASK_BIT_18_TO_20 1835008

int	ft_wctomb(char *buffer, wchar_t c)
{
	// 0 to 7 bits
	if (c <= 127 || (c <= 255 && MB_CUR_MAX == 1))
	{
		buffer[0] = (char) c;
		return 1;
	}
	// 8 to 11 bits
	else if (c <= 2047)
	{
		if (MB_CUR_MAX < 2)
			return 0;
		buffer[0] |= HEADER_2_BYTES;
		buffer[0] |= (c & MASK_BIT_6_TO_10) >> 6;
		buffer[1] |= HEADER_1_BYTE;
		buffer[1] |= (c & MASK_BIT_0_TO_5);
		return 2;
	}
	// 12 to 16 bits
	else if (c <= 65535)
	{
		if (MB_CUR_MAX < 3 || (c >= 0xD800 && c <= 0xDFFF))
			return 0;
		buffer[0] |= HEADER_3_BYTES;
		buffer[0] |= (c & MASK_BIT_12_TO_15) >> 12;
		buffer[1] |= HEADER_1_BYTE;
		buffer[1] |= (c & MASK_BIT_6_TO_11) >> 6;
		buffer[2] |= HEADER_1_BYTE;
		buffer[2] |= (c & MASK_BIT_0_TO_5);
		return 3;
	}
	// 17 to 21 bits
	else if (c <= 0x10FFFF)
	{
		if (MB_CUR_MAX < 4)
			return 0;
		buffer[0] |= HEADER_4_BYTES;
		buffer[0] |= (c & MASK_BIT_18_TO_20) >> 18;
		buffer[1] |= HEADER_1_BYTE;
		buffer[1] |= (c & MASK_BIT_12_TO_17) >> 12;
		buffer[2] |= HEADER_1_BYTE;
		buffer[2] |= (c & MASK_BIT_6_TO_11) >> 6;
		buffer[3] |= HEADER_1_BYTE;
		buffer[3] |= (c & MASK_BIT_0_TO_5);
		return 4;
	}
	return 0;
}