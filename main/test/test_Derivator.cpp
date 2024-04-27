extern "C" {
    #include "unity.h"
}

#include "../models/Derivator.h"
#include "esp_log.h"

extern "C" {
    
    static void test_calculate() {
        float r = 0;
        Derivator * der = new Derivator();
        
        r = der->calculate(2);
        TEST_ASSERT_FLOAT_WITHIN(.01, 2.0 / PWM_PERIOD_SEC, r);

        r = der->calculate(1);
        TEST_ASSERT_FLOAT_WITHIN(.01, -1.0 / PWM_PERIOD_SEC, r);

        r = der->calculate(1);
        TEST_ASSERT_FLOAT_WITHIN(.01, 0.0 / PWM_PERIOD_SEC, r);

        r = der->calculate(0);
        r = der->calculate(0);

        r = der->calculate(-2);
        r = der->calculate(-1);

        TEST_ASSERT_FLOAT_WITHIN(.01, 1.0 / PWM_PERIOD_SEC, r);
    }

    void run_test_Derivator(){
        UNITY_BEGIN();
        RUN_TEST(test_calculate);
        UNITY_END();
    }

}