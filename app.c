#include <stdio.h>
#include "comm.h"
#include "message.h"
#define DEST_PORT 60000
#define DEST_IP "127.0.0.1"
#define MAX_DATA 1024




int main(int argc, char const *argv[]) {
    senderContext *sc = malloc(sizeof(senderContext));
    senderPrepare(sc, DEST_IP, DEST_PORT);
 
    char *regisMsg;
    getRegisterMessage("pixeldummy", 
        7, "Shannon.exe", "Block", &regisMsg);
    printf("RegisMsg: %s", regisMsg);

    char *retMsg;
    sendJson(sc, regisMsg);

    return 0;
}
