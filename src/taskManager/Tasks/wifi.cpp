#include <Arduino.h>
#include <WiFi.h> /*Biblioteca Wifi*/
#include "taskManager/Tasks/wifi.hpp" /*header do arquivo*/
#include <ESPmDNS.h>  // Adicione essa biblioteca para suporte ao mDNS

#define WIFI_TASK_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef WIFI_TASK_DEBUG_ENABLE
    #define WIFI_TASK_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
    #define WIFI_TASK_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
    #define WIFI_TASK_DEBUG_PRINTF(...) { Serial.printf(__VA_ARGS__); }
#else
    #define WIFI_TASK_DEBUG_PRINT(...) {}
    #define WIFI_TASK_DEBUG_PRINTLN(...) {}
    #define WIFI_TASK_DEBUG_PRINTF(...) { }
#endif

/******************************************
 * Protótipos de Funções
 ******************************************/

static void OnWiFiEvent(WiFiEvent_t event);
static void wifi_init ();
static void wifi_maintenance (SystemStatus *systemStatus);
static void wifi_enable_access_point();
static void wifi_disable_access_point();

/**
 * Eventos recebidos do wifi, util para identificar ceonexão e desconexão
 * 
*/
void OnWiFiEvent(WiFiEvent_t event) {

    switch (event) {

        case SYSTEM_EVENT_STA_CONNECTED:
            WIFI_TASK_DEBUG_PRINT("Conectado: ");
            WIFI_TASK_DEBUG_PRINTLN(WiFi.SSID());
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            WIFI_TASK_DEBUG_PRINT("Webserver IP: ");
            WIFI_TASK_DEBUG_PRINTLN(WiFi.localIP());
            break;
        case SYSTEM_EVENT_AP_START:
            WIFI_TASK_DEBUG_PRINTLN("ESP32 soft AP started");
            break;
        case SYSTEM_EVENT_AP_STACONNECTED:
            WIFI_TASK_DEBUG_PRINTLN("Station connected to ESP32 soft AP");
            break;
        case SYSTEM_EVENT_AP_STADISCONNECTED:
            WIFI_TASK_DEBUG_PRINTLN("Station disconnected from ESP32 soft AP");
            break;
        default: break;
    }
}

/**
 * Função de inicialização do wifi
*/
void wifi_init () {

    //Define o modo station e o modo access_point
    WiFi.mode(WIFI_MODE_APSTA);
    //Cadastra o handler de eventos do wifi
    WiFi.onEvent(OnWiFiEvent);
    return;
}

/**
 * Rotina que mantem a conexão wifi ativa ou 
 * quando necessário altera a rede wifi de destino
*/
void wifi_maintenance (SystemStatus *systemStatus) {

    String SSID = String(systemStatus->config.wifi_ssid.c_str());
    String PASSWD = String(systemStatus->config.wifi_passwd.c_str());
    


    if (WiFi.SSID() != SSID || WiFi.psk() != PASSWD) {
        WIFI_TASK_DEBUG_PRINTF("Conectando a rede: %s\r\n", SSID);
        if (WiFi.status() == WL_CONNECTED) {
           WiFi.disconnect(true);
        }
        WiFi.begin(SSID, PASSWD);
    }

    if (WiFi.status() == WL_CONNECTED) {
        systemStatus->flags.wifi_connected = true;
    } else {
        WiFi.begin(SSID, PASSWD);
    }
}

/**
 * Habilita o ponto de acesso
*/
void wifi_enable_access_point() {
    WiFi.softAP("ESTOU_AQUI", "");
}

/**
 * @brief Desabilita o ponto de Acesso
*/
void wifi_disable_access_point() {
    WiFi.softAPdisconnect(true);
}

/**
 * @brief Realiza a conexão WiFi
 * 
 * @param systemStatus
 * @param WIFI_SSID
 * @param WIFI_PASSWORD
 * 
 * @return void
*/
static void connect_wifi(SystemStatus *systemStatus, const char* WIFI_SSID, const char* WIFI_PASSWORD) {
    
    WIFI_TASK_DEBUG_PRINTLN("Conectando na rede WiFi...");
    
    // Conecta à rede WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Aguarda a conexão WiFi ser estabelecida
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(500); // Espera 500ms antes de verificar novamente
    }

    WIFI_TASK_DEBUG_PRINTLN("Conexão WiFi estabelecida!");

    systemStatus->flags.wifi_connected = true;
}



/*--- Lista as redes WIFI  ---*/
String wifiScanNet() {

    String result_json = "{\"wifiAccessPoints\": ["; 
    int numNetworks = WiFi.scanNetworks();
    Serial.println("Redes Wi-Fi encontradas:");
    
    // Exibe o endereço MAC de cada rede encontrada
    for (int i = 0; i < numNetworks; i++) {
        char wifi_info[70] = "";
        sprintf(wifi_info, "{\"macAddress\":\"%s\",\"signalStrength\": %d},", WiFi.BSSIDstr(i).c_str(), WiFi.RSSI(i));
        result_json += String(wifi_info);
    }
    result_json += String("]}");
    Serial.println(result_json);
    return result_json;
}



/**
 * @brief -
 * 
 * @param pvParameters
 * 
 * @return void
*/
void wifi_task(void *pvParameters){
    
    SystemStatus *systemStatus = (SystemStatus *)pvParameters;

    wifi_init();

    // char localIP[16];  // Buffer to hold the IP address string (max length 15 for an IPv4 address + null character)
    // snprintf(localIP, sizeof(localIP), "%s", WiFi.localIP().toString().c_str());
    // systemStatus->config.webserverIp = localIP;

    wifi_enable_access_point();

    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.softAP("ESTOU_AQUI", "");

    WIFI_TASK_DEBUG_PRINTLN("Iniciando task wifi");
    // Start a local timer.
    static unsigned long wifi_timeout = millis() - 5000;
    static unsigned long access_point_timeout = millis();

    // Agora, antes da tarefa terminar, verifique o uso da pilha.
    // UBaseType_t uxHighWaterMark;
        
    for (;;) {

        if (millis() - wifi_timeout >= 5000){
            wifi_maintenance(systemStatus);
            wifi_timeout = millis();
            systemStatus->config.webserverIp = WiFi.localIP().toString().c_str();
        }

        if (millis() - access_point_timeout >= 30000 && WiFi.getMode() == WIFI_MODE_APSTA &&
                systemStatus->flags.wifi_connected && WiFi.softAPgetStationNum() == 0) {
            WIFI_TASK_DEBUG_PRINTLN("Desligando Ponto de Acesso");
            WiFi.softAPdisconnect(true);
        }
        
        // uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        // printf("WIFI - Minimum free stack space for wifi_task: %lu bytes\n", uxHighWaterMark);
        vTaskDelay(500);
    }

}

