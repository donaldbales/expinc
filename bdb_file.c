/*
/usr/lib/aarch64-linux-gnu/libdb-5.3.so
/usr/lib/aarch64-linux-gnu/libdb-5.3.a
*/

#include <db.h> // Berkeley DB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
gcc bdb_file.c -g -o bdb_file /usr/lib/aarch64-linux-gnu/libdb-5.3.so
bdb_file bdb_file.bdb
splint +matchanyintegral -nullpass -compdef -usedef -mustfreeonly bdb_file.c
hexdump -C bdb_file.bdb
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
typedef struct {
    void  *data;
    size_t size;
} DBT;
*/

int main(int argc, char const *argv[])
{
	char *datein = "01/01/1980";
	char *dateout; 
	char *e;
	char *pk;
	DB *bdbf;
	DBT datain;
	DBT dataout;
	DBT key;
	int n = -1;
	int s = -1;
	size_t DATE = 30;
	struct RECORD *rptr;
	struct RECORD *wptr;
	struct RECORD r;
	struct RECORD w;
	struct tm datetm;
	time_t seconds_since_epoch = -1;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: gdbm_file [FILE]\n");
		exit(EXIT_FAILURE);
	}

	printf("Calling db_create()\n");
//	int db_create(DB **dbp, DB_ENV *dbenv, u_int32_t flags);
	n = db_create(&bdbf, NULL, 0);
	if (n != 0) {
		e = db_strerror(n);
		fprintf(stderr, "Database create error: %s\n", e);
		exit(EXIT_FAILURE);
	}

	if (&bdbf == NULL)
	{
		exit(EXIT_FAILURE);
	}

	printf("Calling open()\n");
//	int DB->open(DB *db, DB_TXN *txnid, const char *file, const char *database, DBTYPE type, u_int32_t flags, int mode);
	n = bdbf->open(bdbf, NULL, argv[1], NULL, DB_HASH, DB_CREATE, 0);
	if (n != 0)
	{
		e = db_strerror(n);
		fprintf(stderr, "can't open database: %s\n", e);
		exit(EXIT_FAILURE);
	}

	// initialize the structure
	wptr = &w;
	memset(wptr, 0, sizeof(w));
	w.nl = '\n';

	strcpy(w.first_name, "Donald");
	strcpy(w.last_name, "Bales");
	printf("First name: %s\n", w.first_name);
	printf("Last name: %s\n", w.last_name);

	// Had to initialize this so it could be addressed properly
	memset(&datetm, 0, sizeof(datetm));

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
	printf("Phone number: %s\n", w.phone_number);
	printf("Email Address: %s\n", w.email_address);

	printf("sizeof(struct RECORD): %ld\n", sizeof(struct RECORD));
	printf("sizeof(w): %ld\n", sizeof(w));

	// Prepare key and value
	memset(&key, 0, sizeof(DBT));
	memset(&dataout, 0, sizeof(DBT));

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
	
	key.flags = DB_DBT_USERMEM;
	key.ulen = (u_int32_t)n + 1;
	key.size = key.ulen;
	key.data = pk;
	pk = NULL;

	dataout.flags = DB_DBT_USERMEM;
	dataout.ulen = sizeof(w);
	dataout.size = dataout.ulen;
	dataout.data = wptr;

	printf("Calling put()\n");
// int DB->put(DB *db, DB_TXN *txnid, DBT *key, DBT *data, u_int32_t flags);
	n = bdbf->put(bdbf, NULL, &key, &dataout, 0);
	if (n != 0)
	{
		e = db_strerror(n);
		fprintf(stderr, "can't insert into database: %s\n", e);
		//exit(EXIT_FAILURE);
	}

	printf("Calling close()\n");
//	int DB->close(DB *db, u_int32_t flags);
	n = bdbf->close(bdbf, 0);

	printf("Calling db_create() again\n");
//	int db_create(DB **dbp, DB_ENV *dbenv, u_int32_t flags);
	n = db_create(&bdbf, NULL, 0);
	if (n != 0) {
		e = db_strerror(n);
		fprintf(stderr, "Database create error: %s\n", e);
		exit(EXIT_FAILURE);
	}

	if (&bdbf == NULL)
	{
		exit(EXIT_FAILURE);
	}

//	int DB->open(DB *db, DB_TXN *txnid, const char *file, const char *database, DBTYPE type, u_int32_t flags, int mode);
	printf("Calling open() again\n");
	n = bdbf->open(bdbf, NULL, argv[1], NULL, DB_HASH, 0, 0);
	if (n != 0)
	{
		e = db_strerror(n);
		fprintf(stderr, "can't open database: %s\n", e);
		exit(EXIT_FAILURE);
	}

	printf("Calling get()\n");
	rptr = &r;
	memset(rptr, 0, sizeof(r));

	memset(&datain, 0, sizeof(DBT));
	datain.flags = DB_DBT_USERMEM;
	datain.ulen = sizeof(r);
	datain.data = rptr;

//	int DB->get(DB *db, DB_TXN *txnid, DBT *key, DBT *data, u_int32_t flags);
	n = bdbf->get(bdbf, NULL, &key, &datain, 0);
	if (n != 0)
	{
		e = db_strerror(n);
		fprintf(stderr, "can't retrieve from database: %s\n", e);
		//exit(EXIT_FAILURE);
	}

	if (rptr == NULL)
	{
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

	dateout = calloc(DATE, 1);
	if (dateout == NULL)
	{
		exit(EXIT_FAILURE);
	}
	(void) strftime(dateout, DATE, "%m/%d/%Y", &datetm);

	printf("Birth date: %s\n", dateout);
	printf("Phone number: %s\n", r.phone_number);
	printf("Email Address: %s\n", r.email_address);

	printf("Calling close() again\n");
//	int DB->close(DB *db, u_int32_t flags);
	n = bdbf->close(bdbf, 0);

	free(dateout);
	free(pk);
	
	dataout.app_data = NULL;
	datain.app_data = NULL;
	dataout.data = NULL;
	datain.data = NULL;
	key.app_data = NULL;
	key.data = NULL;
	e = NULL;

	return 0;
}