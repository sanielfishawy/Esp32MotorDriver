extern "C" {
    #include "unity.h"
}

#include "esp_log.h"

#include "RotorSpeed.h"

extern "C" {

    static void test_rotorSpeed() {
        float expected = 1000000.0 / (48.0 * 0.1);
        TEST_ASSERT_DOUBLE_WITHIN(0.1, RS_MAX_TIME_BETWEEN_TICKS_USEC, expected);
    }

    void run_test_RotorSpeed(){
        UNITY_BEGIN();
        RUN_TEST(test_rotorSpeed);
        UNITY_END();
    }

}