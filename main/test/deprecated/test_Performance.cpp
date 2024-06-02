extern "C" {
    #include "unity.h"
}

#include "math.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../models/Vfd.h"
#include "../models/WaveformGen.h"
#include "../models/PwmPairs.h"


extern "C" {

    static void test_performance() {
        VFD::setup();
        WaveformGen::start();

        for (int i=0; i<10; i++){
            WaveformGen::getDuty(M_3PI_4);
        }

        for (int i=0; i<10; i++){
            uint64_t start = esp_timer_get_time();
            uint64_t end = esp_timer_get_time();
            ESP_LOGI("test_performance", "readRawAdcA(): time = %lld", end - start);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        
    }

    void run_test_Performance(){
        UNITY_BEGIN();
        RUN_TEST(test_performance);
        UNITY_END();
    }

}