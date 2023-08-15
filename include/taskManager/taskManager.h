#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include <Arduino.h>
#include "Database/Structures/systemStatus.h"

void taskMAnager_init(SystemStatus* systemStatus);
void taskManager_run(SystemStatus* systemStatus);

#endif /* TASK_MANAGER_H_ */