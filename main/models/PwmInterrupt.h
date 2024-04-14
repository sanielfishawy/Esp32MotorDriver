#ifndef PWM_INTERRUPT_H
#define PWM_INTERRUPT_H


#ifdef __cplusplus

#include <stdio.h>
#include "PwmTimer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gptimer.h"
#include "esp_log.h"

class PwmInterrupt{
    public:
        static void start();
    
    private:
        static bool _isRunning;
        static IRAM_ATTR void _onTimer();
}

#endif  // __cplusplus

#endif  // PWM_INTERRUPT_H