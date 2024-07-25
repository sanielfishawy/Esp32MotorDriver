#pragma once

#include "esp_log.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "appConfig.h"
#include "Quadrature.h"

#ifdef __cplusplus

class RotorSpeed{

    public:
        static void setup();
        static float getSpeedHz();
        static float getElectricalEquivalentSpeedHz();
    
    private:
        static bool _isSetup;
        static Quadrature* _quadrature;
        static bool isSpeedZero(Quadrature::Event currentEvent);

};

#endif
