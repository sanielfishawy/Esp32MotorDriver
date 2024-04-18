extern "C" {
    #include "unity.h"
}

#include "test_runner.h"

extern "C"{
    void app_main(void) {
        esp_log_level_set("*", ESP_LOG_INFO);
        run_test_Temp();
        run_test_PhaseGenTimer();
        run_test_PhaseGen();
    }
}