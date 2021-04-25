#ifndef __KEY_SCHEDULE_H
#define __KEY_SCHEDULE_H

/* Includes */
#include <stdint.h>

/* Macros and Definitions */
#define LOWER_HALF_KEY_MASK 0x000000000fffffff
#define UPPER_HALF_KEY_MASK 0x00fffffff0000000
#define COMPRESSED_KEY_LENGTH 48

/* Function prototypes */
void process_key(uint64_t *key);
void choose_round_key(uint64_t *subkeys, uint64_t key);

#endif
