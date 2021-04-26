#include "des_decrypt.h"
#include "permutation.h"
#include "feistel.h"
#include "gendefs.h"

/**
 * @brief
 *
 * @param key
 * @param data
 */
uint64_t decrypt(uint64_t key, uint64_t data)
{
	uint64_t data_copy = data;

	do_permutation(PERMUTATION_INITIAL, &data_copy);
	do_feistel_cipher(SCHEME_DECRYPT, key, &data_copy);
	do_permutation(PERMUTATION_FINAL, &data_copy);

	return data_copy;
}
