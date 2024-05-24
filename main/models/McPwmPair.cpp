#include "McPwmPair.h"

McPwmPair::McPwmPair( 
                      int groupId,
                      gpio_num_t highGpioNum,
                      gpio_num_t lowGpioNum
                    ): 
    _groupId(groupId),
    _highGpioNum(highGpioNum),
    _lowGpioNum(lowGpioNum),
    _timer(NULL),
    _operator(NULL),
    _leadComparator(NULL),
    _trailComparator(NULL),
    _hiGenerator(NULL),
    _loGenerator(NULL),
    _hiGeneratorConfig({
        .gen_gpio_num = _highGpioNum,
        .flags = {
            .invert_pwm = false,
            .io_loop_back = false,
            .io_od_mode = false,
            .pull_up = false,
            .pull_down = false
        }
    }),
    _loGeneratorConfig({
        .gen_gpio_num = _lowGpioNum,
        .flags = {
            .invert_pwm = false,
            .io_loop_back = false,
            .io_od_mode = false,
            .pull_up = false,
            .pull_down = false
        }
    })
{
    _setup();
};

mcpwm_timer_config_t McPwmPair::_timerConfig = {
    group_id: 0,
    clk_src: MCPWM_TIMER_CLK_SRC_PLL160M, 
    resolution_hz: MCPWM_TIMER_FREQ_HZ,
    count_mode: MCPWM_TIMER_COUNT_MODE_UP,
    period_ticks: MCPWM_TIMER_TICKS,
    intr_priority: 3,
    flags: {
        update_period_on_empty: false,
        update_period_on_sync: false
    }
};

mcpwm_operator_config_t McPwmPair::_operatorConfig = {
    group_id: 0,
    intr_priority: 3,
    flags: {
        update_gen_action_on_tez: false,
        update_gen_action_on_tep: true,
        update_gen_action_on_sync: false,
        update_dead_time_on_tez: false,
        update_dead_time_on_tep: true,
        update_dead_time_on_sync: false
    }
};


mcpwm_comparator_config_t McPwmPair::_comparatorConfig = {
    intr_priority: 3,
    flags: {
        update_cmp_on_tez: false,
        update_cmp_on_tep: true,
        update_cmp_on_sync: false,
    }
};


void McPwmPair::_setup(){
    ESP_ERROR_CHECK(mcpwm_new_timer(&_timerConfig, &_timer));
    ESP_ERROR_CHECK(mcpwm_new_operator(&_operatorConfig, &_operator));
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(_operator, _timer));
    ESP_ERROR_CHECK(mcpwm_new_comparator(_operator, &_comparatorConfig, &_leadComparator));
    ESP_ERROR_CHECK(mcpwm_new_comparator(_operator, &_comparatorConfig, &_trailComparator));
    ESP_ERROR_CHECK(mcpwm_new_generator(_operator, &_hiGeneratorConfig, &_hiGenerator));
    ESP_ERROR_CHECK(mcpwm_new_generator(_operator, &_loGeneratorConfig, &_loGenerator));

    _setPeriodStartAction();
    _setLeadingEdgeAction();
    _setTrailingEdgeAction();

    ESP_ERROR_CHECK(mcpwm_timer_enable(_timer));
}

void McPwmPair::start(){
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(_timer, MCPWM_TIMER_START_NO_STOP));
}

void McPwmPair::pulse(float lead, float pulseWidth){
    uint32_t leadCompareValue = (uint32_t) (lead * MCPWM_TIMER_TICKS);
    uint32_t pw = (uint32_t) (pulseWidth * MCPWM_TIMER_TICKS);
    if (pw > MCPWM_MAX_PW_TICKS) pw = MCPWM_MAX_PW_TICKS;
    if (pw < MCPWM_MIN_PW_TICKS) pw = MCPWM_MIN_PW_TICKS;

    if (leadCompareValue + pw >= MCPWM_TIMER_TICKS){
        ESP_LOGE(MCPWM_TAG, "Pulse width %ld pulse leading ticks %ld greater than period ticks %ld", leadCompareValue, pw, MCPWM_TIMER_TICKS);
        ESP_ERROR_CHECK(ESP_ERR_INVALID_SIZE);
    }
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(_leadComparator, leadCompareValue));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(_trailComparator, leadCompareValue + pw));
}

void McPwmPair::_setPeriodStartAction(){
    // Leading low at period start
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(
                    _hiGenerator,
                    MCPWM_GEN_TIMER_EVENT_ACTION(
                        MCPWM_TIMER_DIRECTION_UP,
                        MCPWM_TIMER_EVENT_EMPTY,
                        MCPWM_GEN_ACTION_LOW
                    )
    ));

    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(
                    _loGenerator,
                    MCPWM_GEN_TIMER_EVENT_ACTION(
                        MCPWM_TIMER_DIRECTION_UP,
                        MCPWM_TIMER_EVENT_EMPTY,
                        MCPWM_GEN_ACTION_HIGH
                    )
    ));
}

void McPwmPair::_setLeadingEdgeAction(){
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(
                    _hiGenerator,
                    MCPWM_GEN_COMPARE_EVENT_ACTION(
                        MCPWM_TIMER_DIRECTION_UP,
                        _leadComparator,
                        MCPWM_GEN_ACTION_HIGH
                    )
    ));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(
                    _loGenerator,
                    MCPWM_GEN_COMPARE_EVENT_ACTION(
                        MCPWM_TIMER_DIRECTION_UP,
                        _leadComparator,
                        MCPWM_GEN_ACTION_LOW
                    )
    ));
}

void McPwmPair::_setTrailingEdgeAction(){
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(
                    _hiGenerator,
                    MCPWM_GEN_COMPARE_EVENT_ACTION(
                        MCPWM_TIMER_DIRECTION_UP,
                        _trailComparator,
                        MCPWM_GEN_ACTION_LOW
                    )
    ));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(
                    _loGenerator,
                    MCPWM_GEN_COMPARE_EVENT_ACTION(
                        MCPWM_TIMER_DIRECTION_UP,
                        _trailComparator,
                        MCPWM_GEN_ACTION_HIGH
                    )
    ));
}   