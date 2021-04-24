#include "des_encrypt.h"
#include "permutation.h"
#include "utils.h"

/**
 * @brief Top level DES encryption function.
 *
 * @param key key input by user to be used in encryption process
 * @param data data input by user to encrypt
 * @return int
 */
int encrypt(char *key, unsigned char *data)
{
	// perform initial permutation
	do_permutation(PERMUTATION_INITIAL, data);
	// 16 feistel cipher rounds

	// perform final permutation
	do_permutation(PERMUTATION_FINAL, data);
	return 0;
}
