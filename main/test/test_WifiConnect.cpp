extern "C" {
    #include "unity.h"
}

#include "../http/WifiConnect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" {

    static void test_wifiConnect() {
        WifiConnect::setup();
        while(1){
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    void run_test_WifiConnect(){
        UNITY_BEGIN();
        RUN_TEST(test_wifiConnect);
        UNITY_END();
    }

}