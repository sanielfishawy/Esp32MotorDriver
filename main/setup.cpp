#include "setup.h"

#ifdef __cplusplus
extern "C" {
#endif

// Methods that can be called from C
extern void setup(){
    PwmInterruptPin* pip = PwmInterruptPin::getInstance();
    
    // TestOutputPin* tp = TestOutputPin::getInstance();
    // while(1){
    //     tp->setLevel(1);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    //     tp->setLevel(0);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    //     ESP_LOGI("setup", "toggle");
    // }

    PwmPairs* pwmPairs = PwmPairs::getInstance();
    PwmInterrupt::setup();

    pwmPairs->startPwm();
    PwmInterrupt::start();
}
#ifdef __cplusplus
}
#endif