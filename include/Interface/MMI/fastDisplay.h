#ifndef FAST_DISPLAY_H_
#define FAST_DISPLAY_H_

/* MAN-MACHINE INTERFACE */

#include <Arduino.h>
#include "Database/Structures/systemStatus.h"

void fastDisplay_ini(SystemStatus*systemStatus);
void fastDisplay_run(SystemStatus*systemStatus);

#endif /* FAST_DISPLAY_H_ */