#ifndef SYSTEM_STATUS_H_
#define SYSTEM_STATUS_H_

#include <Arduino.h>
#include "systemStructures.h"

typedef struct SYSTEM_STATUS {
	
    DbTaskManager taskManager;
    DbPlayerStatus player;
    Config_t config;
    Flags_t flags;
    MachineStatus machine;
} SystemStatus;

void systemStatus_initialize(SystemStatus* systemStatus);
SystemStatus* systemSystem_getSystemStatus();

#endif /* SYSTEM_STATUS_H_ */