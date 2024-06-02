#pragma once

#include "esp_log.h"
#include "appConfig.h"

#ifdef __cplusplus

class ChargePump {
    public:
        ChargePump();
        float   getDuty();
        void    reset();

    private: 
        long long   _timer;
};

#endif // __cplusplus