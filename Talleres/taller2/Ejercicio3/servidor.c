#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int calcular(const char *expresion) {
    int num1, num2, resultado;
    char operador;

    // Usamos sscanf para extraer los dos números y el operador de la expresión
    if (sscanf(expresion, "%d%c%d", &num1, &operador, &num2) != 3) {
        printf("Formato incorrecto\n");
        return 0;  // En caso de error, retornamos 0.
    }

    // Realizamos la operación según el operador
    switch (operador) {
        case '+':
            resultado = num1 + num2;
            break;
        case '-':
            resultado = num1 - num2;
            break;
        case '*':
            resultado = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                resultado = num1 / num2;
            } else {
                printf("Error: División por cero\n");
                return 0;  // Si hay división por cero, retornamos 0.
            }
            break;
        default:
            printf("Operador no reconocido\n");
            return 0;  // Si el operador no es válido, retornamos 0.
    }

    return resultado;
}

void clienteHandler(int clientSocket) {
    int res;
    char c[255];
    while(1) {
        recv(clientSocket, c,255, 0);
        if(strcmp(c, "exit") == 0) break;	
        res = calcular(c);
        send(clientSocket, &res, sizeof(res), 0);
    }
    close(clientSocket);
    printf("CHAU\n");
    exit(0);
}

int main() {
     
    /*
    const char *expresion = "10+5";  
    int resultado = calcular(expresion);
    printf("El resultado de la operación es: %d\n", resultado);
    */

    int server_socket, client_socket;
    struct sockaddr_un server_addr, client_addr;
    uint slen = sizeof(server_addr), clen = sizeof(client_addr);

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");
    unlink(server_addr.sun_path);

    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    bind(server_socket, (struct sockaddr *) &server_addr, slen);
    listen(server_socket, 1);

    printf("Servidor: esperando conexión del cliente...\n");
    while(1) {
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &clen);
        printf("Servidor: Se conectó alguien...\n");

        if(fork() == 0) clienteHandler(client_socket);
        
    }
    
    exit(0);
}
