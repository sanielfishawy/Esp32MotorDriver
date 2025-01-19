extern "C" {
    #include "unity.h"
}

#include "../models/Contactors.h"

extern "C" {

    static void test_contactors() {
        Contactors::setup();
    }

    void run_test_Contactors(){
        UNITY_BEGIN();
        RUN_TEST(test_contactors);
        UNITY_END();
    }

}