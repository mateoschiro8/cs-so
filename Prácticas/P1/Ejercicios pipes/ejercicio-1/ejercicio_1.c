#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include "dado.h"    // tirar_dado()

// Constants 0 and 1 for READ and WRITE
enum { READ, WRITE };
// Constants 0 and 1 for LESTER and ELIZA
enum { LESTER, ELIZA };

// Variables globales
int pipes[2][2];

void lester() {
  // Tiro el dado
  int dado = tirar_dado();
  // Le informo el resultado a Humberto
  write(pipes[LESTER][WRITE], &dado, sizeof(int));
  exit(EXIT_SUCCESS);
}

void eliza() {
  // Tiro el dado
  int dado = tirar_dado();
  // Le informo el resultado a Humberto
  write(pipes[ELIZA][WRITE], &dado, sizeof(int));
  exit(EXIT_SUCCESS);
}

int main(int argc, char const* argv[]) {
  
  // Creo los pipes
  pipe(pipes[LESTER]);
  pipe(pipes[ELIZA]);

  // Creo a Lester
  if(fork() == 0) lester();

  // Creo a Eliza
  if(fork() == 0) eliza();

  int dadoLester, dadoEliza;

  // Recibo el dado de Lester
  read(pipes[LESTER][READ], &dadoLester, sizeof(dadoLester));

  // Recibo el dado de Eliza
  read(pipes[ELIZA][READ], &dadoEliza, sizeof(dadoEliza));

  // Anuncio al ganador
  printf("El dado de Lester es %d y el de Eliza es %d\n", dadoLester, dadoEliza);

  return 0;
}
