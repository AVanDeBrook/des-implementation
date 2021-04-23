#ifndef __MAIN_H
#define __MAIN_H

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Macros and Definitions */
#define REQUIRED_ARGS 5
#define MAX_DATA_LENGTH 1024
#define DES_KEY_LENGTH_BITS 56
#define DES_KEY_LENGTH_BYTES (DES_KEY_LENGTH_BITS / 8)

#define SET_BIT(n) (1 << n)

/* Type, structure, enumerator definitions */
typedef enum scheme_operation_e {
	SCHEME_ENCRYPT,
	SCHEME_DECRYPT,
} scheme_operation_t;

typedef enum data_type_e {
	DATA_TYPE_FILE,
	DATA_TYPE_STRING,
} data_type_t;

typedef struct program_info_s {
	scheme_operation_t encrypt_or_decrypt;
	data_type_t file_or_string;
	char data[MAX_DATA_LENGTH];
	char key[DES_KEY_LENGTH_BYTES];
} program_info_t;

/* Function prototypes */
/**
 * @brief Parses command-line arguments and sets program info accordingly.
 *
 * @param cmd_info data structure containing program info @see program_info_t, program_info_s
 * @param argv command line arguments
 * @return int bitfield indicating errors with arguments. Value of 0 indicates no errors. Bit 0 = problem with encrypt/decrypt syntax, 1 = problem with key, 2 = problem with data type syntax, 3 = problem with data itself.
 */
int parse_args(program_info_t *cmd_info, char **argv);

#endif
