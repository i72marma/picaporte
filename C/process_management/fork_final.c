#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

/* Test functions for wait() test */
void test(int sec);		// Normal -- EXIT_SUCCESS
void err_test(int sec);		// Error exit -- EXIT_FAILURE

int main()
{
	pid_t end;
	time_t when;
	int status;

	/* Children work */
	for (int i = 0; i <= 10; i++) {
		if (!fork()) {
			if (i == 0) {
				err_test(i + 3);
			} else {
				test(i + 3);
			}
		}
	}	
	
	/* Parent work */
	time(&when);
	printf("Parent process started at %s\n", ctime(&when));

	/* Waits until every process finish (Supposed normal exit) */
	do {
		end = wait(&status);

		printf("Wait status=%d -- EndPID=%d\n", status, end);

		if (WIFEXITED(status)) { printf("Exited. Status=%d\n", WEXITSTATUS(status)); }
	} while (end >= (pid_t) 0);

	exit(EXIT_SUCCESS);
}

void err_test(int sec)
{
	time_t when;
	time(&when);

	printf("I'm the process %d, started at %s", getpid(), ctime(&when));
	printf("Waiting %d seconds\n\n", sec);

	sleep(sec);
	
	exit(EXIT_FAILURE);
}

void test(int sec)
{
	time_t when;
	time(&when);

	printf("I'm the process %d, started at %s", getpid(), ctime(&when));
	printf("Waiting %d seconds\n\n", sec);

	sleep(sec);

	exit(EXIT_SUCCESS);
}
