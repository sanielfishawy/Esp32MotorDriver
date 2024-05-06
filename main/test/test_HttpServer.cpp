extern "C" {
    #include "unity.h"
}

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../http/HttpServer.h"

extern "C" {

    static void test_httpServer() {
        HttpServer::setup();
        while(1){
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    void run_test_HttpServer(){
        UNITY_BEGIN();
        RUN_TEST(test_httpServer);
        UNITY_END();
    }

}