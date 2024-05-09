extern "C" {
    #include "unity.h"
}

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../http/HttpServer.h"
#include "../models/Vfd.h"

extern "C" {

    static void test_httpServer() {
        HttpServer::setup();
        VFD::setup();
        VFD::start();
    }

    void run_test_HttpServer(){
        UNITY_BEGIN();
        RUN_TEST(test_httpServer);
        UNITY_END();
    }

}