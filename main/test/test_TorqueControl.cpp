extern "C" {
    #include "unity.h"
}

#include "esp_log.h"

#include "TorqueControl.h"
#include "../http/HttpServer.h"

extern "C" {

    static void test_torqueControl() {
        HttpServer::setup();
        TorqueControl::setup();
    }

    void run_test_TorqueControl(){
        UNITY_BEGIN();
        RUN_TEST(test_torqueControl);
        UNITY_END();
    }

}