#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class Server
{
public:
    Server();
    ~Server();

    int createSocket();
    int waitIncomingConnection();
    int sendImage(int socket);

private:
    int socket_desc_;
    int new_socket_;
    struct sockaddr_in server_, client_;
};
