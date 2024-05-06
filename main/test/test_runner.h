#pragma once
#include "esp_log.h"

extern "C" {
    void run_test_Temp();
    void run_test_PhaseGenTimer();
    void run_test_PhaseGen();
    void run_test_WaveformGen();
    void run_test_Integrator();
    void run_test_Derivator();
    void run_test_Pid();
    void run_test_Calibrate();
    void run_test_Hardware();
    void run_test_Vfd();
    void run_test_WifiConnect();
    void run_test_HttpServer();
    void run_test_VfdOpenLoop();
}