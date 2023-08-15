#ifndef PLAYER_TASK_H_
#define PLAYER_TASK_H_

#include <Arduino.h>
#include "Database/Structures/systemStatus.h"

void playerTask_run(void* pvParameters);

#endif /* PLAYER_TASK_H_ */