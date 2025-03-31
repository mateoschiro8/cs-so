#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int count = 0;

void yava() {
	write(1, "ya va!\n", 7);
	count++;
}

void esperoAlHijo() {
	wait(NULL);
	exit(EXIT_SUCCESS);
}

void hijo(char* argv[]) {
	signal(SIGURG, yava);

	while(count < 5);
	
	kill(getppid(), SIGINT);

	execvp(argv[1], argv + 1);
}

int main(int argc, char* argv[]) {
  	
	pid_t pidHijo = fork();
	if(pidHijo == 0) hijo(argv);

	signal(SIGINT, esperoAlHijo);

	while(1) {
		sleep(1);
		write(1, "sup!\n", 5);
		kill(pidHijo, SIGURG);
	}

	return 0;
}
