#pragma once
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class Client
{
public:
    Client();
    ~Client();

    int createSocket();
    int receiveImage(int socket);

private:
    int socket_desc_;
    struct sockaddr_in server_;
};
