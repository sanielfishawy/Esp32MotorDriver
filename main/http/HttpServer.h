#pragma once

#include <vector>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_netif.h"
#include "esp_http_server.h"
#include "mdns.h"
#include "cJSON.h"

#include "appConfig.h"
#include "WifiConnect.h"
#include "NvsFlash.h"
#include "Routes.h"

#ifdef __cplusplus

class HttpServer {
    public:
        static void setup();
    
    private:
        static bool _isSetup;
        static httpd_handle_t _start_webserver(void);
        static void _setupMdns();


};
#endif // __cplusplus