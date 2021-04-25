#ifndef __PERMUTATION_H
#define __PERMUTATION_H

/* Type, structure, enumerator definitions */

typedef enum permutation_s {
	PERMUTATION_INITIAL,
	PERMUTATION_FINAL,
} permutation_t;

/* Function prototypes */

/**
 * @brief
 *
 * @param permutation
 * @param data
 * @return int
 */
int do_permutation(permutation_t permutation, uint64_t *data);

#endif