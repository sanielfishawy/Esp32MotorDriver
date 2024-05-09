#pragma once

#include "esp_log.h"

#ifdef __cplusplus

class FastLog {

    public:
        static void set(float duty);
        static void log();

    private:
        static float _duty;

};
#endif // __cplusplus