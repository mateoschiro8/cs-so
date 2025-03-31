#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int n;
int numero_maldito;
pid_t* hijos;

int generate_random_number(){
    //Funcion para cargar nueva semilla para el numero aleatorio
    srand(time(NULL) ^ getpid());
    return (rand() % n);
    
}

void signalHandler() {
    int num = generate_random_number();

    if(num == numero_maldito) {
        exit(EXIT_SUCCESS);
    }
    printf("Sobreviví! Soy el hijo #%d y saqué el %d\n", getpid(), num);

}

void seMeMurioUnPibe() {
    pid_t pibeMuerto = wait(NULL);
    for(int i = 0; i < n; i++) {
        if(hijos[i] != pibeMuerto) continue;
        
        printf("Se murió el hijo %d con PID #%d :(\n", i, pibeMuerto);
        hijos[i] = -1;
        break;
    }
}


void hijo() {
    signal(SIGTERM, signalHandler);
    while(1);
}

int main(int argc, char const *argv[]){
    
    n = atoi(argv[1]);
	int rondas = atoi(argv[2]);
	numero_maldito = atoi(argv[3]);

    // Completar
    hijos = malloc(n * sizeof(pid_t));
    pid_t newPid;

    // Voy creando hijos
    for(int i = 0; i < n; i++) {
        newPid = fork();
        // Si soy un hijo, salgo
        if(newPid == 0) break;
        hijos[i] = newPid;
    }

    if(newPid == 0) hijo();
    
    signal(SIGCHLD, seMeMurioUnPibe);
    
    for(int k = 0; k < rondas; k++) {
        printf("RONDA %d\n", k + 1);
        for(int i = 0; i < n; i++) {
            if(hijos[i] == -1) continue;
            kill(hijos[i], SIGTERM);
            sleep(1);
        }
    }

    printf("Hijos que sobrevivieron: \n");
    for(int i = 0; i < n; i++) {
        if(hijos[i] == -1) continue;
        printf("    Hijo %i, con PID #%d\n", i, hijos[i]);
        kill(hijos[i], SIGKILL);
    }

    free(hijos);
    exit(0);
}
