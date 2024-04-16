#include "PhaseGenTimer.h"

bool PhaseGenTimer::_isRunning = false;
bool PhaseGenTimer::_isSetup = false;

gptimer_handle_t PhaseGenTimer::_timer = NULL;
gptimer_config_t PhaseGenTimer::_timerConfig = {};

void PhaseGenTimer::setup() {
    _timerConfig = {
        .clk_src = GPTIMER_CLK_SRC_APB,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = APB_CLK_FREQ / PG_MIN_CLOCK_DIVIDER, 
        .intr_priority = 0,
        .flags = {
            .intr_shared = true,
        }
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&_timerConfig, &_timer));
};

void PhaseGenTimer::startTimer() {
    ESP_ERROR_CHECK(gptimer_enable(_timer));
    ESP_ERROR_CHECK(gptimer_start(_timer));
};

uint64_t PhaseGenTimer::getTick() {
    uint64_t count;
    ESP_ERROR_CHECK(gptimer_get_raw_count(_timer, &count));
    return(count);
};

void PhaseGenTimer::setTick(uint64_t tick) {   
    ESP_ERROR_CHECK(gptimer_set_raw_count(_timer, tick));
};