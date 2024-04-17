#include "PhaseGen.h"

bool PhaseGen::_isSetup = false;
bool PhaseGen::_isStarted = false;
int PhaseGen::_periodTicks = PG_MAX_PERIOD_TICKS;
int PhaseGen::_previousPeriodTicks = PG_MAX_PERIOD_TICKS;

void PhaseGen::setup(){
    if (_isSetup) return;
    PhaseGenTimer::setup();
    _isSetup = true;
}

void PhaseGen::start(){
    if (!_isSetup) return;
    if (_isStarted) return; 
    PhaseGenTimer::startTimer();
    _isStarted = true;
}

void PhaseGen::setPeriodSec(float periodSec){
    int ticks = (int) (periodSec / PG_TIMER_PERIOD_SEC);
    _setPeriodTicks(ticks);
}

void PhaseGen::setFreqHz(float freq){
    float periodSec = 1.0 / freq;
    setPeriodSec(periodSec);
}

float PhaseGen::phaseRadians(){
    return 2 * M_PI * _phaseFraction();
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