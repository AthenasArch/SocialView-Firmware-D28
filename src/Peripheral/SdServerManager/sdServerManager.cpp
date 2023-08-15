#include "Peripheral/SdServerManager/sdServerManager.h"
#include <SD.h>
#include <ArduinoJson.h> /*Lib interpretador json*/
#include "Hardware/hardware.h"

#define SD_SERVER_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef SD_SERVER_DEBUG_ENABLE
    #define SD_SERVER_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
    #define SD_SERVER_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#else
    #define SD_SERVER_DEBUG_PRINT(...) {}
    #define SD_SERVER_DEBUG_PRINTLN(...) {}
#endif

static bool sdcart_init(void);

SPIClass spiSD(VSPI); // FSPI - Da PSRAM / Do display = HSPI / VSPI - Do touch / 

void sdServerManager_ini(SystemStatus* systemStatus){

    SD_SERVER_DEBUG_PRINTLN(F("\r\nInicializando o gerenciador de servidor SD"));

    //Inicializa o cartão SD
    if(!sdcart_init()) { 
        SD_SERVER_DEBUG_PRINTLN(F("\r\nFalha na inicialização do cartão SD"));
        systemStatus->machine.sdCard.status = SD_CARD_FAIL_OPEN;
        return;
    } else {
        systemStatus->machine.sdCard.status = SD_CARD_OK;
    }

    sdcard_loadConfig(systemStatus);

    return;
}

/**
 * @brief inicializa o hardware do cartao SD
 * 
 * @param
 * 
 * @return
*/
static bool sdcart_init() {
  
    pinMode(PIN_SDCARD_CS, OUTPUT);

    SD_SERVER_DEBUG_PRINTLN(F("\r\nInicializando hardware do cartao SD..."));
    
    spiSD.begin(PIN_SDCARD_CLK, PIN_SDCART_MISO, PIN_SDCART_MOSI);
  
    if (!SD.begin(PIN_SDCARD_CS, spiSD, SPI_SD_CARD_SPEED)) {
        SD_SERVER_DEBUG_PRINTLN(F("Falha ao montar o cartao SD"));
        return false;
    } else {
        SD_SERVER_DEBUG_PRINTLN(F("Cartão SD montado com sucesso"));
        return true;
    }
}

/**
 * @brief Carrega informações do sistema
 * @param systemStatus status do sistema
 * @return
*/
bool sdcard_loadConfig(SystemStatus *systemStatus) {

    SD_SERVER_DEBUG_PRINTLN(F("iniciando Leitura do arquivo de configuracao..."));

    File configFile = SD.open("/config.json", "r");
    if (!configFile) {
        SD_SERVER_DEBUG_PRINTLN(F("\r\nFalha ao abrir o arquivo de configuracao"));
        systemStatus->machine.sdCard.status = SD_CARD_FAIL_OPEN; 
        return false;
    }

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonDocument<200> doc;
    auto error = deserializeJson(doc, buf.get());
    
    if (error) {
        SD_SERVER_DEBUG_PRINTLN(F("\r\nFalha ao interpretar o arquivo de configuracao"));
        systemStatus->machine.sdCard.status = SD_CARD_FAIL_JSON; 
        return false;
    } else {
        SD_SERVER_DEBUG_PRINTLN(F("\r\nSD arquivo de configuracao - OK"));
    }
    
    const char* ssid = doc["wifi"]["ssid"];
    const char* password = doc["wifi"]["password"];
    const char* api_key = doc["youtube"]["api_key"];
    const char* channel_id = doc["youtube"]["channel_id"];
    // const char* insta_user = doc["instagram"]["user"];
    // const char* git_user = doc["github"]["user"];
    
    SD_SERVER_DEBUG_PRINTLN(F("\r\nConfiguracao carregada com sucesso:"));
    SD_SERVER_DEBUG_PRINT(F("SSID: ")); SD_SERVER_DEBUG_PRINTLN(ssid);
    SD_SERVER_DEBUG_PRINT(F("Password: ")); SD_SERVER_DEBUG_PRINTLN(password);
    SD_SERVER_DEBUG_PRINT(F("API Key: ")); SD_SERVER_DEBUG_PRINTLN(api_key);
    SD_SERVER_DEBUG_PRINT(F("Channel ID: ")); SD_SERVER_DEBUG_PRINTLN(channel_id);
    // SD_SERVER_DEBUG_PRINT(F("Insta: ")); SD_SERVER_DEBUG_PRINTLN(insta_user);
    // SD_SERVER_DEBUG_PRINT(F("GitHub: ")); SD_SERVER_DEBUG_PRINTLN(git_user);

    // encoding
    systemStatus->config.wifi_ssid.assign(ssid);
    systemStatus->config.wifi_passwd.assign(password);
    systemStatus->config.y_api_key.assign(api_key);
    systemStatus->config.y_channel_id.assign(channel_id);
    // systemStatus->config.i_user.assign(insta_user);
    // systemStatus->config.git_user.assign(git_user);

    configFile.close();
    // Do something with the variables loaded from the JSON file

    systemStatus->machine.sdCard.status = SD_CARD_OK;

    SD_SERVER_DEBUG_PRINTLN(F("\r\nConfiguração aplicada com sucesso"));
    return true;
}