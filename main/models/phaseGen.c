#include <stdio.h>
#include <math.h>
#include "phaseGen.h"

unsigned long long PG_timestamp = 0LL;
int PG_period = PG_MAX_PERIOD;
int PG_previousPeriod = PG_MAX_PERIOD;

void PG_init(){
    PG_timestamp = 0LL;
    PG_period = PG_MAX_PERIOD;
    PG_previousPeriod = PG_MAX_PERIOD;
}

void PG_setPeriod(int period){
    if (period < PG_MIN_PERIOD){
        period = PG_MIN_PERIOD;
    } else if (period > PG_MAX_PERIOD){
        period = PG_MAX_PERIOD;
    }
    PG_period = period;
}

void PG_handlePwmTick(){
    if (PG_period != PG_previousPeriod){
        PG_timestamp = PG_timestampForPeriodChange();
    } else {
        PG_timestamp++;
    }
    PG_previousPeriod = PG_period;
}

int PG_phaseTickNum(){
    return (int) (PG_timestamp % PG_period);
}

float PG_phaseFraction(){
    return (float) PG_phaseTickNum() / PG_period;
}

float PG_phaseRadians(){
    return 2 * M_PI * PG_phaseFraction();
}   

int PG_previousTickNum(){
    return (int) (PG_timestamp % PG_previousPeriod);
}

float PG_previousPhaseFraction(){
    return (float) PG_previousTickNum() / PG_previousPeriod;
}

long long PG_timestampForPeriodChange(){
    return (long long) (PG_previousPhaseFraction() * PG_period);
}