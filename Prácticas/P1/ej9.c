#include <stdio.h>
#include <stdlib.h>   
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

pid_t pingPid;
pid_t pongPid;
int count = 0;

void ping() {

    count++;
    
    if(count == 4) {
        printf("De nuevo? [S]i / [N]o\n");
        char opt;
        scanf(" %c", &opt);
        if(opt == 'N') {
            kill(pongPid, SIGTERM);
            exit(EXIT_SUCCESS);
        }
        count = 1;
    }

    printf("PING! Soy #%d\n", pingPid);
    sleep(1);
    kill(pongPid, SIGUSR1);
}

void pong() {
    printf("PONG! Soy #%d\n", pongPid);
    sleep(1);
    kill(pingPid, SIGUSR1);
}

int main() {

    pingPid = getpid();
    pongPid = fork();

    if(pongPid < 0) 
        exit(EXIT_FAILURE);

    if(pongPid > 0) {
        // Espero que el proceso hijo registre su handler, 
        // registro el mío y arranco el proceso
        sleep(0.5);
        signal(SIGUSR1, ping);
        ping();
    }

    if(pongPid == 0) {
        // Soy el hijo, registro el handler
        pongPid = getpid();
        signal(SIGUSR1, pong);
    }

    // Para esperar las señales
    while(1);
}