#include <Arduino.h>
#include "Interface/MMI/mmi.h"
#include <lv_conf.h>
#include <lvgl.h>

#include "gui/gui.h"

lv_obj_t *ui_Chat2;
lv_obj_t *ui_Alarm_Comp;
lv_obj_t *ui_Alarm_Comp1;
lv_obj_t *ui_Alarm_Comp2;

void btnTaskManager(SystemStatus *systemStatus);
void displayMsgInfo(SystemStatus *systemStatus);

void mmi_initialize(SystemStatus *systemStatus) {
    Serial.print("mmi_initialize");
    gui_start();
}

void mmi_run(SystemStatus *systemStatus){

    lv_timer_handler();

    // debugMemTask();
    btnTaskManager(systemStatus);
    displayMsgInfo(systemStatus);
   
}



void btnTaskManager(SystemStatus *systemStatus){
    
    static unsigned long pressTime_ui_Alarm_Comp = 0;
    static unsigned long pressTime_ui_Alarm_Comp1 = 0;
    static bool ui_Alarm_Comp_Flag = false; 
    static bool ui_Alarm_Comp1_Flag = false;

    // Se o botão ui_Alarm_Comp for pressionado
    if(lv_obj_get_state(ui_Alarm_Comp) & LV_STATE_PRESSED) {
        // Se a flag não estiver definida (início do pressionamento)
        if(!ui_Alarm_Comp_Flag) {
            pressTime_ui_Alarm_Comp = millis();
            ui_Alarm_Comp_Flag = true;
        }
        // Se a diferença de tempo desde o início do pressionamento for maior que 2 segundos
        else if(millis() - pressTime_ui_Alarm_Comp > 2000) {
            Serial.println("0 switch LIGADO por mais de 2 segundos");
            systemStatus->taskManager.status.display = !systemStatus->taskManager.status.display;
            // Altera o status de alguma variável booleana aqui
            // variavelBooleana = !variavelBooleana; 
            ui_Alarm_Comp_Flag = false; // Reseta a flag
        }
    } 
    else {
        ui_Alarm_Comp_Flag = false; // Reseta a flag se o botão não estiver pressionado
    }

    // O mesmo pode ser feito para o botão ui_Alarm_Comp1
    if(lv_obj_get_state(ui_Alarm_Comp1) & LV_STATE_PRESSED) {
        if(!ui_Alarm_Comp1_Flag) {
            pressTime_ui_Alarm_Comp1 = millis();
            ui_Alarm_Comp1_Flag = true;
        }
        else if(millis() - pressTime_ui_Alarm_Comp1 > 2000) {
            Serial.println("1 switch LIGADO por mais de 2 segundos");
            systemStatus->taskManager.status.player = !systemStatus->taskManager.status.player;
            // Altera o status de alguma variável booleana aqui
            // variavelBooleana = !variavelBooleana; 
            ui_Alarm_Comp1_Flag = false;
        }
    } 
    else {
        ui_Alarm_Comp1_Flag = false;
    }
}

void displayMsgInfo(SystemStatus *systemStatus){

    static unsigned long timerDebugMsg = 0;
    const unsigned long TIME_DEBUG_MSG = 500;

    if ( millis() - timerDebugMsg > TIME_DEBUG_MSG ){
        timerDebugMsg = millis();

        sprintf(systemStatus->machine.display.msgBuff,"CNT: %d\n - Display: %d\nPlayer: %d",
            (timerDebugMsg / TIME_DEBUG_MSG),
            systemStatus->taskManager.status.display, 
            systemStatus->taskManager.status.player
            ); 
        lv_label_set_text(ui_Chat2, systemStatus->machine.display.msgBuff);
    } 
}