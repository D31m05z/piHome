#include "pihome/networks/server.h"
#include "pihome/sensors/camera.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <errno.h>

using namespace std;
using namespace pihome::networks;
using namespace pihome::sensors;

Server::Server()
    : socket_desc_(-1)
    , new_socket_(-1)
{

}

Server::~Server()
{
    close(socket_desc_);
    fflush(stdout);
}

int Server::createSocket()
{
    //Create socket
    socket_desc_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc_ == -1) {
        printf("Could not create socket\n");
    }

    //Prepare the sockaddr_in structure
    server_.sin_family = AF_INET;
    server_.sin_addr.s_addr = INADDR_ANY;
    server_.sin_port = htons(8888);

    //Bind
    if (bind(socket_desc_, (struct sockaddr *) &server_, sizeof(server_)) < 0) {
        printf("bind failed\n");
        return 1;
    }

    printf("bind done\n");

    //Listen
    listen(socket_desc_, 3);

    return 0;
}

int Server::waitIncomingConnection()
{
    //Accept and incoming connection
    printf("Waiting for incoming connections...\n");
    int c = sizeof(struct sockaddr_in);

    if ((new_socket_ = accept(socket_desc_, (struct sockaddr *) &client_, (socklen_t *) &c))) {
        printf("Connection accepted\n");
    }

    fflush(stdout);

    if (new_socket_ < 0) {
        printf("Accept Failed\n");
        return 1;
    }

    return new_socket_;
}

int Server::sendImage(int socket, const char* fileName) {
    FILE *picture;
    int size, read_size, stat, packet_index;
    char send_buffer[10240], read_buffer[256];
    packet_index = 1;

    picture = fopen(fileName, "r");
    printf("Getting Picture Size\n");

    if (picture == NULL) {
        printf("Error Opening Image File");
    }

    fseek(picture, 0, SEEK_END);
    size = ftell(picture);
    fseek(picture, 0, SEEK_SET);
    printf("Total Picture size: %i\n", size);

    //Send Picture Size
    printf("Sending Picture Size\n");
    write(socket, (void *) &size, sizeof(int));

    //Send Picture as Byte Array
    printf("Sending Picture as Byte Array\n");

    do { //Read while we get errors that are due to signals.
        stat = read(socket, &read_buffer, 255);
        printf("Bytes read: %i\n", stat);
    } while (stat < 0);

    printf("Received data in socket\n");
    printf("Socket data: %s\n", read_buffer);

    while (!feof(picture)) {
        //while(packet_index = 1){
        //Read from the file into our send buffer
        read_size = fread(send_buffer, 1, sizeof(send_buffer) - 1, picture);

        //Send data through our socket
        do {
            stat = write(socket, send_buffer, read_size);
        } while (stat < 0);

        printf("Packet Number: %i\n", packet_index);
        printf("Packet Size Sent: %i\n", read_size);
        printf(" \n");
        printf(" \n");

        packet_index++;

        //Zero out our send buffer
        bzero(send_buffer, sizeof(send_buffer));
    }

    fclose(picture);

    return 0;
}

int Server::sendImage(int socket, const Image& image)
{
    int size=0, read_size=0, total=0, stat=0, packet_index=1;
    char send_buffer[10240], read_buffer[256];

    size = image.data.size();
    printf("Total Picture size: %i\n", size);

    //Send Picture Size
    printf("Sending Picture Size\n");
    write(socket, (void *) &size, sizeof(int));

    //Send Picture as Byte Array
    printf("Sending Picture as Byte Array\n");

    do { //Read while we get errors that are due to signals.
        stat = read(socket, &read_buffer, 255);
        printf("Bytes read: %i\n", stat);
    } while (stat < 0);

    printf("Received data in socket\n");
    printf("Socket data: %s\n", read_buffer);

    while (total < size) {
        //while(packet_index = 1){
        //Read from the file into our send buffer
        read_size = std::min(image.data.size() - total, sizeof(send_buffer));

        for(int i = 0; i < read_size; i++ ) {
            send_buffer[i] = image.data[total + i];
        }
        total += read_size;
        //read_size = fread(send_buffer, 1, sizeof(send_buffer) - 1, picture);

        //Send data through our socket
        do {
            stat = write(socket, send_buffer, read_size);
        } while (stat < 0);

        printf("Packet Number: %i\n", packet_index);
        printf("Packet Size Sent: %i\n", read_size);
        printf("Total Size: %i\n", total);
        printf(" \n");
        printf(" \n");

        packet_index++;

        //Zero out our send buffer
        bzero(send_buffer, sizeof(send_buffer));
    }

    return 0;
}
