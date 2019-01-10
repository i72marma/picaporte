#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define N_PRO		5

pid_t test();

int main()
{
	pid_t end;

	/* Children work */
	if (!fork()) {
		printf("PID -> %d --- PPID -> %d\n", (int) getpid(), (int) getppid());
		for (int i = 1; i < N_PRO && !test(); i++);
	}

	
	while ((end = wait(NULL)) >= 0) {
		printf("Process %d finished\n", (int) end);
	}

	exit(EXIT_SUCCESS);
}

pid_t test()
{
	pid_t pid = fork();

	if (!pid) {
		printf("PID -> %d --- PPID -> %d\n", (int) getpid(), (int) getppid());
		return(pid);
	} else {
		return(pid);
	}
}
