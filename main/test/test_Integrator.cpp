extern "C" {
    #include "unity.h"
}

#include "../models/Integrator.h"
#include "esp_log.h"

extern "C" {
    
    static void test_calculate() {
        float r = 0;
        Integrator * integ = new Integrator();
        
        for (int i = 0; i < PID_DEFAULT_INTEGRATOR_SIZE - 1; i++){
            r = integ->calculate(i + 1);
            TEST_ASSERT_FLOAT_WITHIN(.01, 0, r);
        }

        r = integ->calculate(10);
        TEST_ASSERT_FLOAT_WITHIN(.01, (1.0 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10) / 10.0, r);

        integ->reset();
        
        for (int i = 0; i < PID_DEFAULT_INTEGRATOR_SIZE - 1; i++){
            r = integ->calculate(i + 1);
            TEST_ASSERT_FLOAT_WITHIN(.01, 0, r);
        }
    }

    void run_test_Integrator(){
        UNITY_BEGIN();
        RUN_TEST(test_calculate);
        UNITY_END();
    }

}