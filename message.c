#include "message.h"
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>


// {"Type": "%s", "Info": {"DeviceCategoryType": "%s", "DeviceBlockNum": %d, "AccessPoint": "%s", "RegisterType": "%s"}
// }

const char *registerMessageTemplate = "{\"Type\": \"%s\", \"Info\": \
    {\"DeviceCategoryType\": \"%s\", \"DeviceBlockNum\": %d, \
    \"AccessPoint\": \"%s\", \"RegisterType\": \"%s\"}}\n";

    

void getRegisterMessage
(const char *DeviceCategory, const int DeviceBlockNum, 
const char *AccessPoint, const char *RegisterType, 
char **regisMsg) {
    char *regisMsgTarget = malloc(sizeof(char) * MAX_MSG_LENGTH);
    sprintf(regisMsgTarget, registerMessageTemplate, 
        "Register", DeviceCategory, DeviceBlockNum, AccessPoint, RegisterType);
    *regisMsg = regisMsgTarget;   
}


