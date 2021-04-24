#include <stdio.h>

#include "utils.h"
#include "gendefs.h"

void print_data(unsigned char *data)
{
	for (int i = 0; i < DES_DATA_LENGTH_BYTES; i++) {
		printf("%02x ", data[i]);
	}
	printf("\n");
}
