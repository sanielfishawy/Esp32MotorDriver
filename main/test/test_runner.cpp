exter "C" {
    #include "unity.h"
}

// Include test files
#include "test_temp.h"

// Declare test functions from those files
extern void test_function_from_file1(void);
extern void test_function_from_file2(void);

// Implement app_main to run all tests
void app_main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_function_from_file1);
    RUN_TEST(test_function_from_file2);
    
    UNITY_END();
}