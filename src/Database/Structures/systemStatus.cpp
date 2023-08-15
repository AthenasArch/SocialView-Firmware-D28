#include "Database/Structures/systemStatus.h"
#include "Database/Structures/systemStructures.h"
#include <Arduino.h>

const char* ELM327_STATUS_MESSAGES[] = {
    "Success",
    "No Response",
    "Buffer Overflow",
    "Garbage",
    "Unable to Connect",
    "No Data",
    "Stopped",
    "Timeout",
    "General Error"
};

// static SystemStatus* _systemStatus = NULL;
 SystemStatus* _systemStatus = NULL;

/*
 * @Method: inicialize o conteudo de status do projeto
 * 
 * @Param: * struct de status
 * 
 * @return: void
 */
void systemStatus_initialize(SystemStatus* systemStatus) {
    memset(systemStatus, 0, sizeof (SystemStatus));
}

SystemStatus* systemSystem_getSystemStatus() {
    return _systemStatus;
}