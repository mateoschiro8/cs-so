#include <stdio.h>
#include <stdlib.h>   
#include <unistd.h>
#include <sys/wait.h>

void Abraham() {
    printf("Soy Abraham\n");
    wait(NULL);
    exit(EXIT_SUCCESS);
}

void Lisa() {
    printf("Soy Lisa\n");
    exit(EXIT_SUCCESS);
}

void Bart() {
    printf("Soy Bart\n");
    exit(EXIT_SUCCESS);
}

void Maggie() {
    printf("Soy Maggie\n");
    exit(EXIT_SUCCESS);
}

void Homero() {
    
    if(fork() == 0) Lisa();

    if(fork() == 0) Bart();
    
    if(fork() == 0) Maggie();
    
    printf("Soy Homero\n");

    wait(NULL);
    wait(NULL);
    wait(NULL);

    exit(0);
}

int main() {

    if(fork() == 0) Homero();

    Abraham();

    return 0;
}