#include <sys/stat.h>
#include "ndnfs-client.h"

#define PORT 8080

using namespace std;

int sock = 0;

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

orders getOrder(string order) {
    orders o = DEFAULT;
    if (strcmp(order.c_str(), "quit") == 0)
        o = QUIT;
    else if (strcmp(order.c_str(), "send") == 0)
        o = SEND;
    else if (strcmp(order.c_str(), "getattr") == 0)
        o = GETATTR;
    else if(strcmp(order.c_str(), "open") == 0)
        o = OPEN;
    else if(strcmp(order.c_str(), "read") == 0)
        o = READ;
    else if(strcmp(order.c_str(), "write") == 0)
        o = WRITE;
    return o;
}

void usage() {
    cout << "usage:" << endl;
    cout << "send: send a message to server." << endl;
    cout << "quit: finish this session." << endl;
    cout << "******************************************" << endl;
}

int main(int argc, char const *argv[]) {

    int  valread;
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
        memset(inputOrder, '\0', sizeof(inputOrder));
        cin.getline(inputOrder, 200);
        vector<string> v;
        SplitString(inputOrder, v, " ");
        orders order = getOrder(v[0]);
        switch (order) {
            case QUIT:
                return 0;
            case SEND: {
                send(sock, hello, strlen(hello), 0);
                printf("Hello message sent\n");
                valread = read(sock, buffer, 1024);
                printf("%s\n", buffer);
                break;
            }
            case GETATTR: {
                struct stat * st;
                if (client_getattr(inputOrder, st) == 0)
//                    cout<< st->st_size<< endl;
                break;
            }
            case OPEN: {
                client_open(inputOrder);
                break;
            }
            case READ: {
                char buf[1024];
                memset(buf, '\0', 1024);
                client_read(inputOrder, buf);
                FILE_LOG(LOG_DEBUG)<< buf<< endl;
                break;
            }
            case WRITE: {
                FILE_LOG(LOG_DEBUG)<< "Write size:"<< client_write(inputOrder)<< endl;
                break;
            }
            default:
                usage();
                break;
        }
    }

    return 0;
}