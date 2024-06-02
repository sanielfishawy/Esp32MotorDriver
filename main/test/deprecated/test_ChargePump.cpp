extern "C" {
    #include "unity.h"
}

#include "esp_log.h"

#include "../models/ChargePump.h"

extern "C" {

    // static const char *TAG = "test_ChargePump";
    static ChargePump *cp = new ChargePump();

    static void test_chargePump() {
        TEST_ASSERT_EQUAL(CP_TIME_BETWEEN_CHARGES_IN_PWM_CYCLES, (int) ( CP_TIME_BETWEEN_CHARGES_USEC / PWM_PERIOD_USEC ));

        for (int i = 0; i < CP_TIME_BETWEEN_CHARGES_IN_PWM_CYCLES -1; i++){
            float duty = cp->getDuty();
            // ESP_LOGI(TAG, "%f", duty); 
            TEST_ASSERT_EQUAL(0, duty);
        }
        TEST_ASSERT_EQUAL(CP_CHARGE_TIME_IN_PWM_DUTY_CYCLE, CP_CHARGE_TIME_USEC / PWM_PERIOD_USEC);
        float duty = cp->getDuty();
        // ESP_LOGI(TAG, "%f", duty); 
        TEST_ASSERT_EQUAL(duty, CP_CHARGE_TIME_IN_PWM_DUTY_CYCLE);
    }

    void run_test_ChargePump(){
        UNITY_BEGIN();
        RUN_TEST(test_chargePump);
        UNITY_END();
    }

}