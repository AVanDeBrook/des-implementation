#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "key_schedule.h"
#include "gendefs.h"
#include "utils.h"

static const int key_permutation_table[DES_KEY_LENGTH_BITS] = {
	57, 49, 41, 33, 25, 17, 9,  1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4,
};

static void drop_parity_bits(uint64_t *key);
static void permute_key(uint64_t *key);

void process_key(uint64_t *key)
{
	drop_parity_bits(key);
	permute_key(key);
}

static void drop_parity_bits(uint64_t *key)
{
	int key_bit_array[DES_KEY_LENGTH_BITS];
	uint64_t output_key = 0;

	int2binarray(key_bit_array, *key);

	for (int i = 0; i < DES_KEY_LENGTH_BITS; i++) {
		if ((i + 1) % 8 != 0) {
			output_key <<= 1;
			output_key |= key_bit_array[i];
		}
	}

	*key = (output_key << 8);
}

static void permute_key(uint64_t *key)
{
	int key_bit_array[DES_KEY_LENGTH_BITS], output_key_array[DES_KEY_EFFECTIVE_LENGTH_BITS];
	uint64_t permuted_key = 0;

	memset(key_bit_array, 0, sizeof(int));
	memset(output_key_array, 0, sizeof(int));

	int2binarray(key_bit_array, *key);

	for (int i = 0; i < DES_KEY_EFFECTIVE_LENGTH_BITS; i++) {
		output_key_array[i] = key_bit_array[key_permutation_table[i] - 1];
	}

	for (int i = 0; i < DES_KEY_EFFECTIVE_LENGTH_BITS; i++) {
		permuted_key <<= 1;
		permuted_key |= output_key_array[i];
	}

	*key = (permuted_key << 8);
}
