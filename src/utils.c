#include <stdio.h>
#include <stdint.h>

#include "utils.h"

/**
 * @brief Converts a 64-bit integer to a binary array.
 *
 * @param bin_array Array to store binary info to. Assumes a length of at least 64.
 * @param num Integer to convert to binary.
 */
void int2binarray(int *bin_array, uint64_t num)
{
	for (int i = 0; i < 64; i++) {
		bin_array[63 - i] = num & 1;
		num >>= 1;
	}
}

/**
 * @brief Converst a binary array back to a 64-bit integer.
 *
 * @param num Integer result
 * @param bin_array Array of binary data. Assumes a length of at least 64.
 */
void binarray2int(uint64_t *num, int *bin_array)
{
	for (int i = 0; i < 64; i++) {
		*num <<= 1;
		*num |= bin_array[i];
	}
}
