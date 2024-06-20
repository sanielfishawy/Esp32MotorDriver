extern "C" {
    #include "unity.h"
}

#include "FastLog.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../http/HttpServer.h"
#include "../http/HttpServer.h"

extern "C" {

    static void test_vfd() {
        HttpServer::setup();
        VFD::setup();
        VFD::setFreqHz(5.0);
        VFD::setAmplitudeFract(0.1);
        VFD::start();
    }

    void run_test_Vfd(){
        UNITY_BEGIN();
        RUN_TEST(test_vfd);
        UNITY_END();
    }

}