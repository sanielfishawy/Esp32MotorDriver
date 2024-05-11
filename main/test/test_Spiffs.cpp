extern "C" {
    #include "unity.h"
}

#include "../telemetry/Spiffs.h"


extern "C" {

    static void test_spiffs() {
        Spiffs::setup();
    }

    void run_test_Spiffs(){
        UNITY_BEGIN();
        RUN_TEST(test_spiffs);
        UNITY_END();
    }

}