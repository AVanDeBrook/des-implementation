#include "feistel.h"

static const int expansion_table[SUBKEY_LENGTH] = {
	32, 1,	2,  3,	4,  5,	4,  5,	6,  7,	8,  9,	8,  9,	10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1,
};

static const int key_rotation_table[FEISTEL_ROUNDS] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

static const int key_compression_table[DES_KEY_LENGTH_BITS] = {
	14, 17, 11, 24, 1,  5,	3,  28, 15, 6,	21, 10, 23, 19, 12, 4,	26, 8,	16, 7,	27, 20, 13, 2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32,
};

static void choose_subkey(uint64_t key, int round);
static void rotate_key(uint64_t key, int n);
static void compress_key(uint64_t *key);
static void expand(uint32_t half_block, uint64_t expanded_block);

int do_feistel_cipher(uint64_t key, uint64_t *data)
{
	int i;
	uint32_t key_halves[2];

	for (i = 0; i < FEISTEL_ROUNDS; i++) {
		key_halves[0] = key & ((1 << 28) - 1);
		// expand
		// expand(expanded_block, half_blocks[0], subkey);
		// mix
		// substitute
		// permute
	}

	return 0;
}

static void choose_subkey(uint64_t key, int round)
{
}

static void rotate_key(uint64_t key, int n)
{
}

static void compress_key(uint64_t *key)
{
}

static void expand(uint32_t half_block, uint64_t expanded_block)
{
}
