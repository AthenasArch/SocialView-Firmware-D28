#ifndef SYSTEM_STRUCTURES_H_
#define SYSTEM_STRUCTURES_H_

#include <Arduino.h>
#include "Database/Structures/systemConstants.h"
#include "modules/eeprom/MAP_FLASH.h"
#include <string>
#include <iostream>
#include <map>

// typedef enum DB_ALARM{
//     ERROR_NONE_MACHINE_OK = 0,
//     ERROR_GENERIC = 1
// } DbAlarm;

// typedef struct DB_UC_STATUS{
//     uint8_t cntTimeMillis;
// } DbUcStatus;

// // typedef enum DB_GETWAY_STATUS{
// //     GATEWAY_AP_MODE_START       = 0,
// //     GATEWAY_TRY_CONNECT_MODEM   = 1,
// //     // GETEWAY_ERROR_CONNECT_MODEM,
// //     GATEWAY_MODEM_CONNECTED     = 2,
// //     GATEWAY_CONNECT_SERVER_OK   = 3,
// //     GATEWAY_SENDING_POST_OK     = 4,
// //     GATEWAY_ERROR_SEND_POST     = 5
// // }DbGetwayStatus;

// // typedef struct NETWORK_STATUS{
// //     NetMode mode;
// //     NetAccessPoint netAccessPoint;
// //     NetServer netServer;
// //     DbGetwayStatus status;
// //     uint8_t buff_SSID[FLASH_SSID_LEN]; 
// // 	uint8_t buff_PASS[FLASH_PASS_LEN];
// //     uint8_t buff_TimeSendData[FLASH_SEND_TIME_LEN];

// //     unsigned long TIME_SEND_PACK;
// // }NetworkStatus;


// typedef enum DB_ELM_COMM_STATUS{
//     IDLE = 0, 
//     CONNECTING, 
//     CONNECTED, 
//     DISCONNECTED,
//     CONN_FAIL
// } DbElmCommStatus;

// typedef enum ELM327_STATUS {
//     ELM_MSG_SUCCESS           = 0,
//     ELM_MSG_NO_RESPONSE       = 1,
//     ELM_MSG_BUFFER_OVERFLOW   = 2,
//     ELM_MSG_GARBAGE           = 3,
//     ELM_MSG_UNABLE_TO_CONNECT = 4,
//     ELM_MSG_NO_DATA           = 5,
//     ELM_MSG_STOPPED           = 6,
//     ELM_MSG_TIMEOUT           = 7,
//     ELM_MSG_GENERAL_ERROR     = -1
// } Elm327Status;

// extern const char* ELM327_STATUS_MESSAGES[];

// typedef struct DB_ELM_STATUS{
//     int attempts;
//     DbElmCommStatus communication; // status da comunicacao com o ELM
//     Elm327Status geral; // status apos estar conectado ao ELM
// }DbElmStatus;

// typedef struct DB_OBD_VALUE{
//     float voltBat;
//     float rpm;
//     float fuelLeve; // nivel do combustivel
//     uint32_t speed; // km por hora
//     float temp;
// }DbObdValue;

/*configurações diversas*/
typedef struct CONFIG {
    std::string wifi_ssid;
    std::string wifi_passwd;
    std::string webserverIp;
    std::string i_user;
    int i_follow;
    int i_followers;
    std::string y_api_key;
    std::string y_channel_id;
    std::string y_channel_name;
    int y_view_count;
    int y_subscrible_count;
    std::string git_user;
    std::string git_name;
    int git_followers;
    int git_following;

    std::string street_address;
}Config_t;

/*flags de status de operaçao do sistema*/
typedef struct FLAGS {
    bool wifi_connected;
    std::map<int, int> servo_pos;
}Flags_t;


typedef enum SD_CARD_COMMUNICATION {
    SD_CARD_OK          = 0,
    SD_CARD_FAIL_OPEN   = 1,
    SD_CARD_FAIL_JSON   = 2
} SdCardCommunication;

/*flags de status de operaçao do sistema*/
typedef struct DB_SD_CARD_STATUS {
    SdCardCommunication status; // qualidade do sinal do wifi
}DbSdCardStatus;

/*flags de status de operaçao do sistema*/
typedef struct DB_WIFI_STATUS {
    uint8_t signal; // qualidade do sinal do wifi
}DbWifiStatus;

/*flags de status de operaçao do sistema*/
typedef struct DB_DISPLAY_STATUS {
    char msgBuff[150];
}DbDisplayStatus;

typedef struct MACHINE_STATUS{
    uint8_t cnt;
    DbDisplayStatus display;
    DbWifiStatus wifi;
    DbSdCardStatus sdCard;
    // uint8_t currPage;
    // DbElmStatus elmStatus;
    // DbObdValue carValue;
}MachineStatus;

typedef struct DB_PLAYER_STATUS{
    bool pauseResum; /* 0 or 1 */
    uint8_t volume; /* 0 a 21 */
    char musicName[20]; /* nome da musica tocando */
}DbPlayerStatus;


typedef struct DB_TASK_STATUS{
    bool display; /* 0 or 1 */
    bool wifi;
    bool webServer;
    bool player;
    bool socialView;
} DbTaskStatus;

typedef struct DB_TASK_HANDLER{
    TaskHandle_t display;
    TaskHandle_t wifi;
    TaskHandle_t webServer;
    TaskHandle_t player;
    TaskHandle_t socialView;
} DbTaskHandler;

typedef struct DB_TASK_MANAGER{
    DbTaskStatus status;
    DbTaskHandler handler;
} DbTaskManager;


#endif /* SYSTEM_STRUCTURES_H_ */