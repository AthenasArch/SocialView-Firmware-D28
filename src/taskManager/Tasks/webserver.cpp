/**
 * Example for the ESP32 HTTP(S) Webserver
 *
 * IMPORTANT NOTE:
 * To run this script, your need to
 *  1) Enter your WiFi SSID and PSK below this comment
 *  2) Make sure to have certificate data available. You will find a
 *     shell script and instructions to do so in the library folder
 *     under extras/
 *
 * This script will install an HTTP Server on port 80 and an HTTPS server
 * on port 443 of your ESP32 with the following functionalities:
 *  - Show simple page on web server root
 *  - 404 for everything else
 *
 * The comments in this script focus on making both protocols available,
 * for setting up the server itself, see Static-Page.
 */

#include "taskManager/Tasks/webserver.hpp" /*Header do arquivo*/
#include "Peripheral/SdServerManager/sdServerManager.h"
#include <WiFi.h> // We will use wifi
#include <HTTPBodyParser.hpp> // We will use wifi
#include <HTTPMultipartBodyParser.hpp> // We will use wifi

#define WEBSERVER_TASK_DEBUG_ENABLE // descomente esta linha para habilitar o debug. 
#ifdef WEBSERVER_TASK_DEBUG_ENABLE
    #define WEBSERVER_TASK_DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
    #define WEBSERVER_TASK_DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
    #define WEBSERVER_TASK_DEBUG_PRINTF(...) { Serial.printf(__VA_ARGS__); }
#else
    #define WEBSERVER_TASK_DEBUG_PRINT(...) {}
    #define WEBSERVER_TASK_DEBUG_PRINTLN(...) {}
    #define WEBSERVER_TASK_DEBUG_PRINTF(...) { }
#endif

// The HTTPS Server comes in a separate namespace. For easier use, include it here.
using namespace httpsserver;

bool reload_config = false;

String serverIndex = "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
    "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
    "<input type='file' name='update'>"
    "<input type='submit' value='Upload'>"
    "</form>"
    "<div id='prg'>progress: 0%</div>"
    "<script>"
    "$('form').submit(function(e){"
    "e.preventDefault();"
    "var form = $('#upload_form')[0];"
    "var data = new FormData(form);"
    " $.ajax({"
    "url: '/update',"
    "type: 'POST',"
    "data: data,"
    "contentType: false,"
    "processData:false,"
    "xhr: function() {"
    "var xhr = new window.XMLHttpRequest();"
    "xhr.upload.addEventListener('progress', function(evt) {"
    "if (evt.lengthComputable) {"
    "var per = evt.loaded / evt.total;"
    "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
    "}"
    "}, false);"
    "return xhr;"
    "},"
    "success:function(d, s) {"
    "console.log('success!')"
    "},"
    "error: function (a, b, c) {"
    "}"
    "});"
    "});"
    "</script>";

// Create an SSL certificate object from the files included above
// SSLCert cert = SSLCert(
//   example_crt_DER, example_crt_DER_len,
//   example_key_DER, example_key_DER_len
// );
SSLCert * cert;

// First, we create the HTTPSServer with the certificate created above
//HTTPSServer * secureServer;// = HTTPSServer(&cert);

// Additionally, we create an HTTPServer for unencrypted traffic
HTTPServer insecureServer = HTTPServer();


static bool loadFromSDCARD(HTTPRequest * req, HTTPResponse * res);

// Declare some handler functions for the various URLs on the server
void handleRoot(HTTPRequest * req, HTTPResponse * res);
void handle404(HTTPRequest * req, HTTPResponse * res);
void handleSaveConfig(HTTPRequest * req, HTTPResponse * res);
void handleSaveItens(HTTPRequest * req, HTTPResponse * res);
void handlePayment(HTTPRequest * req, HTTPResponse * res);
void handleQueryDemo(HTTPRequest * req, HTTPResponse * res);
void handleFormUpload(HTTPRequest * req, HTTPResponse * res);

