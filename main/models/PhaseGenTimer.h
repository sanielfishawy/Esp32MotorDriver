#include "driver/gptimer.h"
#include "soc/soc.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "esp_err.h"

#include "appConfig.h"

#ifndef PHASE_GEN_TIMER_H
#define PHASE_GEN_TIMER_H


#ifdef __cplusplus

class PhaseGenTimer {

    public:
        static void setup();
        static void startTimer();
        static uint64_t getTick();
        static void setTick(uint64_t tick);

    private:
        static bool _isRunning;
        static bool _isSetup;
        static gptimer_config_t _timerConfig;
        static gptimer_handle_t _timer;

};

#endif // __cplusplus

#endif // PHASE_GEN_TIMER_H