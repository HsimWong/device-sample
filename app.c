#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "comm.h"
#include "message.h"
#define DEST_PORT 60000
#define DEST_IP "127.0.0.1"
#define MAX_DATA 1024




int main(int argc, char const *argv[]) {
    senderContext *sc = malloc(sizeof(senderContext));
    senderPrepare(sc, DEST_IP, DEST_PORT);
 

    // char **mountKey
    char *regisMsg;
    getRegisterMessage("pixeldummy", 
        7, "Shannon.exe", "DeviceType", 
        NULL, NULL, 0, NULL, NULL, 0,&regisMsg);
    printf("RegisMsg: %s", regisMsg);

    char *retMsg;
    
    sendJson(sc, regisMsg, &retMsg);

    printf("Sleeping for 1 second.\n");
    sleep(2);
    // senderPrepare(sc, DEST_IP, DEST_PORT);


    // int *statuses = malloc(sizeof(int) * 7);
    // for (int i = 0; i < 7; i++) {
    //     statuses[i] = i%2;
    // }
    // char *reportMsg;
    // getReportMessage("pixeldummy", "Shannon.exe", statuses, 7, &reportMsg);
    // printf("ReportMsg: %s", reportMsg);
    // sendJson(sc, reportMsg, &retMsg);


    // printf("Sleeping for 1 second.\n");
    // sleep(5);
    // senderPrepare(sc, DEST_IP, DEST_PORT);


    // statuses = malloc(sizeof(int) * 7);
    // for (int i = 0; i < 7; i++) {
    //     statuses[i] = !i%2;
    // }
    // reportMsg;
    // getReportMessage("pixeldummy", "Shannon.exe", statuses, 7, &reportMsg);
    // printf("ReportMsg: %s", reportMsg);
    // sendJson(sc, reportMsg, &retMsg);
    return 0;
}
