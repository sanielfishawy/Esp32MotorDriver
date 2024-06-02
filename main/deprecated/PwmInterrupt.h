// Deprecated: This attempt to use a gptimer to generate an interrupt synced to ledc signals was
// unsuccessful. It was delayed by 800us and drifted. I switched to using PwmInterruptPin where
// I use the ouptut of a ledc pin to drive an interrupt on another pin. 
#ifndef PWM_INTERRUPT_H
#define PWM_INTERRUPT_H


#ifdef __cplusplus

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"
#include "driver/gptimer.h"
#include "esp_log.h"
#include "soc/soc.h"
#include "esp_attr.h"

#include "appConfig.h"
#include "PwmTimer.h"
#include "PwmPairs.h"
class PwmInterrupt{
    public:
        static void setup();
        static void start();
    
    private:
        static gptimer_handle_t _timer;
        static bool _isSetup;
        static bool _isRunning;
        static TaskHandle_t loggingTaskHandle;
        static void pwmInterruptHandler(void *params);
        static bool IRAM_ATTR _onAlarm(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data);
};

#endif  // __cplusplus

#endif  // PWM_INTERRUPT_H