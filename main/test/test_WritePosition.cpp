extern "C" {
    #include "unity.h"
}

#include "esp_log.h"
#include "esp_err.h"
#include "../telemetry/WritePosition.h"

extern "C" {

    static void test_writePosition() {
        size_t wp;
        wp = WritePosition::loadWritePos("test");
        TEST_ASSERT_EQUAL_INT32(-1, wp);
        WritePosition::saveWritePos("test", 0);
        wp = WritePosition::loadWritePos("test");
        TEST_ASSERT_EQUAL_INT32(0, wp);
    }

    void run_test_WritePosition(){
        UNITY_BEGIN();
        RUN_TEST(test_writePosition);
        UNITY_END();
    }

}