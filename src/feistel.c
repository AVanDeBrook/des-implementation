#include <string.h>
#include <inttypes.h>

#include "feistel.h"
#include "key_schedule.h"
#include "substitute.h"
#include "gendefs.h"
#include "utils.h"

static const int expansion_table[SUBKEY_LENGTH] = {
	32, 1,	2,  3,	4,  5,	4,  5,	6,  7,	8,  9,	8,  9,	10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1,
};

static const int p_box_permutation_table[DES_DATA_LENGTH_BITS / 2] = { 16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
								       2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25 };

static uint32_t feistel_cipher(uint64_t key, uint32_t half_block);
static void divide_block(uint32_t *half_blocks, uint64_t data_block);
static uint64_t recombine_blocks(uint32_t *half_blocks);
static uint64_t expand_block(uint32_t half_block);
static uint64_t mix_key(uint64_t expanded_block, uint64_t round_key);
static uint32_t permute_output(uint32_t output_data);

void do_feistel_cipher(uint64_t key, uint64_t *data)
{
	uint32_t half_blocks[2];

	divide_block(half_blocks, *data);

	half_blocks[0] = feistel_cipher(key, half_blocks[0]);
	half_blocks[1] = feistel_cipher(key, half_blocks[1]);

	*data = recombine_blocks(half_blocks);
}

static uint32_t feistel_cipher(uint64_t key, uint32_t half_block)
{
	int i;
	uint64_t round_key = 0, expanded_half_block = 0, mixed_key = 0;
	uint64_t subkeys[FEISTEL_ROUNDS];
	uint32_t output_data = 0;

	memset(subkeys, 0, sizeof(uint64_t) * FEISTEL_ROUNDS);

	choose_round_key(subkeys, key);

	for (i = 0; i < FEISTEL_ROUNDS; i++) {
		expanded_half_block = expand_block(half_block);
		mixed_key = mix_key(expanded_half_block, subkeys[i]);
		output_data = do_substitution(mixed_key);
		half_block = permute_output(output_data);
	}

	return half_block;
}

static void divide_block(uint32_t *half_blocks, uint64_t data_block)
{
	half_blocks[0] = data_block & LOWER_HALF_BLOCK_MASK;
	half_blocks[1] = data_block & UPPER_HALF_BLOCK_MASK;
}

static uint64_t recombine_blocks(uint32_t *half_blocks)
{
	uint64_t recombined_data = 0;

	recombined_data |= half_blocks[1];
	recombined_data <<= 32;
	recombined_data |= half_blocks[0];

	return recombined_data;
}

static uint64_t expand_block(uint32_t half_block)
{
	int half_block_bits[DES_DATA_LENGTH_BITS / 2], expanded_block_bits[EXPANDED_BLOCK_LENGTH];
	uint64_t expanded_block = 0;

	memset(half_block_bits, 0, DES_DATA_LENGTH_BITS / 2);
	memset(expanded_block_bits, 0, EXPANDED_BLOCK_LENGTH);

	int2binarray(half_block_bits, half_block, DES_DATA_LENGTH_BITS / 2);

	for (int i = 0; i < DES_DATA_LENGTH_BITS / 2; i++) {
		expanded_block_bits[i] = half_block_bits[expansion_table[i] - 1];
	}

	binarray2int(&expanded_block, expanded_block_bits, EXPANDED_BLOCK_LENGTH);

	return expanded_block;
}

static uint64_t mix_key(uint64_t expanded_block, uint64_t round_key)
{
	return expanded_block ^ round_key;
}

static uint32_t permute_output(uint32_t output_data)
{
	int data_bits[DES_DATA_LENGTH_BITS / 2], permuted_bits[DES_DATA_LENGTH_BITS / 2];
	uint64_t permuted_data = 0;

	memset(data_bits, 0, sizeof(int) * (DES_DATA_LENGTH_BITS / 2));
	memset(permuted_bits, 0, sizeof(int) * (DES_DATA_LENGTH_BITS / 2));

	int2binarray(data_bits, output_data, DES_DATA_LENGTH_BITS / 2);

	for (int i = 0; i < DES_DATA_LENGTH_BITS / 2; i++) {
		permuted_bits[i] = data_bits[p_box_permutation_table[i] - 1];
	}

	binarray2int(&permuted_data, permuted_bits, DES_DATA_LENGTH_BITS / 2);

	return (uint32_t)permuted_data;
}
