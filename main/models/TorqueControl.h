#pragma once

#include "esp_timer.h"
#include "appConfig.h"
#include "esp_log.h"
#include "Vfd.h"
#include "TunedParameters.h"
#include "GoPedal.h"

#ifdef __cplusplus

class TorqueControl{

    public:
        static void  setup();
        static float getTorque();
        static void  setTorque(float torque);
        static void  setUseGoPedal(bool useGoPedal);
        static bool  getUseGoPedal();

    private:
        static bool  _isSetup;
        static float _torque;
        static void  _setMotorTorque();
        static float _rotorFreq();

        static void IRAM_ATTR           _handleInterrupt(void * arg);
        static esp_timer_create_args_t  _timerArgs;
        static esp_timer_handle_t       _timer;
        static void                     _setupTimer();
        static bool  _useGoPedal;
};

#endif // __cplusplus