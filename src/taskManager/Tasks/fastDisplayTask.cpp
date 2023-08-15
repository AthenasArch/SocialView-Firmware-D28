#include "taskManager/Tasks/fastDisplayTask.h"
#include "Interface/MMI/fastDisplay.h"

void debugMemTask_(void);

void fastDisplayTask_run(void* pvParameters){

    SystemStatus *systemStatus = (SystemStatus *)pvParameters;

    Serial.println("Inicializa o Fast Display\n\n");
    fastDisplay_ini(systemStatus);

    for (;;) {
        fastDisplay_run(systemStatus);
        debugMemTask_();
    }
}

void debugMemTask_(void){
    UBaseType_t uxHighWaterMark;
    static unsigned long oldTime;

    if (millis() - oldTime > 500 ) {
        oldTime = millis();
        uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        printf("FAST DISPLAY - Minimum free stack space for fast_display_task: %lu bytes\n", uxHighWaterMark);   
    }
}
