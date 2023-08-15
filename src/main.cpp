
/*Biblioteca do Arduino*/
#include <Arduino.h>
#include <main.h>
#include "Database/Structures/systemStatus.h"
#include "MachineManager/machineManager.h"
#include "Database/Structures/systemInformation.h"
#include "esp32-hal-cpu.h"

#define MAIN_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef MAIN_DEBUG_ENABLE
    #define MAIN_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
    #define MAIN_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
    #define DEBUG_SERIAL_BEGIN(a)    Serial.begin(a)
#else
    #define MAIN_DEBUG_PRINT(...) {}
    #define MAIN_DEBUG_PRINTLN(...) {}
    #define DEBUG_SERIAL_BEGIN(a)    do{}while(0)
#endif

SystemStatus systemStatus;

void debugMain(void);

void setup() {

    // setCpuFrequencyMhz(240);
    delay(100);
    DEBUG_SERIAL_BEGIN(115200); //configura comunicação serial com baudrate de 115200
    debugMain();
    
    machineManager_ini(&systemStatus);
}

void loop() {

    machineManager_run(&systemStatus);
}

void debugMain(void){
    MAIN_DEBUG_PRINT("\r\r\n\nFirmware Version: ");
    MAIN_DEBUG_PRINTLN(FIRMWARE_VERSION);
    MAIN_DEBUG_PRINT("LAST COMPILE TM: ");
    MAIN_DEBUG_PRINTLN(COMPILE_TM);
    MAIN_DEBUG_PRINT("CPU FREQ: ");
    MAIN_DEBUG_PRINTLN(getCpuFrequencyMhz());
    MAIN_DEBUG_PRINTLN("\r\n");
}


// #include <Arduino.h>
// #include <lv_conf.h>
// #include <lvgl.h>

// #include "gui/gui.h"

// /*Bibliotecas FreeRTOS */
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"

// // Declare uma variável global para armazenar o valor do slider
// int sliderValue = 0;

// void displayTask_run_(void* pvParameters);
// void debugMemTask_(void);

// void setup() {
//     Serial.begin(115200);
//     Serial.print("Serial inicializada");

//     xTaskCreatePinnedToCore(displayTask_run_, "display Task", 70 * 1024, NULL, 1, NULL, 1);
// }

// void loop() {
    

//     vTaskDelay(pdMS_TO_TICKS(1000));
//     // static unsigned long myTimer = millis();

    
//     // if (millis() - myTimer > 1000 ){
//     //     myTimer = millis();
//     //     Serial.print("CNT = ");
//     //     Serial.println(myTimer/1000);
//     // }
// }

// void displayTask_run_(void* pvParameters){
//     gui_start();

//     while (1) {
//         lv_timer_handler();
//         debugMemTask_();
        
//         // Feed the watchdog
//         // esp_task_wdt_reset();
//     }
// }

// void debugMemTask_(void){
//     UBaseType_t uxHighWaterMark;
//     static unsigned long oldTime;

//     if (millis() - oldTime > 500 ) {
//         oldTime = millis();
//         uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
//         printf("DISPLAY - Minimum free stack space for DISPLAY : %lu bytes\n", uxHighWaterMark);   
//     }
// }

