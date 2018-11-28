#include "sys/socket.h"
#include "bits/stdc++.h"
#include "iostream"
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
enum orders {
    QUIT, SEND, DEFAULT
};


using namespace std;

int init_socket(struct sockaddr_in &serv_addr) {
    int sock = 0;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    // TODO: figure out WHY?
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    return sock;

}

orders getorder(char *order) {
    orders o = DEFAULT;
    if (strcmp(order, "quit") == 0)
        o = QUIT;
    else if (strcmp(order, "send") == 0)
        o = SEND;
    return o;
}

void usage() {
    cout<< "usage:"<< endl;
    cout << "send: send a message to server." << endl;
    cout << "quit: finish this session." << endl;
    cout<<"******************************************"<< endl;
}

int main(int argc, char const *argv[]) {

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    sock = init_socket(serv_addr);

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    char inputOrder[200];
    while (true) {
        cin >> inputOrder;
        orders order = getorder(inputOrder);
        switch (order) {
            case QUIT:
                return 0;
            case SEND:
                send(sock, hello, strlen(hello), 0);
                printf("Hello message sent\n");
                valread = read(sock, buffer, 1024);
                printf("%s\n", buffer);
                break;
            default:
                usage();
                break;
        }
    }

    return 0;
}