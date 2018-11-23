#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 * Error handeling examples with C.
 *
 * For further built in functions uses, I'd recommend studying man pages
 * and/or POSIX standard.
 *
 */
int main(int argc, char* argv[])
{
	/*
	 * Let's try opening a non-existing file with fopen()
	 *
	 * RETURN VALUE
	 * 	Upon successful completion fopen() return a FILE pointer. Otherwise, 
	 * 	NULL is returned and errno is set to indicate the error.
	 *
	 * We will focus on functions that handle this errno value.
	 *
	 */
	FILE *f= NULL;
	
	f = fopen("null_file", "r");

	/*
	 * We know that at this point there will be an error with fopen()
	 * and it will return NULL so our errno variable is gona be set. 
	 * Each possible errno value has its macro, value, and description
	 * (read the documentation).
	 *
	 */
	if (f == NULL) {
		perror("\0"); /* Null byte as argument */
		perror("Error");
		fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
		
		exit(EXIT_FAILURE);
	}

	return(EXIT_SUCCESS);
}
