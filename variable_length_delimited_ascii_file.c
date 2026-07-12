#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc variable_length_delimited_ascii_file.c -g -o variable_length_delimited_ascii_file
splint +posixlib variable_length_delimited_ascii_file.c
variable_length_delimited_ascii_file variable_length_delimited_ascii_file.tsv
hexdump -C variable_length_delimited_ascii_file.tsv
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
	char buffer[sizeof(struct RECORD)];
	FILE *fo = NULL;
	FILE *fi = NULL;
	struct RECORD r, w;
	struct RECORD *p;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: variable_length_delimited_ascii_file [FILE]\n");
		exit(EXIT_FAILURE);
	}

	fo = fopen(argv[1], "w");
	if (fo == NULL)
	{
		fprintf(stderr, "open file %s errno %d", argv[1], errno);
		exit(EXIT_FAILURE);
	}

	strcpy(w.first_name, "Donald");
	strcpy(w.last_name, "Bales");
	strcpy(w.birth_date, "01/01/1980");
	strcpy(w.phone_number, "630-555-1212");
	strcpy(w.email_address, "don@donaldbales.com");

	printf("First name: %s\n", w.first_name);
	printf("Last name: %s\n", w.last_name);
	printf("Birth date: %s\n", w.birth_date);
	printf("Phone number: %s\n", w.phone_number);
	printf("Email Address: %s\n", w.email_address);

	(void) fprintf(fo, "%s\t%s\t%s\t%s\t%s\n", \
		w.first_name, w.last_name, w.birth_date, w.phone_number, w.email_address);
	if (fclose(fo) == -1)
	{
		fprintf(stderr, "close file %s errno %d\n", argv[1], errno);
		exit(EXIT_FAILURE);
	}

	fi = fopen(argv[1], "r");
	if (fi == NULL)
	{
		fprintf(stderr, "open file %s errno %d\n", argv[1], errno);
		exit(EXIT_FAILURE);
	}

	printf("Buffer size: %ld\n", sizeof(buffer));
	fgets(buffer, sizeof(buffer), fi);
	printf("Bytes read: %ld\n", strlen(buffer));
	p = &r;
	sscanf(buffer, "%s\t%s\t%s\t%s\t%s\n", \
		p->first_name, p->last_name, p->birth_date, p->phone_number, p->email_address);

	printf("First name: %s\n", r.first_name);
	printf("Last name: %s\n", r.last_name);
	printf("Birth date: %s\n", r.birth_date);
	printf("Phone number: %s\n", r.phone_number);
	printf("Email Address: %s\n", r.email_address);

	if (fclose(fi) == -1)
	{
		fprintf(stderr, "close file %s errno %d\n", argv[1], errno);
		exit(EXIT_FAILURE);
	}

	return 0;
}