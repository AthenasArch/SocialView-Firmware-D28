#ifndef MMI_H_
#define MMI_H_

/* MAN-MACHINE INTERFACE */

#include <Arduino.h>
#include "Database/Structures/systemStatus.h"

void mmi_initialize(SystemStatus*systemStatus);
void mmi_run(SystemStatus*systemStatus);

#endif /* IHM_H_ */