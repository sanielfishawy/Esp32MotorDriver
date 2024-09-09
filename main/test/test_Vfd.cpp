extern "C" {
    #include "unity.h"
}

#include "FastLog.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../http/HttpServer.h"
#include "Vfd.h"
#include "GoPedal.h"

extern "C" {

    static void test_vfd() {
        HttpServer::setup();
        GoPedal::setup();
        VFD::setup();
        VFD::setFreqHz(0.0);
        VFD::setAmplitudeFract(0.0);
        VFD::start();

        while(0){
            float a = GoPedal::_getChanANormalized();
            float b = GoPedal::_getChanBNormalized();
            float t = GoPedal::getTorque();
            ESP_LOGI("test_goPedal", "a: %f, b: %f, t: %f", a, b, t);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }

    void run_test_Vfd(){
        UNITY_BEGIN();
        RUN_TEST(test_vfd);
        UNITY_END();
    }

}