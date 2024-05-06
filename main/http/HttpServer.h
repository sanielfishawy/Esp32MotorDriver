#pragma once

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_http_server.h"
#include "cJSON.h"

#include "WifiConnect.h"
#include "NvsFlash.h"

#ifdef __cplusplus

class HttpServer {
    public:
        static void setup();
    
    private:
        static bool _isSetup;
        static esp_err_t _get_hello_handler(httpd_req_t *req);
        static httpd_handle_t _start_webserver(void);
        static httpd_uri_t _hello;


};
#endif // __cplusplus