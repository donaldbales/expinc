#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc fixed_length_ascii_file.c -g -o fixed_length_ascii_file
splint +posixlib fixed_length_ascii_file.c
fixed_length_ascii_file fixed_length_ascii_file.bin
hexdump -C fixed_length_ascii_file.txt 
*/

struct RECORD 
{
	char first_name[31];
	char last_name[31];
	char birth_date[11];
	char phone_number[16];
	char email_address[81];
	char nl;
};

int main(int argc, char const *argv[])
{
	FILE *file = NULL;
	ssize_t n = -1;
	struct RECORD r, w;
	int i;
	if (argc != 2)
	{
		fprintf(stderr, "Usage: fixed_length_ascii_file [FILE]\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "w");
	if (file == NULL)
	{
		fprintf(stderr, "open file %s errno %d", argv[1], errno);
		exit(EXIT_FAILURE);
	}

	for (i=0; i<(int)sizeof(w.first_name); i++)
		w.first_name[i] = '\0';
	for (i=0; i<(int)sizeof(w.last_name); i++)
		w.last_name[i] = '\0';
	for (i=0; i<(int)sizeof(w.birth_date); i++)
		w.birth_date[i] = '\0';
	for (i=0; i<(int)sizeof(w.phone_number); i++)
		w.phone_number[i] = '\0';
	for (i=0; i<(int)sizeof(w.email_address); i++)
		w.email_address[i] = '\0';
	w.nl = '\n';
	strcpy(w.first_name, "Donald");
	strcpy(w.last_name, "Bales");
	strcpy(w.birth_date, "01/01/1980");
	strcpy(w.phone_number, "630-555-1212");
	strcpy(w.email_address, "don@donaldbales.com");

	(void) fwrite(((void *)&w), 1, sizeof(w), file);

	if (fclose(file) == EOF)
	{
		fprintf(stderr, "close file %s errno %d\n", argv[1], errno);
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "open file %s errno %d\n", argv[1], errno);
		exit(EXIT_FAILURE);
	}

	n = fread(((void *)&r), 1, sizeof(r), file);
	if (n == -1)
	{
		fprintf(stderr, "read file error %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	printf("First name: %s\n", r.first_name);
	printf("Last name: %s\n", r.last_name);
	printf("Birth date: %s\n", r.birth_date);
	printf("Phone number: %s\n", r.phone_number);
	printf("Email Address: %s\n", r.email_address);

	(void) fclose(file);

	return 0;
}