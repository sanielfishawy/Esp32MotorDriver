extern "C" {
    #include "unity.h"
}

#include "Torque.h"

extern "C" {

    static void test_torque() {
        Torque::setup();
    }

    void run_test_Torque(){
        UNITY_BEGIN();
        RUN_TEST(test_torque);
        UNITY_END();
    }

}