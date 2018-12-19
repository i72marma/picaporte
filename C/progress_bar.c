#include <stdio.h>
#include <unistd.h> /* sleep() */

void fill_progress(const int percent, const int proglen);

int main()
{
	for (int i = 0; i < 100; i++) {
		fill_progress(i, 75);

		sleep(1);
	}

	return 0;
}

void fill_progress(const int percent, const int proglen)
{
	const unsigned int hashlen = proglen - 8;
	const unsigned int hash = percent * hashlen / 100;

	printf(" [");
	for (unsigned int i = hashlen; i > 1; --i) {
		if(i > hashlen - hash) {
			printf("#");
		} else {
			printf("-");
		}
	}
	printf("] %3d%%", percent);

	if(percent == 100) {
		printf("\n");
	} else {
		printf("\r");
	}
	
	fflush(stdout);
}
