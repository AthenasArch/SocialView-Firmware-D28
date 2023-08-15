#include <Arduino.h>
#include <WiFi.h> /*Biblioteca Wifi*/
#include "taskManager/Tasks/socialView.hpp" /*header do arquivo*/
#include "taskManager/Tasks/wifi.hpp" /*header do arquivo*/
/*Biblioteca de autenticação*/
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define SOCIALVIEW_TASK_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef SOCIALVIEW_TASK_DEBUG_ENABLE
    #define SOCIALVIEW_TASK_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
    #define SOCIALVIEW_TASK_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
    #define SOCIALVIEW_TASK_DEBUG_PRINTF(...) { Serial.printf(__VA_ARGS__); }
#else
    #define SOCIALVIEW_TASK_DEBUG_PRINT(...) {}
    #define SOCIALVIEW_TASK_DEBUG_PRINTLN(...) {}
    #define SOCIALVIEW_TASK_DEBUG_PRINTF(...) { }
#endif


/**
 * @brief -
 * 
 * @param pvParameters
 * 
 * @return void
*/
bool youtube_request(SystemStatus *systemStatus){
        
    HTTPClient http;  // Iniciando HTTP Client
    bool result = false;
    String URL = YOUTUBE_API_URL(systemStatus->config.y_channel_id, systemStatus->config.y_api_key).c_str();            
    http.begin(URL);  // URL de requisição

    if (http.GET() == 200) { // Se o get retornou com sucesso
        String payload = http.getString();  // Salva a resposta na string
        // SOCIALVIEW_TASK_DEBUG_PRINTLN(payload);
        
        StaticJsonDocument<2048> jsonDocument;
        DeserializationError error = deserializeJson(jsonDocument, payload);

        if (error) {
            SOCIALVIEW_TASK_DEBUG_PRINT("Erro na desserialização: ");
            SOCIALVIEW_TASK_DEBUG_PRINTLN(error.c_str());
            http.end();  // Free the resources
            return result;
        }
        int totalResults = jsonDocument["pageInfo"]["totalResults"];
        if (totalResults == 0) {
            Serial.println("Total Results is 0");
            http.end();  // Free the resources
            return result;
        }

        const JsonObject& channel = jsonDocument["items"][0];
        const JsonObject& statistics = channel["statistics"];

        const char* viewCount = statistics["viewCount"];
        const char* subscriberCount = statistics["subscriberCount"];
        const char* title = channel["snippet"]["title"];
    
        SOCIALVIEW_TASK_DEBUG_PRINTLN("#########  YOUTUBE  #######");
        SOCIALVIEW_TASK_DEBUG_PRINTLN("Canal: " + String(title));
        SOCIALVIEW_TASK_DEBUG_PRINTLN("Incritos: " + String(subscriberCount));
        SOCIALVIEW_TASK_DEBUG_PRINTLN("Visualizações: " + String(viewCount));
        systemStatus->config.y_channel_name.assign(title);
        systemStatus->config.y_view_count = atoi(viewCount);
        systemStatus->config.y_subscrible_count = atoi(subscriberCount);
        result = true;
    }
    http.end();  // Free the resources
    return result;
}


/**
 * @brief -
 * 
 * @param pvParameters
 * 
 * @return void
*/
bool github_request(SystemStatus *systemStatus){
        
    HTTPClient http;  // Iniciando HTTP Client
    bool result = false;
    String URL = GITHUB_API_URL(systemStatus->config.git_user).c_str();            
    http.begin(URL);  // URL de requisição
    int code = http.GET();
    if (code != 404 && code != 403) { // Se o get retornou com sucesso
        String payload = http.getString();  // Salva a resposta na string
        // SOCIALVIEW_TASK_DEBUG_PRINTLN(payload);
        
        StaticJsonDocument<2048> jsonDocument;
        DeserializationError error = deserializeJson(jsonDocument, payload);

        if (error) {
            SOCIALVIEW_TASK_DEBUG_PRINT("Erro na desserialização: ");
            SOCIALVIEW_TASK_DEBUG_PRINTLN(error.c_str());
            http.end();  // Free the resources
            return result;
        }
          // Extrai os campos desejados
        const char* login = jsonDocument["login"];
        int followers = jsonDocument["followers"];
        int following = jsonDocument["following"];

        // Imprime os valores extraídos
        SOCIALVIEW_TASK_DEBUG_PRINTLN("#########   GITHUB  #######");
        SOCIALVIEW_TASK_DEBUG_PRINT("Login: ");
        SOCIALVIEW_TASK_DEBUG_PRINTLN(login);
        SOCIALVIEW_TASK_DEBUG_PRINT("Seguidores: ");
        SOCIALVIEW_TASK_DEBUG_PRINTLN(followers);
        SOCIALVIEW_TASK_DEBUG_PRINT("Seguindo: ");
        SOCIALVIEW_TASK_DEBUG_PRINTLN(following);

        systemStatus->config.git_name.assign(login);
        systemStatus->config.git_followers = followers;
        systemStatus->config.git_following = following;
        result = true;
    }
    http.end();  // Free the resources
    return result;
}

