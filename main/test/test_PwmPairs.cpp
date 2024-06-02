extern "C" {
    #include "unity.h"
}

#include "FastLog.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "PwmPairs.h"
#include "PhaseGen.h"

extern "C" {

    static void test_pwmPairs() {
        PhaseGen::setup();
        PhaseGen::setFreqHz(60);
        PhaseGen::start();  
        PwmPairs::setup();
        PwmPairs::startPwm();
        // while(1){
        //     vTaskDelay(1000 / portTICK_PERIOD_MS);
        //     FastLog::log();
        // }
    }

    void run_test_PwmPairs(){
        UNITY_BEGIN();
        RUN_TEST(test_pwmPairs);
        UNITY_END();
    }

}