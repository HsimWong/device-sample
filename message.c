#include "message.h"
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>


#define ENTRY_MAX_LENGTH 0x200

void hello() {
    printf("Hello, world");
}


// {"Type": "%s", "Info": "{\"DeviceCategoryType\": \"%s\", \"DeviceBlockNum\": \"%s\", \"AcessPoint\": \"%s\", \"RegisterType\": \"%s\", \"Envs\": {}, \"Mounts\": {}}"}


const char *registerMessageTemplate = "{\"Type\": \"%s\", \
\"Info\": \"{\\\"DeviceCategoryType\\\": \\\"%s\\\", \
\\\"DeviceBlockNum\\\": \\\"%s\\\", \\\"AcessPoint\\\": \\\"%s\\\", \
\\\"RegisterType\\\": \\\"%s\\\", \\\"Envs\\\": {%s}, \\\"Mounts\\\": \
{%s}}\"}\n";

    
// {"Type": "Report","Info": {"DeviceType": "%s","GroupID": "%s","BlockStatuses": [%s]}}

const char *reportMessageTemplate = "{\"Type\": \"Report\",\"Info\": \
{\"DeviceType\": \"%s\",\"AccessPoint\": \"%s\",\"BlockStatuses\": [%s]}}";

void getRegisterMessage
(const char *DeviceCategory, const int DeviceBlockNum, 
const char *AccessPoint, const char *RegisterType, 
const char **EnvKeys, const char **EnvValues, const int EnvLength,
const char **MountKeys, const char **MountValues, const int MountLength,
char **regisMsg) {
    char * envs = malloc(sizeof(char) * MAX_MSG_LENGTH);
    envs[0] = '\0';
    const char *envtemplate = "\\\"%s\\\": \\\"%s\\\"";
    for (int i = 0; i < EnvLength; i++) {
        char *env = malloc(sizeof(char) * ENTRY_MAX_LENGTH);
        sprintf(env, envtemplate, EnvKeys[i], EnvValues[i]);
        strcat(envs, env);
        if (i == (EnvLength - 1)) {
            strcat(envs, ", ");
        }
        free(env);
    }
    char *mounts = malloc(sizeof(char) * ENTRY_MAX_LENGTH);
    mounts[0] = '\0';
    // const 
    for (int i = 0; i < MountLength; i++) {
        char *mount = malloc(sizeof(char) * ENTRY_MAX_LENGTH);
        sprintf(mount, envtemplate, MountKeys[i], MountValues[i]);
        strcat(mounts, mount);
        if (i == (MountLength -1 )) {
            strcat(mount, ", ");
        }
        free(mount);
    }



    char *regisMsgTarget = malloc(sizeof(char) * 2 * MAX_MSG_LENGTH);
    sprintf(regisMsgTarget, registerMessageTemplate, 
        "Register", DeviceCategory, DeviceBlockNum, AccessPoint, RegisterType, envs, mounts);
    free(mounts);
    free(envs);
    *regisMsg = regisMsgTarget;   
}

void getReportMessage
(const char *DeviceType, const char *GroupID,
int *statuses, const int blockNum, char **reportMsg) {
    char *insertList = malloc(sizeof(char) * (blockNum * 2 - 1));
    for (int i = 0; i < blockNum; i++) {
        insertList[2 * i] = statuses[i] + 0x30;
        insertList[2*i+1] = (i == (blockNum - 1) ? '\0' : ',');
    }
    char *result = malloc(sizeof(char) * MAX_MSG_LENGTH);
    sprintf(result, reportMessageTemplate, DeviceType, GroupID, insertList);
    *reportMsg = result;    
}


