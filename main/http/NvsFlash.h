#pragma once    

#include "esp_err.h"
#include "nvs_flash.h"

#ifdef __cplusplus

class NvsFlash {
    public:
        static void setup();
    
    private:
        static bool _isSetup;
};

#endif // __cplusplus