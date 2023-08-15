#include "taskManager/taskManager.h"
/*Bibliotecas FreeRTOS */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/*Tasks do sistema*/
#include "taskManager/Tasks/wifi.hpp"
#include "taskManager/Tasks/webserver.hpp"
#include "taskManager/Tasks/displayTask.h"
#include "taskManager/Tasks/socialView.hpp"
#include "taskManager/Tasks/playerTask.h"
#include "Interface/MMI/mmi.h"
#include "taskManager/Tasks/fastDisplayTask.h"

void iniTaskStatus(SystemStatus *systemStatus);

/**
 * @brief inicializamos todas as tasks do sistema aqui.
 * 
 * @param systemStatus 
 * 
 * @return void
*/
void taskMAnager_init(SystemStatus *systemStatus){
    
    iniTaskStatus(systemStatus);

    // xTaskCreatePinnedToCore(displayTask_run, "display Task", 68 * 1024, systemStatus, 2,  &(systemStatus->taskManager.handler.display), APP_CPU_NUM);
    xTaskCreatePinnedToCore(fastDisplayTask_run, "display Task", 68 * 1024, systemStatus, 2,  NULL, APP_CPU_NUM);
    /*criação das tasks*/
    xTaskCreatePinnedToCore(wifi_task,"Wifi Task", 3 * 1024, systemStatus, 1, NULL, APP_CPU_NUM);
    xTaskCreatePinnedToCore(webserver_task, "webserver Task", 7 * 1024, systemStatus, 1, NULL, PRO_CPU_NUM);
    // xTaskCreatePinnedToCore(socialView_task, "social view Task", 10 * 1024, systemStatus, 1, NULL, APP_CPU_NUM); 
    // xTaskCreatePinnedToCore(playerTask_run, "player Task", (10 * 1024), systemStatus, 1, NULL, APP_CPU_NUM);
}

/**
 * @brief aqui e o loop infinito do gerenciados das tasks.
 * 
 * @param systemStatus 
 * 
 * @return void
*/
void taskManager_run(SystemStatus* systemStatus){
    // mmi_run(systemStatus);
    // vTaskDelay(pdMS_TO_TICKS(1000));
    vTaskDelay(1);
}

void iniTaskStatus(SystemStatus *systemStatus){
    systemStatus->taskManager.status.display = 0;
}