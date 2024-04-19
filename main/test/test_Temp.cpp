extern "C" {
    #include "unity.h"
}

#include "Temp.h"

extern "C" {
    
    void test_sum() {
        TEST_ASSERT_EQUAL_FLOAT(5.0, Temp::sum(2.0, 3.0));
        TEST_ASSERT_TRUE(1);
    }

    void run_test_Temp(){
        UNITY_BEGIN();
        RUN_TEST(test_sum);
        UNITY_END();
    }

}