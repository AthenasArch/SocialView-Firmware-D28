#include "Hardware/hardware.h"
#include <Arduino.h>

void ini_digitalOutputs(void);
void ini_digitalInputs(void);
void ini_analog(void);
void ini_pwm(void);

void hardware_initialize(void){
    ini_digitalOutputs();
    ini_digitalInputs();
    ini_analog();
    ini_pwm();
}

void ini_digitalOutputs(void){

}

void ini_digitalInputs(void){

}

void ini_analog(void){

}

void ini_pwm(void){

}