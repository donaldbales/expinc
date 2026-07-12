#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/*
gcc fixed_length_text_file.c -g -o fixed_length_text_file
splint +posixlib fixed_length_text_file.c
fixed_length_text_file fixed_length_text_file.bin
hexdump -C fixed_length_text_file.txt 
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
	int fd = -1;
	ssize_t n = -1;
	struct RECORD r, w;
	int i;
	if (argc != 2)
	{
		fprintf(stderr, "Usage: fixed_length_binary_file [FILE]\n");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], \
			O_CREAT | O_WRONLY | O_TRUNC, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw- */
	if (fd == -1)
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

	(void) write(fd, &w, sizeof(r));

	if (close(fd) == -1)
	{
		fprintf(stderr, "close file %s errno %d\n", argv[1], errno);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "open file %s errno %d\n", argv[1], errno);
		exit(EXIT_FAILURE);
	}

	n = read(fd, &r, sizeof(r));

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


	return 0;
}