void webServer_init(SystemStatus *systemStatus) {
  
    cert = new SSLCert();

    int createCertResult = createSelfSignedCert(*cert, KEYSIZE_1024, "CN=myesp.local,O=acme,C=US");

    if (createCertResult != 0) {
        WEBSERVER_TASK_DEBUG_PRINTLN("Erro ao gerar certificado");
        return;
    }

    //  secureServer = new HTTPSServer(cert);

    // The ResourceNode links URL and HTTP method to a handler function
    ResourceNode * node404  = new ResourceNode("", "GET", &handle404);
    // For every resource available on the server, we need to create a ResourceNode
    ResourceNode * nodeRoot = new ResourceNode("/", "GET", &handleRoot);
    //Salvando a configuração
    ResourceNode * saveCfg  = new ResourceNode("/app/config", "POST", &handleSaveConfig);
    //Salvando a configuração
    ResourceNode * saveItens  = new ResourceNode("/app/itens", "POST", &handleSaveItens);
    //Salvando a configuração
    ResourceNode * update  = new ResourceNode("/update", "POST", &handleFormUpload);
    //realizando pagamento
    ResourceNode * payment  = new ResourceNode("/app/payment/*/*", "POST", &handlePayment);
    
    // We do the same for the default Node
    //  secureServer->setDefaultNode(node404);
    insecureServer.setDefaultNode(node404);

    // Add the root node to the servers. We can use the same ResourceNode on multiple
    // servers (you could also run multiple HTTPS servers)
    //  secureServer->registerNode(nodeRoot);
    insecureServer.registerNode(nodeRoot);

    // registrando o handler da configuração 
    //  secureServer->registerNode(saveCfg);
    insecureServer.registerNode(saveCfg);

    // registrando o handler dos itens 
    //  secureServer->registerNode(saveItens);
    insecureServer.registerNode(saveItens);

    // registrando o handler de upload de arquivo
    //  secureServer->registerNode(update);
    insecureServer.registerNode(update);

    // registrando o handler de pagamento 
    //  secureServer->registerNode(payment);
    insecureServer.registerNode(payment);

    //  WEBSERVER_TASK_DEBUG_PRINTLN("Starting HTTPS server...");
    //  secureServer->start();
    WEBSERVER_TASK_DEBUG_PRINTLN("Starting HTTP server...");
    insecureServer.start();
    
    if (insecureServer.isRunning()) {
        //  if (secureServer->isRunning() && insecureServer.isRunning()) {
        WEBSERVER_TASK_DEBUG_PRINTLN("Servers pronto.");
    }
}

void webserver_task(void* pvParameters) {
    
    SystemStatus *systemStatus = (SystemStatus *)pvParameters;

    webServer_init(systemStatus);
    UBaseType_t uxHighWaterMark;

    for (;;) {
        // We need to call both loop functions here
        // secureServer->loop();
        insecureServer.loop();

        if (reload_config) {
            WEBSERVER_TASK_DEBUG_PRINTLN("Recarregando configurações");
            reload_config = false;
            sdcard_loadConfig(systemStatus);
        }

        // Other code would go here...
        vTaskDelay(50);    
    }
}

// This is a more generic demo for the query parameters. It makes use of the iterator
// interface to access them, which is useful if you do not know the paramter names in
// adavance.
void handleQueryDemo(HTTPRequest * req, HTTPResponse * res) {
    // Get access to the parameters
    ResourceParameters * params = req->getParams();

    // Set a simple content type
    res->setHeader("Content-Type", "text/plain");

    // The url pattern is: /urlparam/*/*
    // This will make the content for the first parameter available on index 0,
    // and the second wildcard as index 1.
    // getPathParameter will - like getQueryParameter - write the value to the second parameter,
    // and return true, if the index is valid. Otherwise it returns false and leaves the second
    // parameter as it is.

    std::string parameter1, parameter2;
    // Print the first parameter value
    if (params->getPathParameter(0, parameter1)) {
        WEBSERVER_TASK_DEBUG_PRINT("Parameter 1: ");
        WEBSERVER_TASK_DEBUG_PRINTLN(parameter1.c_str());
    }
    
    // Print the second parameter value
    if (params->getPathParameter(1, parameter2)) {
        WEBSERVER_TASK_DEBUG_PRINT("Parameter 2: ");
        WEBSERVER_TASK_DEBUG_PRINTLN(parameter2.c_str());
    }

    WEBSERVER_TASK_DEBUG_PRINTLN("\n\nChange the parameters in the URL to see how they get parsed!");
}