/**
 * @brief -
 * 
 * @param pvParameters
 * 
 * @return void
*/
bool instagram_request(SystemStatus *systemStatus){
    

    HTTPClient http;  // Iniciando HTTP Client
    bool result = false;
    String URL = INSTAGRAM_API_URL(systemStatus->config.i_user).c_str();
    http.begin(URL);  // URL de requisição
    http.setUserAgent(INSTAGRAM_USER_AGENT);
    
    if (http.GET() == 200) { // Se o get retornou com sucesso
        String payload = http.getString();  // Salva a resposta na string
        // SOCIALVIEW_TASK_DEBUG_PRINTLN(payload);
        
        
        SOCIALVIEW_TASK_DEBUG_PRINTLN("######### INSTAGRAM #######");
        StaticJsonDocument<100> doc;
        char *ptrInit = strstr(payload.c_str(), "\"edge_followed_by\"");
        if (ptrInit != NULL) {
            char *ptrEnd = strchr(ptrInit, ',');
            *ptrEnd = '\0';
            char json[100] = "";
            sprintf(json, "{%s}", ptrInit);
            // SOCIALVIEW_TASK_DEBUG_PRINTLN(json);
            // Faz o parse do JSON
            DeserializationError error = deserializeJson(doc, json);
            // Verifica se o parse foi bem-sucedido
            if (error) {
                SOCIALVIEW_TASK_DEBUG_PRINT("Falha ao fazer o parse do JSON: ");
                SOCIALVIEW_TASK_DEBUG_PRINTLN(error.c_str());
                http.end();  // Free the resources
                return result;
            }
            // Extrai o valor do campo "count" em "edge_followed_by"
            int count = doc["edge_followed_by"]["count"];

            // Imprime o valor extraído
            SOCIALVIEW_TASK_DEBUG_PRINT("Seguidores: ");
            SOCIALVIEW_TASK_DEBUG_PRINTLN(count);
            systemStatus->config.i_followers = count;
            *ptrEnd = ',';
        }

        ptrInit = strstr(payload.c_str(), "\"edge_follow\"");
        if (ptrInit != NULL) {
            char *ptrEnd = strchr(ptrInit, ',');
            char json[100] = "";
            *ptrEnd = '\0';
            sprintf(json, "{%s}", ptrInit);
            // SOCIALVIEW_TASK_DEBUG_PRINTLN(json);
            // Faz o parse do JSON
            DeserializationError error = deserializeJson(doc, json);
            // Verifica se o parse foi bem-sucedido
            if (error) {
                SOCIALVIEW_TASK_DEBUG_PRINT("Falha ao fazer o parse do JSON: ");
                SOCIALVIEW_TASK_DEBUG_PRINTLN(error.c_str());
                http.end();  // Free the resources
                return result;
            }
            // Extrai o valor do campo "count" em "edge_followed_by"
            int count = doc["edge_follow"]["count"];

            // Imprime o valor extraído
            SOCIALVIEW_TASK_DEBUG_PRINT("Seguindo: ");
            SOCIALVIEW_TASK_DEBUG_PRINTLN(count);
            systemStatus->config.i_follow = count;
            *ptrEnd = ',';
        }
        
    }
    SOCIALVIEW_TASK_DEBUG_PRINTLN("Requsição END");

    http.end();  // Free the resources

     return result;
}
    


/**
 * @brief -
 * 
 * @param pvParameters
 * 
 * @return void
*/
bool location_request(SystemStatus *systemStatus){
        
    HTTPClient http;  // Iniciando HTTP Client
    bool result = false;
    String scan = wifiScanNet();
    String key = String(systemStatus->config.y_api_key.c_str());
    String URL = GOOGLE_GEOLOCATION(key).c_str();            
    http.begin(URL);  // URL de requisição
    http.addHeader("Content-Type", "application/json");
    

    float latitude;
    float longitude;
    if (http.sendRequest("POST", scan) == 200) { // Se o get retornou com sucesso

        String payload = http.getString();  // Salva a resposta na string
        SOCIALVIEW_TASK_DEBUG_PRINTLN(payload);
        
        StaticJsonDocument<500> jsonDocument;
        DeserializationError error = deserializeJson(jsonDocument, payload);

        if (error) {
            SOCIALVIEW_TASK_DEBUG_PRINT("Erro na desserialização: ");
            SOCIALVIEW_TASK_DEBUG_PRINTLN(error.c_str());
            http.end();  // Free the resources
            return result;
        }
          // Extrai os campos desejados
        latitude = jsonDocument["location"]["lat"];
        longitude = jsonDocument["location"]["lng"];
        
        
    }
    http.end();  // Free the resources
    
    char location[50] = "";
    sprintf(location, "%f,%f", latitude, longitude);
    URL = GOOGLE_GEOCODE(String(location), key).c_str();            
    http.begin(URL);  // URL de requisição
    
    if (http.GET() == 200) { // Se o get retornou com sucesso
        String response = http.getString();
        // Serial.print("Response: ");
        // Serial.println(response);
        StaticJsonDocument<4096> jsonDocument;
        DeserializationError error = deserializeJson(jsonDocument, response);

        if (error) {
            SOCIALVIEW_TASK_DEBUG_PRINT("Erro na desserialização: ");
            SOCIALVIEW_TASK_DEBUG_PRINTLN(error.c_str());
            http.end();  // Free the resources
            return result;
        }
        const char* formattedAddress = jsonDocument["results"][0]["formatted_address"];

        // Imprimir o valor do campo "formatted_address"
        Serial.print("Formatted Address: ");
        Serial.println(formattedAddress);
        systemStatus->config.street_address.assign(formattedAddress);
        result = true;
    }
    http.end();  // Free the resources

    
    return result;
}



void socialView_task(void *pvParameters){ 
    SystemStatus *systemStatus = (SystemStatus *)pvParameters;
    for (;;) {
        if (WiFi.status() == WL_CONNECTED) {
            github_request(systemStatus);
            instagram_request(systemStatus);
            youtube_request(systemStatus);
            location_request(systemStatus);
            vTaskDelay(60000 * 1);
        } else {
            vTaskDelay(3000);
        }
    }
}