#ifndef WIFI_HPP
#define WIFI_HPP

#include "Database/Structures/systemStatus.h"

String wifiScanNet();
void wifi_task(void *pvParameters);

#endif