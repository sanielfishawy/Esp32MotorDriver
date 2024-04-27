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
        VFD::start();
        while(1){
            FastLog::log();
            vTaskDelay(1523 / portTICK_PERIOD_MS);

        }
    }

    void run_test_Vfd(){
        UNITY_BEGIN();
        RUN_TEST(test_vfd);
        UNITY_END();
    }

}