//
// Created by anson on 18-11-28.
//
#include <sys/stat.h>
#include "connect.h"

using namespace std;

int getattr(char * inputOrder, struct stat * stbuf) {
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
            cout<< stbuf->st_size<< endl;
        } else {
            FILE_LOG(LOG_ERROR)<<"Parameter Error!";
            return -errno;
        }
    }
    return 0;
}
