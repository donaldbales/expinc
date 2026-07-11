#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc dynallmem3.c -g -o dynallmem3
splint dynallmem3.c

*/

int main()
{
	const size_t SIZEOF_FIRST_NAME = 31;
	const size_t SIZEOF_LAST_NAME = 31;
	const size_t SIZEOF_PHONE_NUMBER = 16;
	const size_t SIZEOF_EMAIL_ADDRESS = 81;
	struct contact 
	{
		char *first_name;
		char *last_name;
		char *phone_number;
		char *email_address;
	};
	struct contact *c;

	c = malloc(sizeof(struct contact));
	if (c == NULL)
	{
		fprintf(stderr, "Allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		(void) puts("Struct contact memory allocated.");
	}

	c->first_name = malloc(SIZEOF_FIRST_NAME);
	if (c->first_name == NULL)
	{
		fprintf(stderr, "Allocation of c->first_name failed!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		(void) puts("Struct c->first_name memory allocated.");
	}

	c->last_name = malloc(SIZEOF_LAST_NAME);
	if (c->last_name == NULL)
	{
		fprintf(stderr, "Allocation of c->last_name failed!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		(void) puts("Struct c->last_name memory allocated.");
	}

	c->phone_number = malloc(SIZEOF_PHONE_NUMBER);
	if (c->phone_number == NULL)
	{
		fprintf(stderr, "Allocation of c->phone_number failed!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		(void) puts("Struct c->phone_number memory allocated.");
	}

	c->email_address = malloc(SIZEOF_EMAIL_ADDRESS);
	if (c->email_address == NULL)
	{
		fprintf(stderr, "Allocation of c->email_address failed!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		(void) puts("Struct c->email_address memory allocated.");
	}

	/* now let's try using it */

	strncpy(c->first_name, "First Name First Name First Name First Name", SIZEOF_FIRST_NAME);
	strncpy(c->last_name, "Last Name", SIZEOF_LAST_NAME);
	strncpy(c->phone_number, "Phone Number Phone Number", SIZEOF_PHONE_NUMBER);
	strncpy(c->email_address, "Email Address", SIZEOF_EMAIL_ADDRESS);

	(void) free(c->email_address);
	(void) free(c->phone_number);
	(void) free(c->last_name);
	(void) free(c->first_name);

	(void) free(c);

	exit(0);
}