#ifndef __UTILS_H
#define __UTILS_H

/* Includes */
#include <stdint.h>

/* Function prototypes */
void int2binarray(int *bin_array, uint64_t num, const int length);
void int2bytearray(uint8_t *byte_array, uint64_t num, const int length);
void binarray2int(uint64_t *num, int *bin_array, const int length);

#endif
