extern "C" {
    // #include "unity.h"
}

#include "test_runner.h"

extern "C"{
    void app_main(void) {
        esp_log_level_set("*", ESP_LOG_INFO);
        // run_test_PhaseGenTimer();
        // run_test_PhaseGen();
        // run_test_Integrator(); 
        // run_test_Derivator();
        // run_test_Pid();
        // run_test_Calibrate();
        // run_test_WifiConnect();
        // run_test_WritePosition();
        // run_test_TelemetryToFile();
        // run_test_Spiffs();
        // run_test_McPwmPair();
        // run_test_PwmPairs();
        // run_test_SvPwm();
        // run_test_HttpServer();
        // run_test_Dynamic();
        // run_test_Malloc();
        // run_test_Torque();
        // run_test_RotorSpeed();
        // run_test_Vfd();
        // run_test_TunedParameters();
        // run_test_GoPedal();
        // run_test_TorqueControl();
        // run_test_Contactors();
        // run_test_Adc();
        run_test_DcVoltage();
    }
}