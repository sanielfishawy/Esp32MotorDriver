extern "C" {
    #include "unity.h"
}

#include "../models/Pid.h"
#include "esp_log.h"

extern "C" {
    
    static void test_calculate() {
        float r = 0;
        PID * pid = new PID();
        pid->setKp(.001);
        pid->setKd(0);
        pid->setKi(0);
        
        r = pid->calculate(500, 300);
        TEST_ASSERT_FLOAT_WITHIN(.0001, .2, r);

        pid->setKp(0);
        pid->setKd(.001 * 1.0 * PWM_PERIOD_SEC);
        pid->setKi(0);
        r = pid->calculate(500, 400);
        TEST_ASSERT_FLOAT_WITHIN(.00001, -.1, r);

        pid->setKp(0);
        pid->setKd(0);
        pid->setKi(.001);
        for (int i = 0; i <= PID_DEFAULT_INTEGRATOR_SIZE; i++){
            r = pid->calculate(500, 400);
        };
        TEST_ASSERT_FLOAT_WITHIN(.00001, .1, r);
    }

    void run_test_Pid(){
        UNITY_BEGIN();
        RUN_TEST(test_calculate);
        UNITY_END();
    }

}