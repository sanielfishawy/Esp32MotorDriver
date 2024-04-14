#ifndef PWM_TIMER_H
#define PWM_TIMER_H

#include "driver/ledc.h"

#ifdef __cplusplus

#define PWM_DUTY_RESOLUTION LEDC_TIMER_10_BIT
#define PWM_TIMER_MODE LEDC_LOW_SPEED_MODE
#define PWM_TIMER_NUM LEDC_TIMER_0
#define PWM_FREQ 40000

class PwmTimer{
    public:
        static void setUpTimer();

    private:
        static bool _isSetup;
};

#endif // __cplusplus

#endif // PWM_TIMER_H