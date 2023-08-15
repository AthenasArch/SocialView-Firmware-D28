#include "MachineManager/machineManager.h"
#include "Hardware/hardware.h"
#include "Peripheral/SdServerManager/sdServerManager.h"
#include "taskManager/taskManager.h" 
#include "Interface/MMI/mmi.h"

#define MACHINE_MANAGER_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef MACHINE_MANAGER_DEBUG_ENABLE
    #define MACHINE_MANAGER_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
    #define MACHINE_MANAGER_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
    #define MACHINE_MANAGER_DEBUG_PRINT(...) {}
    #define MACHINE_MANAGER_DEBUG_PRINTLN(...) {}
#endif

void debugInfo(SystemStatus *systemStatus);
void cntClock(SystemStatus *systemStatus);

/**
 * @brief
 * 
 * @param
 * 
 * @return
*/
void machineManager_ini(SystemStatus *systemStatus){

    systemStatus->flags.wifi_connected = false;
    
    sdServerManager_ini(systemStatus);  //Carrega as informações do Cartão SD

    taskMAnager_init(systemStatus);

    MACHINE_MANAGER_DEBUG_PRINTLN("\r\nmachineManager_init(OK)");
}

/**
 * @brief
 * 
 * @param
 * 
 * @return
*/
void machineManager_run(SystemStatus *systemStatus){

    taskManager_run(systemStatus);

    debugInfo(systemStatus); // printa informacoes de debug

    cntClock(systemStatus);
}

void cntClock(SystemStatus *systemStatus){

    static unsigned long timerClock = 0;
    const unsigned long TIME_CLOCK = 1000;

    if (millis() - timerClock > TIME_CLOCK){
        timerClock = millis();
        systemStatus->machine.cnt++;
    }
}

void debugInfo(SystemStatus *systemStatus){
    
}




