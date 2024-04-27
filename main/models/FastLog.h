#pragma once

#include "esp_log.h"

#ifdef __cplusplus

class FastLog {

    public:
        static void set(int setPoint, int actPoint, float duty);
        static void log();

    private:
        static int _setPoint;
        static int _actPoint;
        static float _duty;

};
#endif // __cplusplus