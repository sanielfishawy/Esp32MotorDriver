#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_err.h"

#include "appConfig.h"

#ifndef TEST_OUTPUT_PIN_H
#define TEST_OUTPUT_PIN_H

#ifdef __cplusplus

class TestOutputPin {
    public:
        static TestOutputPin* getInstance();
        void setLevel(int level);

    protected:
        TestOutputPin();

    private:
        static TestOutputPin* _instance;
        static SemaphoreHandle_t _mutex;
        static void initializeMutex();
};


#endif // __cplusplus

#endif  // TEST_OUTPUT_PIN_H