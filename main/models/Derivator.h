#pragma once 

#include "appConfig.h"

#ifdef __cplusplus

class Derivator{

    public:
        Derivator(); 
        float calculate(int error);
        void reset();
        
    private:
        int _priorError;

};

#endif // __cplusplus