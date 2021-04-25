#ifndef __FEISTEL_H
#define __FEISTEL_H

#include <stdint.h>

#include "gendefs.h"

#define HALFBLOCK_LENGTH (DES_DATA_LENGTH_BYTES / 2)
#define FEISTEL_ROUNDS 16
#define SUBKEY_LENGTH 48

int do_feistel_cipher(uint64_t key, uint64_t *data);

#endif