#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

int server_socket;
    
void intHandler() {
    send(server_socket, "exit", 5, 0);
    close(server_socket);
    exit(0);
}

int main() {
    
    struct sockaddr_un server_addr;

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");

    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error");
        exit(1);
    }

    signal(SIGINT, intHandler);

	char* c = calloc(255, 1);
    int res;

	while(1) {
		scanf("%s", c);
        send(server_socket, c,strlen(c) + 1, 0);
        if(strcmp(c, "exit") == 0) break;    
        read(server_socket, &res,sizeof(res));
		printf("%d\n", res);
	}

    close(server_socket);
    exit(0);
}

