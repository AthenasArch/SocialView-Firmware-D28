#ifndef HARDWARE_DEFINITION_H_
#define HARDWARE_DEFINITION_H_

// #include "Hardware/hardware.h"

#include <Arduino.h>
#include <stdio.h.>
#include <stdlib.h>
#include <string.h>

#define PIN_BUZZER

// #define ELM_PORT Serial1
// #define PIN_ELM_RXD2 17
// #define PIN_ELM_TXD2 18

/*Definição dos pinos do cartão SD*/
#define PIN_SDCARD_CS   5
#define PIN_SDCARD_CLK  18
#define PIN_SDCART_MISO 19
#define PIN_SDCART_MOSI 23

#define SPI_SD_CARD_SPEED 60000000 /* frequencia do SPI */
// #define SPI_SD_CARD_SPEED 40000000 /* frequencia do SPI */
//  #define SPI_SD_CARD_SPEED 20000000 /* frequencia do SPI */

void hardware_initialize(void);

#endif /* HARDWARE_DEFINITION_H_ */
