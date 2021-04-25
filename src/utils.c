#include <stdio.h>
#include <stdint.h>

#include "utils.h"

/**
 * @brief Converts a 64-bit integer to a binary array.
 *
 * @param bin_array Array to store binary info to. Assumes a length of at least 64.
 * @param num Integer to convert to binary.
 */
void int2binarray(int *bin_array, uint64_t num, const int length)
{
	for (int i = 0; i < length; i++) {
		bin_array[(length - 1) - i] = num & 1;
		num >>= 1;
	}
}

/**
 * @brief Converst a binary array back to a 64-bit integer.
 *
 * @param num Integer result
 * @param bin_array Array of binary data.
 */
void binarray2int(uint64_t *num, int *bin_array, const int length)
{
	for (int i = 0; i < length; i++) {
		*num <<= 1;
		*num |= bin_array[i];
	}
}
