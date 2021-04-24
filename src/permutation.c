#include <stdio.h>

#include "permutation.h"
#include "gendefs.h"
#include "utils.h"

static const unsigned char initial_permutation_table[DES_DATA_LENGTH_BITS] = {
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9,  1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7,
};

static const unsigned char final_permutation_table[DES_DATA_LENGTH_BITS] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9,  49, 17, 57, 25,
};

/**
 * @brief
 *
 * @param permutation
 * @param data
 * @return int
 */
int do_permutation(permutation_t permutation, unsigned char *data)
{
	int i, j, status_code = 0;
	const unsigned char *permutation_table;
	unsigned char output_data[DES_DATA_LENGTH_BYTES];
	int input_data_bits[DES_DATA_LENGTH_BITS], output_data_bits[DES_DATA_LENGTH_BITS];

	if (permutation == PERMUTATION_INITIAL) {
		permutation_table = initial_permutation_table;
	} else if (permutation == PERMUTATION_FINAL) {
		permutation_table = final_permutation_table;
	} else {
		status_code |= SET_BIT(0);
	}

	if (status_code == 0) {
		for (i = 0; i < DES_DATA_LENGTH_BYTES; i++) {
			for (j = 0; j < 8; j++) {
				input_data_bits[i * 8 + (7 - j)] = (data[i] & (1 << j)) >> j;
			}
		}

		for (i = 0; i < DES_DATA_LENGTH_BITS; i++) {
			output_data_bits[i] = input_data_bits[permutation_table[i] - 1];
		}

		for (i = 0; i < DES_DATA_LENGTH_BYTES; i++) {
			unsigned char temp = 0;
			for (j = 0; j < 8; j++) {
				temp <<= 1;
				temp |= output_data_bits[i * 8 + j];
			}
			output_data[i] = temp;
		}

		for (i = 0; i < DES_DATA_LENGTH_BYTES; i++) {
			data[i] = output_data[i];
		}
	}

	return status_code;
}
