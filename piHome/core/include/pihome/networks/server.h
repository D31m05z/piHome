#pragma once
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace pihome {
    namespace networks {

        class Server {
        public:
            Server();

            ~Server();

            int createSocket();

            int waitIncomingConnection();

            int sendImage(int socket, const char* fileName);

        private:
            int socket_desc_;
            int new_socket_;
            struct sockaddr_in server_, client_;
        };

    } // networks
} // pihome
