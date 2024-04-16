#ifndef PHASEGEN_H
#define PHASEGEN_H

#define PG_MIN_PERIOD 125
#define PG_MAX_PERIOD 250000

unsigned long long PG_timestamp;
int PG_period;
int PG_previousPeriod;

void PG_init();
void PG_setPeriod(int period);
void PG_handlePwmTick();
int PG_phaseTickNum();
float PG_phaseFraction();
float PG_phaseRadians();
int PG_previousTickNum();
float PG_previousPhaseFraction();
long long PG_timestampForPeriodChange();
#endif