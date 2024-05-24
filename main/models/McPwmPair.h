#pragma once

#include "driver/mcpwm_prelude.h"
#include "soc/clk_tree_defs.h"
#include "esp_clk_tree.h"
#include "esp_err.h"
#include "esp_log.h"

#include "appConfig.h"

#ifdef __cplusplus

class McPwmPair{

    public:
        McPwmPair(  int group_id, 
                    gpio_num_t highGpioNum, 
                    gpio_num_t lowGpioNum
        );
        void start();
        void pulse(float lead, float pulseWidth);
    
    private:
        int _groupId;
        gpio_num_t _highGpioNum;
        gpio_num_t _lowGpioNum;
        mcpwm_timer_handle_t _timer;
        mcpwm_oper_handle_t _operator;
        mcpwm_cmpr_handle_t _leadComparator;
        mcpwm_cmpr_handle_t _trailComparator;
        mcpwm_gen_handle_t _hiGenerator;
        mcpwm_gen_handle_t _loGenerator;
        mcpwm_generator_config_t _hiGeneratorConfig;
        mcpwm_generator_config_t _loGeneratorConfig;

        void _setup();
        void _setPeriodStartAction();
        void _setLeadingEdgeAction();
        void _setTrailingEdgeAction();
        
        static mcpwm_timer_config_t _timerConfig;
        static mcpwm_operator_config_t _operatorConfig;
        static mcpwm_comparator_config_t _comparatorConfig;
};

#endif // __cplusplus