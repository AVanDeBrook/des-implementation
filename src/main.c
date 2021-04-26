#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

#include "main.h"
#include "des_encrypt.h"
#include "des_decrypt.h"
#include "key_schedule.h"
#include "utils.h"

static uint32_t parse_args(program_info_t *cmd_info, char **argv);

int main(int argc, char **argv)
{
	program_info_t cmd_args;

	memset(&cmd_args, 0, sizeof(program_info_t));

	// if (argc < REQUIRED_ARGS) {
	// 	fprintf(stderr, "Usage: %s [encrypt|decrypt] [key] [-f <file> | -s <string>]\n", argv[0]);
	// 	return 1;
	// }

	// if (parse_args(&cmd_args, argv) == 0) {
	// 	if (cmd_args.encrypt_or_decrypt == SCHEME_ENCRYPT) {
	// 		encrypt(cmd_args.key, cmd_args.data);
	// 	} else {
	// 		decrypt(cmd_args.key, cmd_args.data);
	// 	}
	// } else {
	// 	fprintf(stderr, "Problem with input syntax.\n");
	// 	return 1;
	// }

	const uint64_t key = 0x3030303030303030;
	const uint64_t plaintext = 0x3030303030303030;

	printf("Key: %016" PRIx64 "\n", key);
	printf("Plaintext: %016" PRIx64 "\n\n", plaintext);

	uint64_t encrypted_data = encrypt(key, plaintext);

	printf("Encrypted data: %016" PRIx64 "\n\n", encrypted_data);

	uint64_t decrypted_data = decrypt(key, encrypted_data);

	printf("Decrypted data: %016" PRIx64 "\n", decrypted_data);

	return 0;
}

/**
 * @brief Parses command-line arguments and sets program info accordingly.
 *
 * @param cmd_info data structure containing program info @see program_info_t, program_info_s
 * @param argv command line arguments
 * @return int bitfield indicating errors with arguments. Value of 0 indicates no errors. Bit 0 = problem with encrypt/decrypt syntax, 1 = problem with key, 2 =
 * problem with data type syntax, 3 = problem with data itself.
 */
static uint32_t parse_args(program_info_t *cmd_info, char **argv)
{
	uint32_t i, status_code = 0;
	FILE *data_file;

	if (strcmp(argv[1], "encrypt") == 0) {
		cmd_info->encrypt_or_decrypt = SCHEME_ENCRYPT;
	} else if (strcmp(argv[1], "decrypt") == 0) {
		cmd_info->encrypt_or_decrypt = SCHEME_DECRYPT;
	} else {
		status_code |= SET_BIT(0);
	}

	for (i = 0; i < DES_KEY_LENGTH_BYTES && argv[2][i] != 0; i++) {
		cmd_info->key <<= 8;
		cmd_info->key |= argv[2][i];
	}

	process_key(&(cmd_info->key));

	if (strcmp(argv[3], "-s") == 0) {
		cmd_info->file_or_string = DATA_TYPE_STRING;
	} else {
		status_code |= SET_BIT(2);
	}

	if (cmd_info->file_or_string == DATA_TYPE_FILE) {
		if (access(argv[4], F_OK)) {
			data_file = fopen(argv[4], "rb");
			fread(&(cmd_info->data), sizeof(uint64_t), 1, data_file);
			fclose(data_file);
		} else {
			SET_BIT(3);
		}
	} else if (cmd_info->file_or_string == DATA_TYPE_STRING) {
		for (i = 0; i < DES_DATA_LENGTH_BYTES && argv[4][i] != 0; i++) {
			cmd_info->data <<= 8;
			cmd_info->data |= argv[4][i];
		}
	} else {
		SET_BIT(3);
	}

	return status_code;
}
