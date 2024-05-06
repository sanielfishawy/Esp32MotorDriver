extern "C" {
    #include "unity.h"
}

#include "FastLog.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../models/Vfd.h"
#include "../models/OpenLoopClosedLoop.h"

extern "C" {

    static void test_vfdOpenLoop() {
        VFD::setup();
        // OpenLoopClosedLoop::dangerousSetOpenLoop();
        VFD::start();
        while(1){
            FastLog::log();
            vTaskDelay(1523 / portTICK_PERIOD_MS);
        }
    }

    void run_test_VfdOpenLoop(){
        UNITY_BEGIN();
        RUN_TEST(test_vfdOpenLoop);
        UNITY_END();
    }

}