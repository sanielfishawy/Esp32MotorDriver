extern "C" {
    #include "unity.h"
}

extern "C" {

    static void _mallocToPassedPointer(char **buf) {
        *buf = (char *) malloc(21);
    }

    static void test_malloc() {
        char *ptr = NULL;
        _mallocToPassedPointer(&ptr);
        TEST_ASSERT_NOT_NULL(ptr);
        free(ptr);
    }

    void run_test_Malloc(){
        UNITY_BEGIN();
        RUN_TEST(test_malloc);
        UNITY_END();
    }

}