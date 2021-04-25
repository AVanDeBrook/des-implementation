#ifndef __SUBSTITUTE_H
#define __SUBSTITUTE_H

/* Includes */
#include <stdint.h>

/* Macros and Definitions */
#define S_BOX_INPUT_MASK 0x3f
#define S_BOX_INPUTS 8

/* Function prototypes */
uint32_t do_substitution(uint64_t mixed_key);

#endif
