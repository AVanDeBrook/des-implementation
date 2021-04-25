#include <inttypes.h>

#include "des_encrypt.h"
#include "permutation.h"
#include "feistel.h"
#include "utils.h"

/**
 * @brief Top level DES encryption function.
 *
 * @param key Key input by user to be used in encryption process
 * @param data Data input by user to encrypt
 * @return int Status of function execution. Value of 0 indicates no errors.
 */
int encrypt(uint64_t key, uint64_t data)
{
	// perform initial permutation
	do_permutation(PERMUTATION_INITIAL, &data);
	// 16 feistel cipher rounds

	// perform final permutation
	do_permutation(PERMUTATION_FINAL, &data);
	return 0;
}
