#pragma once

#include "esp_spiffs.h"
#include "esp_err.h"
#include "esp_log.h"

#ifdef __cplusplus

class Spiffs{
    public:
        static void setup();

    private:
        static bool _isSetup;
};

#endif // __cplusplus