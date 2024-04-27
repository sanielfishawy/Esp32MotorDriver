extern "C" {
    #include "unity.h"
}

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../models/Adc.h"
#include "../models/PwmInterruptPin.h"
#include "../models/PwmPairs.h"

extern "C" {

    static void test_hardware() {
        
        // int bottom = WG_ADC_ZERO_OFFSET;
        // int mid = WG_ADC_RANGE / 2 + WG_ADC_ZERO_OFFSET;
        // int top = WG_ADC_RANGE + WG_ADC_ZERO_OFFSET;

        Adc::setup();
        PwmPairs::setup();
        PwmPairs::startPwm();
        while(1){
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

    }

    void run_test_Hardware(){
        UNITY_BEGIN();
        RUN_TEST(test_hardware);
        UNITY_END();
    }

}