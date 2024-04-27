extern "C" {
    // #include "unity.h"
}

#include "test_runner.h"

extern "C"{
    void app_main(void) {
        esp_log_level_set("*", ESP_LOG_INFO);
        // run_test_Temp();
        // run_test_PhaseGenTimer();
        // run_test_PhaseGen();
        // run_test_WaveformGen();
        // run_test_Integrator(); 
        // run_test_Derivator();
        // run_test_Pid();
        // run_test_Calibrate();
        // run_test_Hardware();
        // run_test_Vfd();
        run_test_WifiConnect();
    }
}