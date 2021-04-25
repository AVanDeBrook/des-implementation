#ifndef __DES_ENCRYPT_H
#define __DES_ENCRYPT_H

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Function prototypes */
/**
 * @brief Top level DES encryption function.
 *
 * @param key key input by user to be used in encryption process
 * @param data data input by user to encrypt
 * @return int
 */
int encrypt(uint64_t key, uint64_t data);

#endif
