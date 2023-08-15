#ifndef SD_SERVER_MANAGER_H_
#define SD_SERVER_MANAGER_H_

#include <Arduino.h>
#include "Database/Structures/systemStatus.h"

void sdServerManager_ini(SystemStatus* systemStatus);
bool sdcard_loadConfig(SystemStatus *systemStatus);

#endif /* SD_SERVER_MANAGER_H_ */