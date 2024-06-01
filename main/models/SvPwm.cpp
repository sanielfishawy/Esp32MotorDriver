#include "SvPwm.h"

SvPwm::SvPwm(float theta, float amp):
    _theta(theta),
    _sectorTheta(fmod(theta, (M_PI/3))),
    _sector(_getSector(_theta)),
    _amp(amp),

    _alpha(amp * SQRT3 * cos(_sectorTheta) / 2.0),
    _beta(amp * SQRT3 * sin(_sectorTheta) / 2.0),
    _zeroDegT((_alpha - (_beta / SQRT3))),
    _sixtyDegT((2.0 * _beta / SQRT3)),

    _t0(0),
    _t1(0),
    _t2(0),
    _t3(0),
    _t4(0),
    _t5(0),
    _t6(0)
{
    _calcTs();
}

int SvPwm::_getSector(float theta){
    if(theta < PI_DIV_3){
        return 1;
    } else if(theta < PI_2_DIV_3){
        return 2;
    } else if(theta < PI_3_DIV_3){
        return 3;
    } else if(theta < PI_4_DIV_3){
        return 4;
    } else if(theta < PI_5_DIV_3){
        return 5;
    } else {
        return 6;
    }
}

void SvPwm::_calcTs(){
    if (_sector == 1){
        _t4 = _zeroDegT;
        _t6 = _sixtyDegT;
    }
    else if (_sector == 2){
        _t2 = _sixtyDegT;
        _t6 = _zeroDegT;
    }
    else if (_sector == 3){
        _t2 = _zeroDegT;
        _t3 = _sixtyDegT;
    }
    else if (_sector == 4){
        _t3 = _zeroDegT;
        _t1 = _sixtyDegT;
    }
    else if (_sector == 5){
        _t1 = _zeroDegT;
        _t5 = _sixtyDegT;
    }
    else {
        _t5 = _zeroDegT;
        _t4 = _sixtyDegT;
    }
    _t0 = (1 - _t1 - _t2 - _t3 - _t4 - _t5 - _t6) / 2;
}

void SvPwm::aPulse(SvPwmPulse *pulse){
    if(_sector == 1){
        pulse->edge = _t0 / 2;
        pulse->pw   = _t0 + _t4 + _t6;
    }
    else if(_sector == 2){
        pulse->edge = (_t0 + _t2) / 2;
        pulse->pw   = _t0 + _t6;
    }
    else if(_sector == 3){
        pulse->edge = (_t0 + _t2 + _t3) / 2;
        pulse->pw   = _t0;
    }
    else if(_sector == 4){
        pulse->edge = (_t0 + _t1 + _t3) / 2;
        pulse->pw   = _t0;
    }
    else if(_sector == 5){
        pulse->edge = (_t0 + _t1) / 2;
        pulse->pw   = _t0 + _t5;
    }
    else {
        pulse->edge = _t0 / 2;
        pulse->pw   = _t4 + _t5 + _t0;
    }
}

void SvPwm::bPulse(SvPwmPulse *pulse){
    if(_sector == 1){
        pulse->edge = (_t0 + _t4) / 2;
        pulse->pw   = _t0 + _t6;
    }
    else if(_sector == 2){
        pulse->edge = _t0 / 2;
        pulse->pw   = _t0 + _t2 + _t6;
    }
    else if(_sector == 3){
        pulse->edge = _t0 / 2;
        pulse->pw   =  _t0 + _t2 + _t3;
    }
    else if(_sector == 4){
        pulse->edge = (_t0 + _t1) / 2;
        pulse->pw   = _t0 + _t3;
    }
    else if(_sector == 5){
        pulse->edge = (_t0 + _t1 + _t5) / 2;
        pulse->pw   = _t0;
    }
    else {
        pulse->edge = (_t0 + _t4 + _t5) / 2;
        pulse->pw   = _t0;
    }
}

void SvPwm::cPulse(SvPwmPulse *pulse){
    if(_sector == 1){
        pulse->edge = (_t0 + _t4 + _t6) / 2;
        pulse->pw   = _t0;
    }
    else if(_sector == 2){
        pulse->edge = (_t0 + _t2 + _t6) / 2;
        pulse->pw   = _t0;
    }
    else if(_sector == 3){
        pulse->edge = (_t0 + _t2) / 2;
        pulse->pw   = _t0 + _t3;
    }
    else if(_sector == 4){
        pulse->edge = _t0 / 2;
        pulse->pw   = _t0 + _t1 + _t3;
    }
    else if(_sector == 5){
        pulse->edge = _t0 / 2;
        pulse->pw   = _t0 + _t1 + _t5;
    }
    else {
        pulse->edge = (_t0 + _t4) / 2;
        pulse->pw   = _t0 + _t5; 
    }
}

