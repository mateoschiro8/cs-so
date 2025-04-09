#include <stdio.h>    // printf()
#include <stdlib.h>   // exit()
#include <unistd.h>   // fork() pipe() execlp() dup2() close()
#include <sys/wait.h> // wait()

// Constants 0 and 1 for READ and WRITE
enum { READ, WRITE };

// Debe ejecutar "ls -al"
void ejecutar_hijo_1(int pipe_fd[]) {
  // Cierro lectura
  close(pipe_fd[READ]);

  // Conectar escritura a stdout
  dup2(pipe_fd[WRITE], STDOUT_FILENO);

  execlp("ls", "ls", "-al", NULL);
}

// Debe ejecutar "wc -l"
void ejecutar_hijo_2(int pipe_fd[]) {
  // Cerrar escritura
  close(pipe_fd[WRITE]);

  // Conectar lectura a stdin
  dup2(pipe_fd[READ], STDIN_FILENO);

  execlp("wc", "wc", "-l", NULL);
}

int main(int argc, char const* argv[]) {
  
  int pipes[2];
  pipe(pipes);

  if(fork() == 0) ejecutar_hijo_1(pipes);

  if(fork() == 0) ejecutar_hijo_2(pipes);

  // Cierro el fd de escritura para que hijo2 reciba el EOF
  // cuando hijo1 termine de escribir
  close(pipes[WRITE]);

  wait(NULL);
  wait(NULL);

  return 0;
}
