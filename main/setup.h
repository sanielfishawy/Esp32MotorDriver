#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "PwmPairs.h"
#include "models/PwmInterrupt.h"
#include "models/TestOutputPin.h"
#include "models/PwmInterruptPin.h"

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

#endif  // SETUP_H