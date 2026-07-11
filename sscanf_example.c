/*
 This example comes from the sscanf(3) man page
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
gcc sscanf_example.c -g -o sscanf_example
splint sscanf_example.c

*/

int main()
{
	char *p;
	int n;
	char *str = "This is a long string to be parsed by sscanf in this program.";

	errno = 0;
	n = sscanf(str, "%m[ -~]", &p);
	if (n == 1) {
	    printf("read: %s\n", p);
	    free(p);
	} else if (errno != 0) {
	    perror("sscanf");
	} else {
	    fprintf(stderr, "No matching characters\n");
	}

	return 0;
}