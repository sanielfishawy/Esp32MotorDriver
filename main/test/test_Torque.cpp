extern "C" {
    #include "unity.h"
}

#include "StaticTorqueMeasurement.h"

extern "C" {

    static void test_torque() {
        StaticTorqueMeasurement::setup();
    }

    void run_test_Torque(){
        UNITY_BEGIN();
        RUN_TEST(test_torque);
        UNITY_END();
    }

}