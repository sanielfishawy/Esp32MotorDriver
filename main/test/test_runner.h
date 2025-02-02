#pragma once
#include "esp_log.h"

extern "C" {
    void run_test_PhaseGenTimer();
    void run_test_PhaseGen();
    void run_test_Integrator();
    void run_test_Derivator();
    void run_test_Pid();
    void run_test_Calibrate();
    void run_test_Vfd();
    void run_test_WifiConnect();
    void run_test_HttpServer();
    void run_test_ChargePump();
    void run_test_Performance();
    void run_test_WritePosition();
    void run_test_TelemetryToFile();
    void run_test_Spiffs();
    void run_test_McPwmPair();
    void run_test_SvPwm();
    void run_test_PwmPairs();
    void run_test_Dynamic();
    void run_test_Malloc();
    void run_test_Torque();
    void run_test_RotorSpeed();
    void run_test_TunedParameters();
    void run_test_TorqueControl();
    void run_test_GoPedal();
    void run_test_Contactors();
    void run_test_Adc();
    void run_test_DcVoltage();
}