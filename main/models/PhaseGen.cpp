#include "PhaseGen.h"

bool PhaseGen::_isSetup = false;
bool PhaseGen::_isStarted = false;
const char *PhaseGen::_logTag = "PhaseGen";
int PhaseGen::_periodTicks = PG_MAX_PERIOD_TICKS;
int PhaseGen::_previousPeriodTicks = PG_MAX_PERIOD_TICKS;

void PhaseGen::setup(){
    if (_isSetup) return;
    ESP_LOGD(_logTag, "setup()");
    PhaseGenTimer::setup();
    _isSetup = true;
}

void PhaseGen::tearDown(){
    if (!_isSetup) return;
    if (_isStarted) stop();
    ESP_LOGD(_logTag, "tearDown()");
    PhaseGenTimer::tearDown();
    _isSetup = false;
};

void PhaseGen::start(){
    if (!_isSetup) return;
    if (_isStarted) return; 
    ESP_LOGD(_logTag, "start()");
    PhaseGenTimer::startTimer();
    _isStarted = true;
}

void PhaseGen::stop(){
    if (!_isStarted) return;
    ESP_LOGD(_logTag, "stop()");
    PhaseGenTimer::stopTimer();
    _isStarted = false;
}

void PhaseGen::setPeriodSec(float periodSec){
    int ticks = (int) (periodSec / PG_TIMER_PERIOD_SEC);
    _setPeriodTicks(ticks);
}

float PhaseGen::getPeriodSec(){
    return (float) getPeriodTicks() * PG_TIMER_PERIOD_SEC;
}

void PhaseGen::setFreqHz(float freq){
    float periodSec = 1.0 / freq;
    setPeriodSec(periodSec);
}

float PhaseGen::getFreqHz(){
    return 1.0 / getPeriodSec();
}

float PhaseGen::getPhaseRad(){
    return 2 * M_PI * _phaseFraction();
}   

int PhaseGen::getPeriodTicks(){
    return _periodTicks;
}

void PhaseGen::_setPeriodTicks(int ticks){
    if (ticks < PG_MIN_PERIOD_TICKS){
        ticks = PG_MIN_PERIOD_TICKS;
    } else if (ticks > PG_MAX_PERIOD_TICKS){
        ticks = PG_MAX_PERIOD_TICKS;
    }
    _periodTicks = ticks;
    _checkAndAdjustForPeriodChange();
}

uint64_t PhaseGen::getTimerTick(){
    return _getTimerTick();
}

void PhaseGen::_setTimerTick(uint64_t tick){
    PhaseGenTimer::setTick(tick);
}

uint64_t PhaseGen::_getTimerTick(){
    return PhaseGenTimer::getTick();
}

void PhaseGen::_checkAndAdjustForPeriodChange(){
    if (_periodTicks != _previousPeriodTicks){
        _setTimerTick(_timerTicksForPeriodChange());
    }
    _previousPeriodTicks = _periodTicks;
}

int PhaseGen::_phaseTickNum(){
    return (int) (_getTimerTick() % _periodTicks);
}

float PhaseGen::_phaseFraction(){
    return (float) _phaseTickNum() / _periodTicks;
}


int PhaseGen::_previousPhaseTickNum(){
    return (int) (_getTimerTick() % _previousPeriodTicks);
}

float PhaseGen::_previousPhaseFraction(){
    return  static_cast<float>( _previousPhaseTickNum() ) / _previousPeriodTicks;
}

uint64_t PhaseGen::_timerTicksForPeriodChange(){
    return (uint64_t) (_previousPhaseFraction() * _periodTicks);
}