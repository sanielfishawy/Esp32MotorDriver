extern "C" {
    #include "unity.h"
}

#include "FastLog.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../models/Vfd.h"

extern "C" {

    static void test_vfd() {
        VFD::setup();
        VFD::setFreqHz(60.0);
        VFD::setAmplitudeFract(1);
        VFD::start();
        while(1){
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            FastLog::log();
        }
    }

    void run_test_Vfd(){
        UNITY_BEGIN();
        RUN_TEST(test_vfd);
        UNITY_END();
    }

}