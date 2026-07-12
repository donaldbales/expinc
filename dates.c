#define _XOPEN_SOURCE
#define __USE_XOPEN
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	// FYI:
	// struct tm 
	// {
	//     int tm_sec;   /* Seconds (0-60) */
	//     int tm_min;   /* Minutes (0-59) */
	//     int tm_hour;  /* Hours (0-23) */
	//     int tm_mday;  /* Day of the month (1-31) */
	//     int tm_mon;   /* Month (0-11) */
	//     int tm_year;  /* Year since 1900 */
	//     int tm_wday;  /* Day of the week (Sunday = 0)*/
	//     int tm_yday;  /* Day in the year (0-365; 1 Jan = 0)*/
	//     int tm_isdst; /* Daylight saving time flag
	//                      > 0: DST is in effect;
	//                      = 0: DST is not effect;
	//                      < 0: DST information not 
	//                      available */
	// };
	size_t MAX = 11;
	struct tm datetm;
	char *datein = "01/01/1980";
	char *dateout = malloc(MAX);
	time_t seconds_since_epoch = -1;

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

	datetm = *localtime(&seconds_since_epoch);
	printf("datetm.tm_sec: %d\n", datetm.tm_sec);
	printf("datetm.tm_min: %d\n", datetm.tm_min);
	printf("datetm.tm_hour: %d\n", datetm.tm_hour);
	printf("datetm.tm_mday: %d\n", datetm.tm_mday);
	printf("datetm.tm_mon: %d\n", datetm.tm_mon);
	printf("datetm.tm_year: %d\n", datetm.tm_year);
	printf("datetm.tm_wday: %d\n", datetm.tm_wday);
	printf("datetm.tm_yday: %d\n", datetm.tm_yday);
	
	(void) strftime(dateout, MAX, "%m/%d/%Y", &datetm);

	printf("dateout: %s\n", dateout);

	return 0;
}