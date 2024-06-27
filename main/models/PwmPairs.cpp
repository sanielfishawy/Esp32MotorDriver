#include "PwmPairs.h"

bool  PwmPairs::_isSetup = false;
bool  PwmPairs::_isStarted = false;
float PwmPairs::_amplitudeFract = 0.5;

McPwmPair PwmPairs::_pairA(
    0,
    MCPWM_A_HIGH_GPIO_NUM,
    MCPWM_A_LOW_GPIO_NUM
);

McPwmPair PwmPairs::_pairB(
    1,
    MCPWM_B_HIGH_GPIO_NUM,
    MCPWM_B_LOW_GPIO_NUM
);

McPwmPair PwmPairs::_pairC(
    2,
    MCPWM_C_HIGH_GPIO_NUM,
    MCPWM_C_LOW_GPIO_NUM
);

void PwmPairs::setup(){
    if (_isSetup) return; 
    PhaseGen::setup();
    PhaseGen::start();
    _syncPairs();
    _setupInterrupt();
    _isSetup = true;
}

void PwmPairs::_syncPairs(){
    //          +->timer1
    // timer0---+
    //          +->timer2
    ESP_LOGI(PWM_PAIRS_TAG, "Syncing timers");
    mcpwm_sync_handle_t syncSource = NULL;
    mcpwm_timer_sync_src_config_t syncConfig = {
        .timer_event = MCPWM_TIMER_EVENT_EMPTY, 
        .flags = {
            .propagate_input_sync = 0,
        },
    };
    ESP_ERROR_CHECK(mcpwm_new_timer_sync_src(_pairA.getTimer(), &syncConfig, &syncSource));
    mcpwm_timer_sync_phase_config_t syncPhaseConfig = {
        .sync_src = syncSource,
        .count_value = 0,
        .direction = MCPWM_TIMER_DIRECTION_UP,
    };
    ESP_ERROR_CHECK(mcpwm_timer_set_phase_on_sync(_pairB.getTimer(), &syncPhaseConfig));
    ESP_ERROR_CHECK(mcpwm_timer_set_phase_on_sync(_pairC.getTimer(), &syncPhaseConfig));
}

void PwmPairs::_setupInterrupt(){
    McPwmInterrupt::setup(_pairA.getTimer(), handleInterrupt);
}

void PwmPairs::startPwm(){
    if (_isStarted) return;

    _pairA.start();
    _pairB.start();
    _pairC.start();
    _isStarted = true;
}

void PwmPairs::pairAPulse(float lead, float pulseWidth){
    _pairA.pulse(lead, pulseWidth);
}

void PwmPairs::pairBPulse(float lead, float pulseWidth){
    _pairA.pulse(lead, pulseWidth);
}

void PwmPairs::pairCPulse(float lead, float pulseWidth){
    _pairA.pulse(lead, pulseWidth);
}

void PwmPairs::setActive(){
    _pairA.setActive();
    _pairB.setActive();
    _pairC.setActive();
}

void PwmPairs::setFloat(){
    _pairA.setFloat();
    _pairB.setFloat();
    _pairC.setFloat();
}

bool PwmPairs::getIsActive(){
    return _pairA.getIsActive() || _pairB.getIsActive() || _pairC.getIsActive();
}

bool PwmPairs::getIsFloating(){
    return _pairA.getIsFloating() && _pairB.getIsFloating() && _pairC.getIsFloating();
}

void PwmPairs::handleInterrupt(){
    // static float duty = 0;
    // FastLog::set(duty++);
    // return;

    float phase = PhaseGen::getPhaseRad();
    SvPwm svPwm(phase, _amplitudeFract);
    SvPwmPulses pulses;
    svPwm.pulses(&pulses);
    _pairA.pulse(pulses.aPulse.edge, pulses.aPulse.pw);
    _pairB.pulse(pulses.bPulse.edge, pulses.bPulse.pw);
    _pairC.pulse(pulses.cPulse.edge, pulses.cPulse.pw);

    // _pairA.pulse(0.375, 0.25);
    // _pairB.pulse(0.375, 0.25);
    // _pairC.pulse(0.375, 0.25);
}

void PwmPairs::setAmplitudeFract(float amplitudeFract){
    _amplitudeFract = amplitudeFract;
}

float PwmPairs::getAmplitudeFract(){
    return _amplitudeFract;
}