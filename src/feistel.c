#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "feistel.h"
#include "key_schedule.h"
#include "utils.h"

static const int expansion_table[SUBKEY_LENGTH] = {
	32, 1,	2,  3,	4,  5,	4,  5,	6,  7,	8,  9,	8,  9,	10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1,
};

static void feistel_cipher(uint64_t key, uint32_t half_block);
static void divide_block(uint32_t *half_blocks, uint64_t data_block);
static uint64_t expand_block(uint32_t half_block);
static uint64_t mix_key(uint64_t expanded_block, uint64_t round_key);

void do_feistel_cipher(uint64_t key, uint64_t *data)
{
	uint32_t half_blocks[2];

	divide_block(half_blocks, *data);

	feistel_cipher(key, half_blocks[0]);
	// feistel_cipher(key, half_blocks[1]);
}

static void feistel_cipher(uint64_t key, uint32_t half_block)
{
	int i;
	uint64_t round_key = 0, expanded_half_block = 0, mixed_key = 0;
	uint64_t subkeys[FEISTEL_ROUNDS];

	memset(subkeys, 0, sizeof(uint64_t) * FEISTEL_ROUNDS);

	choose_round_key(subkeys, key);

	for (i = 0; i < FEISTEL_ROUNDS; i++) {
		// printf("subkey %d:\t%016" PRIx64 "\n", i + 1, subkeys[i]);
		// expanded_half_block = expand_block(half_block);
		// mix
		// mixed_key = mix_key(expanded_half_block, subkeys[i]);
		// substitute
		// permute
	}
}

static void divide_block(uint32_t *half_blocks, uint64_t data_block)
{
	half_blocks[0] = data_block & LOWER_HALF_BLOCK_MASK;
	half_blocks[1] = data_block & UPPER_HALF_BLOCK_MASK;
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
}

// static void substitute()
// {
// }

// static void permute()
// {
// }
