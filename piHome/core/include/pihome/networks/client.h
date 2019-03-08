#pragma once
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace pihome {
    namespace networks {

        class Client {
        public:
            Client();

            ~Client();

            int createSocket(const char* address, int port);

            int receiveImage(int socket, std::vector<unsigned char>& data);

        private:
            int socket_desc_;
            struct sockaddr_in server_;
        };

    } // networks
} // pihome
