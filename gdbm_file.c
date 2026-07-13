#define _XOPEN_SOURCE // for strptime()
#include <errno.h>
#include <gdbm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

/*
gcc gdbm_file.c -g -o gdbm_file -lgdbm
gdbm_file gdbm_file.gdbm
splint -mustfreefresh +matchanyintegral -shiftimplementation -warnposix gdbm_file.c
hexdump -C gdbm_file.gdbm
*/

// Here so splint sees it
char *strptime(const char *restrict s, const char *restrict format, struct tm *restrict tm);

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

/* for reference
typedef struct
{
   char *dptr;
   int  dsize;
} datum;
*/

int main(int argc, char const *argv[])
{
	GDBM_FILE gdbf;
	datum key;
	datum content;
	datum contentin;
	char *pk;
	char *datein = "01/01/1980";
	char *dateout; 
	char *p;
	int i = 0;
	int n = -1;
	int s = -1;
	size_t DATE = 30;
	struct RECORD r;
	struct RECORD *rptr;
	struct RECORD w;
	struct RECORD *wptr;
	struct tm datetm;
	time_t seconds_since_epoch = -1;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: gdbm_file [FILE]\n");
		exit(EXIT_FAILURE);
	}

	gdbf = gdbm_open(argv[1], 0, GDBM_WRCREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH), NULL);
	if (gdbf == NULL)
	{
		fprintf(stderr, "can't open database: %s\n", gdbm_strerror (gdbm_errno));
		exit(EXIT_FAILURE);
	}
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
	// Can I use a pointer like I did 20 years ago?
	p = ((void *)&w);
	for (i=0; i<(int)sizeof(w); i++)
		*(p + i) = '\0';
	w.nl = '\n';

	strcpy(w.first_name, "Donald");
	strcpy(w.last_name, "Bales");

	// Had to initialize this so it could be addressed properly
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

	(void) strptime(datein, "%m/%d/%Y", &datetm);

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

	s = sizeof(w.last_name) + sizeof(w.first_name) + 2;
	printf("max key size: %d\n", s);
	pk = malloc(s);
	if (pk == NULL)
	{
		exit(EXIT_FAILURE);
	}
	n = snprintf(pk, s, "%s, %s", w.last_name, w.first_name);
	printf("actual key size: %d\n", n);
	printf("strlen(pk) size: %ld\n", strlen(pk));
	key.dsize = n;
	key.dptr = (((void *)pk));
	pk = NULL;

	content.dsize = sizeof(w);
	wptr = &w;
	content.dptr = (((void *)wptr));
	wptr = NULL;

	n = gdbm_store(gdbf, key, content, GDBM_INSERT);
	if (n == -1)
	{
		fprintf(stderr, "can't insert into database: %s\n", gdbm_strerror (gdbm_errno));
		exit(EXIT_FAILURE);
	}
	else if (n == 1)
	{
		fprintf(stderr, "can't insert into database: %s\n", gdbm_strerror (gdbm_errno));
	}
	(void) gdbm_close(gdbf);

	gdbf = gdbm_open(argv[1], 0, GDBM_WRCREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH), NULL);
	if (gdbf == NULL)
	{
		fprintf(stderr, "can't open database: %s\n", gdbm_strerror (gdbm_errno));
		exit(EXIT_FAILURE);
	}

	// The key value is still the same as above
	contentin = gdbm_fetch(gdbf, key);
	if (contentin.dptr == NULL && \
		gdbm_errno == GDBM_ITEM_NOT_FOUND) 
	{
		printf("key not found!\n");
	}
	else if (contentin.dptr == NULL)
	{
		fprintf(stderr, "%s\n", gdbm_db_strerror (gdbf));
	}
	// from dptr to rptr to rptr value to r
	rptr = ((void *)contentin.dptr);
	if (rptr == NULL)
	{
		exit(EXIT_FAILURE);
	}
	r = *rptr;
	rptr = NULL;

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

	dateout = calloc(DATE, 1);
	if (dateout == NULL)
	{
		exit(EXIT_FAILURE);
	}
	(void) strftime(dateout, DATE, "%m/%d/%Y", &datetm);

	printf("Birth date: %s\n", dateout);
	printf("Phone number: %s\n", r.phone_number);
	printf("Email Address: %s\n", r.email_address);

	free(dateout);
	free(pk);
	(void) gdbm_close(gdbf);
	return 0;
}