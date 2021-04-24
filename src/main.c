#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "main.h"
#include "des_encrypt.h"
#include "utils.h"

/**
 * @brief Parses command-line arguments and sets program info accordingly.
 *
 * @param cmd_info data structure containing program info @see program_info_t, program_info_s
 * @param argv command line arguments
 * @return int bitfield indicating errors with arguments. Value of 0 indicates no errors. Bit 0 = problem with encrypt/decrypt syntax, 1 = problem with key, 2 =
 * problem with data type syntax, 3 = problem with data itself.
 */
static int parse_args(program_info_t *cmd_info, char **argv);

int main(int argc, char **argv)
{
	program_info_t cmd_args;

	if (argc < REQUIRED_ARGS) {
		fprintf(stderr, "Usage: %s [encrypt|decrypt] [key] [-f <file> | -s <string>]\n", argv[0]);
		return 1;
	}

	if (parse_args(&cmd_args, argv) == 0) {
		if (cmd_args.encrypt_or_decrypt == SCHEME_ENCRYPT) {
			encrypt(cmd_args.key, cmd_args.data);
		}
	} else {
		fprintf(stderr, "Problem with input syntax.\n");
		return 1;
	}

	return 0;
}

static int parse_args(program_info_t *cmd_info, char **argv)
{
	int i, status_code = 0;
	FILE *data_file;

	if (strcmp(argv[1], "encrypt") == 0) {
		cmd_info->encrypt_or_decrypt = SCHEME_ENCRYPT;
	} else if (strcmp(argv[1], "decrypt") == 0) {
		cmd_info->encrypt_or_decrypt = SCHEME_DECRYPT;
	} else {
		status_code |= SET_BIT(0);
	}

	for (i = 0; i < DES_KEY_LENGTH_BYTES && argv[2][i] != 0; i++) {
		cmd_info->key[i] = argv[2][i];
	}

	if (strcmp(argv[3], "-f") == 0) {
		cmd_info->file_or_string = DATA_TYPE_FILE;
	} else if (strcmp(argv[3], "-s") == 0) {
		cmd_info->file_or_string = DATA_TYPE_STRING;
	} else {
		status_code |= SET_BIT(2);
	}

	if (cmd_info->file_or_string == DATA_TYPE_FILE) {
		if (access(argv[4], F_OK)) {
			data_file = fopen(argv[4], "rb");
			fread(cmd_info->data, sizeof(char), DES_DATA_LENGTH_BYTES, data_file);
			fclose(data_file);
		} else {
			SET_BIT(3);
		}
	} else if (cmd_info->file_or_string == DATA_TYPE_STRING) {
		for (i = 0; i < DES_DATA_LENGTH_BYTES && argv[4] != 0; i++) {
			cmd_info->data[i] = argv[4][i];
		}
	} else {
		SET_BIT(3);
	}

	return status_code;
}