void handleRoot(HTTPRequest * req, HTTPResponse * res) {
  File root = SD.open("/");
  String response = printDirectory(root, 0);
  res->setHeader("Content-Type", "text/html");
  req->discardRequestBody();
  res->setStatusCode(200);
  res->println(response);
}

void handle404(HTTPRequest * req, HTTPResponse * res) {

  if (loadFromSDCARD(req, res))
        return; 

  req->discardRequestBody();
  res->setStatusCode(404);
  res->setStatusText("Not Found");
  res->setHeader("Content-Type", "text/html");
  res->println("<!DOCTYPE html>");
  res->println("<html>");
  res->println("<head><title>Not Found</title></head>");
  res->println("<body><h1>404 Not Found</h1><p>The requested resource was not found on this server.</p></body>");
  res->println("</html>");
}

void handleSaveConfig(HTTPRequest * req, HTTPResponse * res) {

    bool success = true;
    //Fresh File
    SD.remove("/config.json");
    File root = SD.open("/config.json", FILE_WRITE);
    if (!root) {
        success = false;
    }

    if (success) {
        while(req->getContentLength()) {
            char arrayJson[500];
            memset(arrayJson, 0x00, 500);
            int len = req->readChars(arrayJson, 500);
            if (root.write((uint8_t*)arrayJson, len) != len) {
                success = false;
                break;
            }
        }
        root.close();
    }

    if (success) {
        res->setStatusCode(200);
        res->println("Configurações salvas");
        WEBSERVER_TASK_DEBUG_PRINTLN("Configurações salvas... recarregando");
        reload_config = true;
    } else {
        res->setStatusCode(500);
        res->println("Falha ao salvar configurações");
    }

    return;
}

void handleSaveItens(HTTPRequest * req, HTTPResponse * res) {
   
    bool success = true;
    SD.remove("/itens.json");
    SD.rename("/itens.json", "/itens.bak");
    File root = SD.open("/itens.json", FILE_WRITE);
    if (!root) {
        success = false;
    }

    if (success) {
        while(req->getContentLength()) {
            char arrayJson[500];
            memset(arrayJson, 0x00, 500);
            int len = req->readChars(arrayJson, 500);
            if (root.write((uint8_t*)arrayJson, len) != len) {
                success = false;
                break;
            }
        }
        root.close();
    }

    if (success) {
        res->setStatusCode(200);
        res->println("Configurações salvas");
        SD.remove("/itens.bak");
    } else {
        res->setStatusCode(500);
        res->println("Falha ao salvar itens");
        SD.rename("/itens.bak", "/itens.json");
    }
}



void handleFormUpload(HTTPRequest * req, HTTPResponse * res) {

    HTTPBodyParser *parser;
    std::string contentType = req->getHeader("Content-Type");

    size_t semicolonPos = contentType.find(";");
    if (semicolonPos != std::string::npos) {
        contentType = contentType.substr(0, semicolonPos);
    }

    // Now, we can decide based on the content type:
    if (contentType == "multipart/form-data") {
        parser = new HTTPMultipartBodyParser(req);
    } else {
        WEBSERVER_TASK_DEBUG_PRINTF("Desconecido POST Content-Type: %s\n", contentType.c_str());
        return;
    }

    res->println("<html><head><title>File Upload</title></head><body><h1>File Upload</h1>");

    bool didwrite = false;

    while(parser->nextField()) {
        std::string name = parser->getFieldName();
        std::string filename = parser->getFieldFilename();
        std::string mimeType = parser->getFieldMimeType();
        
        WEBSERVER_TASK_DEBUG_PRINTF("handleFormUpload: field name='%s', filename='%s', mimetype='%s'\n", name.c_str(), filename.c_str(), mimeType.c_str());

        std::string pathname = "/" + filename;

    
        //Fresh File
        SD.remove((char *) pathname.c_str());
        File root = SD.open(pathname.c_str(), FILE_WRITE);
    
    
        size_t fileLength = 0;
        didwrite = true;

        while (!parser->endOfField()) {
            byte buf[512];
            size_t readLength = parser->read(buf, 512);
            root.write(buf, readLength);
            fileLength += readLength;
        }
        root.close();
        res->printf("<p>Saved %d bytes to %s</p>", (int)fileLength, pathname.c_str());
    }
    if (!didwrite) {
        res->println("<p>Did not write any file</p>");
    }
    res->println("</body></html>");
    delete parser;
}

