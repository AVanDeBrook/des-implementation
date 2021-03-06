#ifndef __MAIN_H
#define __MAIN_H

/* Includes */
#include <stdint.h>

#include "gendefs.h"

/* Type, structure, enumerator definitions */
typedef enum data_type_e {
	DATA_TYPE_FILE,
	DATA_TYPE_STRING,
} data_type_t;

typedef struct program_info_s {
	scheme_operation_t encrypt_or_decrypt;
	data_type_t file_or_string;
	uint64_t data;
	uint64_t key;
} program_info_t;

#endif
