//
// Created by anson on 18-11-28.
//

#ifndef NDNFS_CLIENT_NDNFS_CLIENT_H
#define NDNFS_CLIENT_NDNFS_CLIENT_H
#include "sys/socket.h"
#include "bits/stdc++.h"
#include "iostream"
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "jsoncpp/json/json.h"
#include "logger.h"
#include "connect.h"

#include <assert.h>
#include <iostream>
#include <sstream>
#include <string>
#include <dirent.h>

#include <time.h>
#include <sys/time.h>
#include <utime.h>

#include <pthread.h>

extern int sock;

enum orders {
    DEFAULT, QUIT, SEND, GETATTR, OPEN, READ, WRITE, RELEASE
};


void usage();
orders getOrder(std::string order);
int init_socket(struct sockaddr_in &serv_addr);

inline void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}


#endif //NDNFS_CLIENT_NDNFS_CLIENT_H
