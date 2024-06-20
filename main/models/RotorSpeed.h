#pragma once

#include "esp_log.h"
#include "esp_log.h"

#include "Quadrature.h"
#include "appConfig.h"

#ifdef __cplusplus

class RotorSpeed{

    public:
        static void setup();
        static float getSpeedHz();
        static float getElectricalEquivalentSpeedHz();
    
    private:
        static bool _isSetup;
        static Quadrature* _quadrature;

};

#endif
