#ifndef __GENDEFS_H
#define __GENDEFS_H

/* Macros and Definitions */
#define REQUIRED_ARGS 5
#define DES_DATA_LENGTH_BITS 64
#define DES_DATA_LENGTH_BYTES (DES_DATA_LENGTH_BITS / 8)
#define DES_KEY_LENGTH_BITS 56
#define DES_KEY_LENGTH_BYTES (DES_KEY_LENGTH_BITS / 8)

#define SET_BIT(n) (1 << n)
#define DATA_BYTE_POS(n) (n / DES_KEY_LENGTH_BYTES)
#define DATA_BIT_POS_IN_BYTE(n) (n % DES_KEY_LENGTH_BYTES)

#endif