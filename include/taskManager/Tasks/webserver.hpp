#ifndef ESP32_WEBSERVER_HPP
#define ESP32_WEBSERVER_HPP

#include <FS.h>
#include <SD.h>
#include <HTTPSServer.hpp>
#include <HTTPServer.hpp>
#include <SSLCert.hpp>
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>
#include "Database/Structures/systemStatus.h"

#define HTTPS_KEEPALIVE_CACHESIZE              1600

void webserver_task(void* pvParameters);

static String printDirectory(File dir, int numTabs);;

#endif