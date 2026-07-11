#include <stdio.h>
#include <stdlib.h>

/*
gcc dynallmem2.c -g -o dynallmem2
splint dynallmem2.c

*/

int main()
{
	struct contact 
	{
		char first_name[31];
		char last_name[31];
		char phone_number[16];
		char email_address[81];
	};
	struct contact *c;

	c = malloc(sizeof(struct contact));

	if (c == NULL)
	{
		fprintf(stderr, "Allocation failed!\n");
		exit(EXIT_FAILURE);
	}

	(void) puts("Struct contact memory allocated.");

	(void) free(c);

	exit(0);
}