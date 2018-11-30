//
// Created by anson on 18-11-28.
//
#include <sys/stat.h>
#include "connect.h"

using namespace std;

int client_getattr(char *inputOrder, struct stat *stbuf) {
    FILE_LOG(LOG_DEBUG) << "client_getattr" << endl;
    send(sock, inputOrder, strlen(inputOrder), 0);
    Json::Value info;
    Json::Reader reader;
    char buffer[1024];
    memset(buffer, '\0', sizeof buffer);
    read(sock, buffer, 1024);
    if (reader.parse(buffer, info)) {
        if (info["issucess"].asInt() == 1) {
            stbuf->st_atime = info["st_atime"].asInt();
            stbuf->st_mtime = info["st_mtime"].asInt();
            stbuf->st_size = info["st_size"].asInt();
            stbuf->st_nlink = info["st_nlink"].asInt();
            stbuf->st_uid = info["st_uid"].asInt();
            stbuf->st_gid = info["st_gid"].asInt();
            cout << stbuf->st_size << endl;
        } else {
            FILE_LOG(LOG_ERROR) << "File not Exists!" << endl;
            return -errno;
        }
    } else {
        FILE_LOG(LOG_ERROR) << "Parameter Error!" << endl;
        return -errno;
    }
    return 0;
}

int client_open(char *inputOrder) {
    FILE_LOG(LOG_DEBUG) << "client_open" << endl;
    send(sock, inputOrder, strlen(inputOrder), 0);
    Json::Value root;
    Json::Reader reader;
    char buffer[1024];
    memset(buffer, '\0', sizeof buffer);
    read(sock, buffer, 1024);
    if (reader.parse(buffer, root)) {
        if (root["issucess"].asInt() == 1) {
            return 0;
        } else {
            FILE_LOG(LOG_ERROR) << "File not exists" << endl;
            return -errno;
        }
    } else {
        FILE_LOG(LOG_ERROR) << "Parameter Error!" << endl;
        return -errno;
    }

}

int client_read(char *inputOrder, char *buf) {
    vector<string> v;
    SplitString(inputOrder, v, " ");
    int size = stoi(v[2]);
    FILE_LOG(LOG_DEBUG) << "client_read" << endl;
    send(sock, inputOrder, strlen(inputOrder), 0);
    int len;
    Json::Reader reader;
    Json::Value root;
    char buffer[size+1024];
    char read_buf[size];
    memset(buffer, '\0', sizeof read_buf);
    read(sock, buffer, sizeof buffer);
    if (reader.parse(buffer, root)) {
        if (root["issucess"].asInt() == 1) {
            strcpy(read_buf, root["buf"].asCString());
//            FILE_LOG(LOG_DEBUG)<< read_buf<< "  "<< root["readlen"].asInt()<< endl;
            strcpy(buf, read_buf);
            return root["readlen"].asInt();
        } else {
            FILE_LOG(LOG_ERROR)<< "File not exists!"<< endl;
            return -errno;
        }
    } else {
        FILE_LOG(LOG_ERROR) << "Parameter Error!" << endl;
        return -errno;
    }
}
