#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_adc/adc_oneshot.h"


#include "PwmPairs.h"
#include "models/PwmInterrupt.h"
#include "models/TestOutputPin.h"
#include "models/PwmInterruptPin.h"
#include "models/Adc.h"
#include "models/PhaseGenTimer.h"

#ifndef SETUP_H
#define SETUP_H

#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif

// C accessible functions
void setup();

#ifdef __cplusplus
}
#endif


void _testAdc();
void _testOuputPin();
void _runPwm();
void _testPhaseGenTimer(); 

#endif  // SETUP_H