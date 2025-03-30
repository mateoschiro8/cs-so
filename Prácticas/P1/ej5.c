#include <stdio.h>
#include <stdlib.h>   
#include <unistd.h>
#include <sys/wait.h>

void Abraham() {
    printf("Soy Abraham");
    wait(NULL);
    exit(0);
}

void Homero() {
    printf("Soy Homero");

    if(fork() == 0) Lisa();

    if(fork() == 0) Bart();

    if(fork() == 0) Maggie();

    wait(NULL);
    wait(NULL);
    wait(NULL);

    exit(0);
}

void Lisa() {
    printf("Soy Lisa");
    exit(0);
}

void Bart() {
    printf("Soy Bart");
    exit(0);
}

void Maggie() {
    printf("Soy Maggie");
    exit(0);
}

int main() {

    if(fork() == 0) Homero();

    Abraham();

    return 0;
}