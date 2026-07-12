#define _XOPEN_SOURCE
#define __USE_XOPEN
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

/*
gcc fixed_length_binary_file.c -g -o fixed_length_binary_file

splint +posixlib +trytorecover fixed_length_binary_file.c

hexdump -C flbf.bin
*/

// Now let's use the return value from the date
struct RECORD 
{
	char first_name[31];
	char last_name[31];
	time_t birth_date;
	char phone_number[16];
	char email_address[81];
	char nl;
};

int main(int argc, char const *argv[])
{
	int fd = -1;
	int fi = -1;
	int n = -1;
	struct RECORD r;
	struct RECORD w;
	char *p;
	char buffer[1024];
	size_t DATE = 30;
	struct tm datetm;
	char *datein = "01/01/1980";
	char *dateout = calloc(DATE, 1);
	time_t seconds_since_epoch = -1;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: fixed_length_binary_file [FILE]\n");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], \
			O_CREAT | O_WRONLY | O_TRUNC, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); 
	if (fd == -1)
	{
		fprintf(stderr, "open file %s errno %d", argv[1], errno);
		exit(EXIT_FAILURE);
	}
	// can I cheat and use a pointer ike I did 20 years ago?
	p = &w;
	int i;
//# ifndef S_SPLINT_S
	for (i=0; i<(int)sizeof(w); i++)
		*(p + i) = 0;
//# endif
/*
	// This is needed to clear the garbage out of memory
	for (int i=0; i<sizeof(w.first_name); i++)
		w.first_name[i] = '\0';
	for (int i=0; i<sizeof(w.last_name); i++)
		w.last_name[i] = '\0';
	w.birth_date = 0L;
	for (int i=0; i<sizeof(w.phone_number); i++)
		w.phone_number[i] = '\0';
	for (int i=0; i<sizeof(w.email_address); i++)
		w.email_address[i] = '\0';
	w.nl = '\n';
*/
	strcpy(w.first_name, "Donald");
	strcpy(w.last_name, "Bales");

	// Had to initialize this so it could be addressesd properly
	datetm.tm_sec = 0;
	datetm.tm_min = 0;
	datetm.tm_hour = 0;
	datetm.tm_mday = 1;
	datetm.tm_mon = 0;
	datetm.tm_year = 0;
	datetm.tm_wday = -1;
	datetm.tm_yday = -1;
	datetm.tm_isdst = -1;

	printf("datein: %s\n", datein);

	strptime(datein, "%m/%d/%Y", &datetm);

	printf("datetm.tm_sec: %d\n", datetm.tm_sec);
	printf("datetm.tm_min: %d\n", datetm.tm_min);
	printf("datetm.tm_hour: %d\n", datetm.tm_hour);
	printf("datetm.tm_mday: %d\n", datetm.tm_mday);
	printf("datetm.tm_mon: %d\n", datetm.tm_mon);
	printf("datetm.tm_year: %d\n", datetm.tm_year);
	printf("datetm.tm_wday: %d\n", datetm.tm_wday);
	printf("datetm.tm_yday: %d\n", datetm.tm_yday);
	
	seconds_since_epoch = mktime(&datetm);
	printf("seconds since epoch: %ld\n", seconds_since_epoch);

	w.birth_date = seconds_since_epoch;
	printf("w.birth_date: %ld\n", w.birth_date);

	strcpy(w.phone_number, "630-555-1212");
	strcpy(w.email_address, "don@donaldbales.com");

	printf("sizeof(struct RECORD): %ld\n", sizeof(struct RECORD));
	printf("sizeof(w): %ld\n", sizeof(w));
	write(fd, &w, sizeof(w));

	if (close(fd) == -1)
	{
		fprintf(stderr, "close file %s errno %d\n", argv[1], errno);
		exit(EXIT_FAILURE);
	}

	fi = open(argv[1], O_RDONLY);
	if (fi == -1)
	{
		fprintf(stderr, "open file %s errno %d\n", argv[1], errno);
		exit(EXIT_FAILURE);
	}
/*  Don't seem to need this
	for (int i=0; i<sizeof(r.first_name); i++)
		r.first_name[i] = '\0';
	for (int i=0; i<sizeof(r.last_name); i++)
		r.last_name[i] = '\0';
	r.birth_date = 0L;
	for (int i=0; i<sizeof(r.phone_number); i++)
		r.phone_number[i] = '\0';
	for (int i=0; i<sizeof(r.email_address); i++)
		r.email_address[i] = '\0';
	r.nl = '\n';
*/
	n = read(fi, &r, sizeof(r));
	printf("Number of bytes read: %d\n", n);
	printf("sizeof(r): %ld\n", sizeof(r));

	if (n == -1)
	{
		fprintf(stderr, "read file error %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	printf("First name: %s\n", r.first_name);
	printf("Last name: %s\n", r.last_name);

	datetm.tm_mday = 1;
	datetm.tm_mon = 0;
	datetm.tm_year = 0;
	datetm.tm_wday = -1;
	datetm.tm_yday = -1;
	datetm.tm_isdst = -1;

	datetm = *localtime(&seconds_since_epoch);
	printf("datetm.tm_sec: %d\n", datetm.tm_sec);
	printf("datetm.tm_min: %d\n", datetm.tm_min);
	printf("datetm.tm_hour: %d\n", datetm.tm_hour);
	printf("datetm.tm_mday: %d\n", datetm.tm_mday);
	printf("datetm.tm_mon: %d\n", datetm.tm_mon);
	printf("datetm.tm_year: %d\n", datetm.tm_year);
	printf("datetm.tm_wday: %d\n", datetm.tm_wday);
	printf("datetm.tm_yday: %d\n", datetm.tm_yday);

	(void) strftime(dateout, DATE, "%m/%d/%Y", &datetm);
	printf("Birth date: %s\n", dateout);

	printf("Phone number: %s\n", r.phone_number);
	printf("Email Address: %s\n", r.email_address);

	close(fi);
	return 0;
}