extern "C" {
    #include "unity.h"
}

#include <inttypes.h>
#include "esp_log.h"
#include "../appConfig.h"
#include "../models/McPwmPair.h"


extern "C" {

    static void test_mcPwmPair() {
        McPwmPair pair(0, MCPWM_A_HIGH_GPIO_NUM, MCPWM_A_LOW_GPIO_NUM);
        pair.start();
        pair.pulse(0.25, 0.25);
        pair.setFloat();
        TEST_ASSERT_TRUE(pair.getIsFloating());
        pair.setActive();
        TEST_ASSERT_TRUE(pair.getIsActive());
        // pair.pulse(0.25, 0.25);
        // mcPwmPair->pulse(0.0, 10.0);
    }

    static void test_mcAppConfig() {
        ESP_LOGI("test_mcAppConfig", "TIMER_FREQ_HZ: %" PRIu32, MCPWM_TIMER_FREQ_HZ );
        ESP_LOGI("test_mcAppConfig", "TIMER_TICK_SEC: %.10f", MCPWM_TIMER_TICK_SEC );
        ESP_LOGI("test_mcAppConfig", "TIMER_TICK_USEC: %f", MCPWM_TIMER_TICK_USEC );
        ESP_LOGI("test_mcAppConfig", "TIMER_TICKS: %" PRIu32, MCPWM_TIMER_TICKS );
        ESP_LOGI("test_mcAppConfig", "MIN_PW_USEC: %" PRIu32, MCPWM_MIN_PW_USEC );
        ESP_LOGI("test_mcAppConfig", "MAX_PW_USEC: %" PRIu32, MCPWM_MAX_PW_USEC );
        ESP_LOGI("test_mcAppConfig", "MIN_PW_TICKS: %" PRIu32, MCPWM_MIN_PW_TICKS );
        ESP_LOGI("test_mcAppConfig", "MAX_PW_TICKS: %" PRIu32, MCPWM_MAX_PW_TICKS );
        ESP_LOGI("test_mcAppConfig", "DEAD_TIME_TICKS: %" PRIu32, MCPWM_DEAD_TIME_TICKS );
    }

    void run_test_McPwmPair(){
        UNITY_BEGIN();
        RUN_TEST(test_mcPwmPair);
        // RUN_TEST(test_mcAppConfig);
        UNITY_END();
    }

}