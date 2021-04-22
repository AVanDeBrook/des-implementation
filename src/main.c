#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("Usage: %s [encrypt|decrypt] [key] [file|string]\n", argv[0]);
        return 1;
    }

    return 0;
}
