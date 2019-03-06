
#include "pihome/networks/server.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void SIGINT_signal(int s){
    printf("Caught signal %d\n", s);
    exit(1);
}

int main(int argc, char** argv)
{
    signal(SIGINT, SIGINT_signal);

    pihome::networks::Server server;

    if(server.createSocket() != 0) {
        return 1;
    }

    int client_socket = server.waitIncomingConnection();

    if( client_socket < 0) {
      return client_socket;
    }

    while(true) {
        // for test
        if(server.sendImage(client_socket, "image.jpg") !=0) {
            return 1;
        }
    }

    return 0;
}
