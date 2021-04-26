#include "des_encrypt.h"
#include "permutation.h"
#include "feistel.h"
#include "gendefs.h"

/**
 * @brief Top level DES encryption function.
 *
 * @param key Key input by user to be used in encryption process
 * @param data Data input by user to encrypt
 */
uint64_t encrypt(uint64_t key, uint64_t data)
{
	uint64_t data_copy = data;

	do_permutation(PERMUTATION_INITIAL, &data_copy);
	do_feistel_cipher(SCHEME_ENCRYPT, key, &data_copy);
	do_permutation(PERMUTATION_FINAL, &data_copy);

	return data_copy;
}
