#include <string.h>
#include <inttypes.h>

#include "key_schedule.h"
#include "gendefs.h"
#include "feistel.h"
#include "utils.h"

static const int key_permutation_table[DES_KEY_LENGTH_BITS] = {
	57, 49, 41, 33, 25, 17, 9,  1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4,
};

static const int key_rotation_table[FEISTEL_ROUNDS] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

static const int key_compression_table[COMPRESSED_KEY_LENGTH] = {
	14, 17, 11, 24, 1,  5,	3,  28, 15, 6,	21, 10, 23, 19, 12, 4,	26, 8,	16, 7,	27, 20, 13, 2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32,
};

static void divide_key(uint32_t *key_halves, uint64_t key);
static void rotate_key(uint32_t *key_half, int round);
static uint64_t compress_key(uint64_t key);
static void drop_parity_bits(uint64_t *key);
static void permute_key(uint64_t *key);

/**
 * @brief Processes the key (removes parity bits and permutes the key). @see key_permutation_table, drop_parity_bits, permute_key
 *
 * @param key Pointer to the user provided key.
 */
void process_key(uint64_t *key)
{
	drop_parity_bits(key);
	permute_key(key);
}

/**
 * @brief Chooses the round keys based off the given master key.
 *
 * @param subkeys Array of master keys. Should be one for each feistel cipher round i.e. 16.
 * @param key Master key to derive the subkeys from.
 */
void choose_round_key(uint64_t *subkeys, uint64_t key)
{
	uint32_t key_halves[2];
	uint64_t temp_key = 0;

	memset(key_halves, 0, sizeof(uint32_t) * 2);

	divide_key(key_halves, key);

	for (int i = 0; i < FEISTEL_ROUNDS; i++) {
		rotate_key(&key_halves[0], i);
		rotate_key(&key_halves[1], i);

		temp_key |= key_halves[1];
		temp_key <<= 28;
		temp_key |= key_halves[0];

		subkeys[i] = compress_key(temp_key);
	}
}

/**
 * @brief Divides a key into upper and lower halves.
 *
 * @param key_halves Array to store key halves to.
 * @param key Key to split into halves.
 */
static void divide_key(uint32_t *key_halves, uint64_t key)
{
	key_halves[0] = (key >> 8) & LOWER_HALF_KEY_MASK;
	key_halves[1] = ((key >> 8) & UPPER_HALF_KEY_MASK) >> 28;
}

/**
 * @brief Rotates the key half to the left 1 or 2 bits depending on the current round.
 *
 * @param key_half Half of the key to rotate (28-bits).
 * @param round Current round.
 */
static void rotate_key(uint32_t *key_half, int round)
{
	uint32_t mask = (1 << 28);
	for (int i = 0; i < key_rotation_table[round]; i++) {
		uint32_t msb = *key_half & mask;
		*key_half &= ~mask;
		*key_half <<= 1;
		*key_half |= (msb >> 28);
	}
}

/**
 * @brief Compresses the key from 56-bits to 48-bits.
 *
 * @param key Key to compress (56-bits).
 * @return uint64_t Compressed version of the key (48-bits).
 */
static uint64_t compress_key(uint64_t key)
{
	int key_bits[DES_KEY_EFFECTIVE_LENGTH_BITS], compressed_key_bits[COMPRESSED_KEY_LENGTH];
	uint64_t compressed_key = 0;

	memset(key_bits, 0, sizeof(int) * DES_KEY_EFFECTIVE_LENGTH_BITS);
	memset(compressed_key_bits, 0, sizeof(int) * COMPRESSED_KEY_LENGTH);

	int2binarray(key_bits, key, DES_KEY_EFFECTIVE_LENGTH_BITS);

	for (int i = 0; i < COMPRESSED_KEY_LENGTH; i++) {
		compressed_key_bits[i] = key_bits[key_compression_table[i] - 1];
	}

	binarray2int(&compressed_key, compressed_key_bits, COMPRESSED_KEY_LENGTH);

	return compressed_key;
}

/**
 * @brief Drops the parity bits (LSB of each byte).
 *
 * @param key Pointer to the key.
 */
static void drop_parity_bits(uint64_t *key)
{
	int key_bit_array[DES_KEY_LENGTH_BITS];
	uint64_t output_key = 0;

	memset(key_bit_array, 0, sizeof(int) * DES_KEY_LENGTH_BITS);

	int2binarray(key_bit_array, *key, DES_KEY_LENGTH_BITS);

	for (int i = 0; i < DES_KEY_LENGTH_BITS; i++) {
		if ((i + 1) % 8 != 0) {
			output_key <<= 1;
			output_key |= key_bit_array[i];
		}
	}

	*key = (output_key << 8);
}

/**
 * @brief Permutes the key according to the DES key permutation table.
 *
 * @param key Pointer to the key.
 */
static void permute_key(uint64_t *key)
{
	int key_bit_array[DES_KEY_LENGTH_BITS], output_key_array[DES_KEY_EFFECTIVE_LENGTH_BITS];
	uint64_t permuted_key = 0;

	memset(key_bit_array, 0, sizeof(int) * DES_KEY_LENGTH_BITS);
	memset(output_key_array, 0, sizeof(int) * DES_KEY_EFFECTIVE_LENGTH_BITS);

	int2binarray(key_bit_array, *key, DES_KEY_EFFECTIVE_LENGTH_BITS);

	for (int i = 0; i < DES_KEY_EFFECTIVE_LENGTH_BITS; i++) {
		output_key_array[i] = key_bit_array[key_permutation_table[i] - 1];
	}

	binarray2int(&permuted_key, output_key_array, DES_KEY_EFFECTIVE_LENGTH_BITS);

	*key = (permuted_key << 8);
}
