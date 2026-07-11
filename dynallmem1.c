#include <stdio.h>
#include <stdlib.h>

/*
gcc dynallmem1.c -g -o dynallmem1
splint dynallmem1.c

*/

int main()
{
	char *buffer;

	buffer = malloc(2048);

	if (buffer == NULL)
	{
		fprintf(stderr, "buffer allocation of 2048 bytes failed\n");
		exit(EXIT_FAILURE);
	}

	(void) puts("2K buffer allocated");

	(void) free(buffer);

	exit(0);
}