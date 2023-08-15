#include "taskManager/Tasks/displayTask.h"
#include "Interface/MMI/mmi.h"
#include "Interface/MMI/fastDisplay.h"

void debugMemTask(void);

void displayTask_run(void* pvParameters){

    SystemStatus *systemStatus = (SystemStatus *)pvParameters;

    Serial.println("Inicializa o LVGL\n\n");
    mmi_initialize(systemStatus);

    for (;;) {
        mmi_run(systemStatus);
    }
    
}

void debugMemTask(void){
    UBaseType_t uxHighWaterMark;
    static unsigned long oldTime;

    if (millis() - oldTime > 500 ) {
        oldTime = millis();
        uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        printf("DISPLAY - Minimum free stack space for wifi_task: %lu bytes\n", uxHighWaterMark);   
    }
}
