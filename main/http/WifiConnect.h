#pragma once 

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"

#include "appConfig.h"


#ifdef __cplusplus

class WifiConnect {

public:
    static void setup();


private:
    const static char *_logTag;
    static bool _isSetup;
    static void _eventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
    static void _scan();
    
};


#endif // __cplusplus