/**
 * @brief - 
 * 
 * @param
 * 
 * @return
*/
void handlePayment(HTTPRequest * req, HTTPResponse * res) {
  /*  int result = 0;
    int productId = 0;
    ResourceParameters * params = req->getParams();
    
    // Set a simple content type
    res->setHeader("Content-Type", "text/plain");

    std::string parameter1, parameter2;
    // Print the first parameter value
    if (params->getPathParameter(0, parameter1)) {
        Serial.print("Parameter 1: ");
        Serial.println(parameter1.c_str());
        
        // Print the second parameter value
        if (params->getPathParameter(1, parameter2)) {
            Serial.print("Parameter 2: ");
            Serial.println(parameter2.c_str());
            result = 1;
        }

    }

    if (result == 1) {
        if (strcmp(parameter1.c_str(), "productId") == 0) {
            productId = atoi(parameter2.c_str());
        } else if (strcmp(parameter1.c_str(), "cancel") == 0) {
            productId = atoi(parameter2.c_str());
            result = 2;
        } else {
            result = 0;
        }
    }
    
    if (result == 1) {
        start_paiment(productId);
        char* QRCODE = NULL;
        
        while (1) { 
            QRCODE = get_qrcode();
            if (QRCODE != NULL) {
                break;
            }  
            vTaskDelay(100);         
        }
        res->setStatusCode(200);
        res->println(QRCODE);
    } else if (result == 2) {
        stop_paiment(productId);
    } else {
        res->setStatusCode(400);
        res->println("");
    }
*/

}


/***************************************************************
 * Funções auxiliares
 **************************************************************/


/**
 * @brief Função cadastrada na raiz do servidor para apresentar todos arquivos raiz 
 * 
 * @param
 * 
 * @return
*/
static String printDirectory(File dir, int numTabs) {

    String response = "";
    dir.rewindDirectory();

    while (true) {

        File entry = dir.openNextFile();
        
        if (!entry) {
            break;
        }

        // Recurse for directories, otherwise print the file size
        if (entry.isDirectory()) {
            printDirectory(entry, numTabs + 1);
        } else {
            response += String("<a href='") + String(entry.name()) + String("'>") + String(entry.name()) + String("</a>") + String("</br>");
        }
        entry.close();
    }
    return String("List files:</br>") + response + String("</br></br> Upload file:") + serverIndex;
}


/**
 * @brief Função para dar vida ao webserver, carregando os arquivos necesários para o servidor rodar
 * 
 * @param
 * 
 * @return
*/
static bool loadFromSDCARD(HTTPRequest * req, HTTPResponse * res) {
    
    String path = req->getRequestString().c_str();
    path.toLowerCase();
    String dataType = "text/plain";
    
    if (path.endsWith("/"))
        path += "index.html";

    if (path.endsWith(".src"))
        path = path.substring(0, path.lastIndexOf("."));
    else if (path.endsWith(".html"))
        dataType = "text/html";
    else if (path.endsWith(".css"))
        dataType = "text/css";
    else if (path.endsWith(".jpg"))
        dataType = "image/jpeg";
    else if (path.endsWith(".txt"))
        dataType = "text/plain";
    else if (path.endsWith(".zip"))
        dataType = "application/zip";

    Serial.println(dataType);
    File dataFile = SD.open(path.c_str());

    Serial.println(path.c_str());

    if (!dataFile)
        return false;

    res->setStatusCode(200);
    res->setHeader("Connection", "keep-alive");
    res->setHeader("Content-Type", dataType.c_str());
    res->setHeader("Content-Length", httpsserver::intToString(dataFile.size()));

    // Read the file and write it to the response
    uint8_t buffer[2048];
    size_t length = 0;
    
    do {
        length = dataFile.read(buffer, 2048);
        res->write(buffer, length);
    } while (length > 0);
    
    dataFile.close();
    
  
    return true;
}