// Reduce compares for performance
void SvPwm::pulses(SvPwmPulses *pulses){
    if(_sector == 1){
        pulses->aPulse.edge = _t0 / 2;
        pulses->aPulse.pw   = _t0 + _t4 + _t6;
        pulses->bPulse.edge = (_t0 + _t4) / 2;
        pulses->bPulse.pw   = _t0 + _t6;
        pulses->cPulse.edge = (_t0 + _t4 + _t6) / 2;
        pulses->cPulse.pw   = _t0;
    }
    else if(_sector == 2){
        pulses->aPulse.edge = (_t0 + _t2) / 2;
        pulses->aPulse.pw   = _t0 + _t6;
        pulses->bPulse.edge = _t0 / 2;
        pulses->bPulse.pw   = _t0 + _t2 + _t6;
        pulses->cPulse.edge = (_t0 + _t2 + _t6) / 2;
        pulses->cPulse.pw   = _t0;
    }
    else if(_sector == 3){
        pulses->aPulse.edge = (_t0 + _t2 + _t3) / 2;
        pulses->aPulse.pw   = _t0;
        pulses->bPulse.edge = _t0 / 2;
        pulses->bPulse.pw   =  _t0 + _t2 + _t3;
        pulses->cPulse.edge = (_t0 + _t2) / 2;
        pulses->cPulse.pw   = _t0 + _t3;
    }
    else if(_sector == 4){
        pulses->aPulse.edge = (_t0 + _t1 + _t3) / 2;
        pulses->aPulse.pw   = _t0;
        pulses->bPulse.edge = (_t0 + _t1) / 2;
        pulses->bPulse.pw   = _t0 + _t3;
        pulses->cPulse.edge = _t0 / 2;
        pulses->cPulse.pw   = _t0 + _t1 + _t3;
    }
    else if(_sector == 5){
        pulses->aPulse.edge = (_t0 + _t1) / 2;
        pulses->aPulse.pw   = _t0 + _t5;
        pulses->bPulse.edge = (_t0 + _t1 + _t5) / 2;
        pulses->bPulse.pw   = _t0;
        pulses->cPulse.edge = _t0 / 2;
        pulses->cPulse.pw   = _t0 + _t1 + _t5;
    }
    else {
        pulses->aPulse.edge = _t0 / 2;
        pulses->aPulse.pw   = _t4 + _t5 + _t0;
        pulses->bPulse.edge = (_t0 + _t4 + _t5) / 2;
        pulses->bPulse.pw   = _t0;
        pulses->cPulse.edge = (_t0 + _t4) / 2;
        pulses->cPulse.pw   = _t0 + _t5; 
    }
}

void SvPwm::show(){
    ESP_LOGI(SV_PWM_TAG, "theta: %f", _theta);
    ESP_LOGI(SV_PWM_TAG, "sector: %d", _sector);
    ESP_LOGI(SV_PWM_TAG, "sectorTheta: %f", _sectorTheta);
    ESP_LOGI(SV_PWM_TAG, "amp: %f", _amp);
    ESP_LOGI(SV_PWM_TAG, "alpha: %f", _alpha);
    ESP_LOGI(SV_PWM_TAG, "beta: %f", _beta);
    ESP_LOGI(SV_PWM_TAG, "zeroDegT: %f", _zeroDegT);
    ESP_LOGI(SV_PWM_TAG, "sixtyDegT: %f", _sixtyDegT);
    ESP_LOGI(SV_PWM_TAG, "t0: %f", _t0);
    ESP_LOGI(SV_PWM_TAG, "t1: %f", _t1);
    ESP_LOGI(SV_PWM_TAG, "t2: %f", _t2);
    ESP_LOGI(SV_PWM_TAG, "t3: %f", _t3);
    ESP_LOGI(SV_PWM_TAG, "t4: %f", _t4);
    ESP_LOGI(SV_PWM_TAG, "t5: %f", _t5);
    ESP_LOGI(SV_PWM_TAG, "t6: %f", _t6);

    SvPwmPulse _aPulse;
    SvPwmPulse _bPulse;
    SvPwmPulse _cPulse;

    aPulse(&_aPulse);
    bPulse(&_bPulse);
    cPulse(&_cPulse);

    _showPulse("A", &_aPulse);
    _showPulse("B", &_bPulse);
    _showPulse("C", &_cPulse);

    SvPwmPulses _pulses;
    pulses(&_pulses);
    _showPulses(&_pulses);
}

void SvPwm::_showPulse(const char *name, SvPwmPulse *pulse){
    ESP_LOGI(SV_PWM_TAG, "%s edge: %f", name, pulse->edge);
    ESP_LOGI(SV_PWM_TAG, "%s   pw: %f", name, pulse->pw);
}

void SvPwm::_showPulses(SvPwmPulses *pulses){
    _showPulse("A pulses", &pulses->aPulse);
    _showPulse("B pulses", &pulses->bPulse);
    _showPulse("C pulses", &pulses->cPulse);
}

void SvPwm::getAll(SvPwmAll *all){
    all->theta = _theta;
    all->sector = _sector;
    all->sectorTheta = _sectorTheta;
    all->amp = _amp;
    all->alpha = _alpha;
    all->beta = _beta;
    all->zeroDegT = _zeroDegT;
    all->sixtyDegT = _sixtyDegT;
    all->t0 = _t0;
    all->t1 = _t1;
    all->t2 = _t2;
    all->t3 = _t3;
    all->t4 = _t4;
    all->t5 = _t5;
    all->t6 = _t6;
    aPulse(&all->aPulse);
    bPulse(&all->bPulse);
    cPulse(&all->cPulse);
    pulses(&all->pulses);
}