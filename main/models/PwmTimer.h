#ifndef PWM_TIMER_H
#define PWM_TIMER_H

#include "driver/ledc.h"
#include "appConfig.h"

#ifdef __cplusplus


class PwmTimer{
    public:
        static void setUpTimer();

    private:
        static bool _isSetup;
};

#endif // __cplusplus

#endif // PWM_TIMER_H