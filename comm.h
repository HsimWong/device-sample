#ifndef COMM_H
#define COMM_H
#include<json-c/json.h>

typedef struct {
    int sockfd;
    struct sockaddr_in *destAddr;
} senderContext;


void senderPrepare(senderContext *sc, char *destIP, int destPort);
ssize_t sendJson(senderContext *sc, char *obj);
void senderRelease(senderContext *sc);



#endif