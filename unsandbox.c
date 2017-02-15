/* Escape the Gentoo sandbox. Needed for ASAN tests to work. */
/* (c) 2016 Michał Górny, 2-clause BSD license */

#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	pid_t pid;
	int exitst;
	void* libc;
	int (*execvp_func)(const char *, char *const[]);

	if (argc < 2)
	{
		printf("Usage: %s <program> [<args>...]\n", argv[0]);
		return EXIT_FAILURE;
	}

	unsetenv("LD_PRELOAD");
	libc = dlopen("libc.so.6", RTLD_NOW);
	if (!libc)
	{
		perror("dlopen() failed");
		return EXIT_FAILURE;
	}
	execvp_func = dlsym(libc, "execvp");
	assert(execvp_func);

	execvp_func(argv[1], &argv[1]);
	perror("execvp() failed");

	dlclose(libc);
	return EXIT_FAILURE;
}
