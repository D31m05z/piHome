
#include "pihome/networks/client.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <errno.h>

using namespace std;
using namespace pihome::networks;

Client::Client()
    : socket_desc_(-1)
{

}

Client::~Client()
{
    close(socket_desc_);
}

int Client::createSocket()
{
    //Create socket
    socket_desc_ = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc_ == -1) {
        printf("Could not create socket");
    }

    memset(&server_, 0, sizeof(server_));
    server_.sin_addr.s_addr = inet_addr("10.1.12.75");
    server_.sin_family = AF_INET;
    server_.sin_port = htons(8889);

    //Connect to remote server
    if (connect(socket_desc_, (struct sockaddr *) &server_, sizeof(server_)) < 0) {
        cout << strerror(errno);
        close(socket_desc_);
        puts("Connect Error");
        return 1;
    }

    puts("Connected\n");

    return socket_desc_;
}

//This function is to be used once we have confirmed that an image is to be sent
//It should read and output an image file
int Client::receiveImage(int socket)
{
    int buffersize = 0, recv_size = 0, size = 0, read_size, write_size, packet_index = 1, stat;

    char imagearray[10241], verify = '1';
    FILE *image;

//Find the size of the image
    do {
        stat = read(socket, &size, sizeof(int));
    } while (stat < 0);

    printf("Packet received.\n");
    printf("Packet size: %i\n", stat);
    printf("Image size: %i\n", size);
    printf(" \n");

    char buffer[] = "Got it";

//Send our verification signal
    do {
        stat = write(socket, &buffer, sizeof(int));
    } while (stat < 0);

    printf("Reply sent\n");
    printf(" \n");

    image = fopen("capture2.jpeg", "w");

    if (image == NULL) {
        printf("Error has occurred. Image file could not be opened\n");
        return -1;
    }

//Loop while we have not received the entire file yet


    int need_exit = 0;
    struct timeval timeout = {10, 0};

    fd_set fds;
    int buffer_fd, buffer_out;

    while (recv_size < size) {
//while(packet_index < 2){

        FD_ZERO(&fds);
        FD_SET(socket, &fds);

        buffer_fd = select(FD_SETSIZE, &fds, NULL, NULL, &timeout);

        if (buffer_fd < 0)
            printf("error: bad file descriptor set.\n");

        if (buffer_fd == 0)
            printf("error: buffer read timeout expired.\n");

        if (buffer_fd > 0) {
            do {
                read_size = read(socket, imagearray, 10241);
            } while (read_size < 0);

            printf("Packet number received: %i\n", packet_index);
            printf("Packet size: %i\n", read_size);


            //Write the currently read data into our image file
            write_size = fwrite(imagearray, 1, read_size, image);
            printf("Written image size: %i\n", write_size);

            if (read_size != write_size) {
                printf("error in read write\n");
            }


            //Increment the total number of bytes read
            recv_size += read_size;
            packet_index++;
            printf("Total received image size: %i\n", recv_size);
            printf(" \n");
            printf(" \n");
        }

    }


    fclose(image);
    printf("Image successfully Received!\n");
    return 1;
}

#if 0
int main(int argc, char *argv[])
{
    Client client;
    int socket_desc = client.createSocket();
    client.receiveImage(socket_desc);

    return 0;
}
#endif