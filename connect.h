//
// Created by anson on 18-11-28.
//

#ifndef NDNFS_CLIENT_CONNECT_H
#define NDNFS_CLIENT_CONNECT_H

#include "ndnfs-client.h"

int client_getattr(char * inputOrder,  struct stat * stbuf);

int client_open(char *inputOrder);

int client_read(char *inputOrder, char * buf);

int client_write(char *inputOrer);

int client_release(char *inputOrder);

#endif //NDNFS_CLIENT_CONNECT_H
