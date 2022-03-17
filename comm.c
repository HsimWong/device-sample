#include <stdio.h>
#include<errno.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<json-c/json.h>
#include <string.h>
#include "comm.h"

void senderPrepare(senderContext *sc, char *destIP, int destPort) {

    sc->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sc->sockfd==-1){
    	printf("socket failed:%d",errno);
    }
    sc->destAddr = malloc(sizeof(struct sockaddr_in));
    sc->destAddr->sin_family = AF_INET;
    sc->destAddr->sin_port = htons(60000);
    printf("Received port: %d\n", sc->destAddr->sin_port);
    sc->destAddr->sin_addr.s_addr = inet_addr(destIP);
    bzero(&(sc->destAddr->sin_zero),8);
}


ssize_t sendJson(senderContext *sc, char *obj) {
    ssize_t sentSize = 0;
    if(connect(sc->sockfd, (struct sockaddr*)(sc->destAddr),
        sizeof(struct sockaddr)) == -1){
    	printf("connect failed:%d",errno);
    } else {
        sentSize = send(sc->sockfd, obj, strlen(obj),0);
        printf("send success\n");

        char recv[1024];
        memset(recv, 0, sizeof(recv));
        if (read(sc->sockfd, recv, sizeof(recv)) < 0) {
            perror("cannot read");
            exit(4);
        }
        printf("Received %s from server\n", recv);


    }
    close(sc->sockfd);
    return sentSize;
}




void senderRelease(senderContext *sc) {
    free(sc->destAddr);
    free(sc);
}


