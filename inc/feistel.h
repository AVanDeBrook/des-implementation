#ifndef __FEISTEL_H
#define __FEISTEL_H

/* Includes */
#include <stdint.h>

#include "gendefs.h"

/* Macros and Definitions */
#define HALFBLOCK_LENGTH (DES_DATA_LENGTH_BYTES / 2)
#define FEISTEL_ROUNDS 16
#define SUBKEY_LENGTH 48
#define EXPANDED_BLOCK_LENGTH 48
#define LOWER_HALF_BLOCK_MASK ((uint64_t)(0x00000000ffffffff))
#define UPPER_HALF_BLOCK_MASK ((uint64_t)(0xffffffff00000000))

/* Function prototypes */
void do_feistel_cipher(scheme_operation_t mode, uint64_t key, uint64_t *data);

#endif
