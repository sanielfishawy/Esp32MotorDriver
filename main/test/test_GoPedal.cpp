extern "C" {
    #include "unity.h"
}

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "GoPedal.h"

extern "C" {

    static void test_goPedal() {
        GoPedal::setup();
        while(1){
            GoPedal::show();
            // float a = GoPedal::_getChanANormalized();
            // float b = GoPedal::_getChanBNormalized();
            // float t = GoPedal::getTorque();
            // ESP_LOGI("test_goPedal", "a: %f, b: %f, t: %f", a, b, t);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

    }

    void run_test_GoPedal(){
        UNITY_BEGIN();
        RUN_TEST(test_goPedal);
        UNITY_END();
    }

}