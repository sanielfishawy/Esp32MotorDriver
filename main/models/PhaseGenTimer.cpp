#include "PhaseGenTimer.h"

bool PhaseGenTimer::_isStarted = false;
bool PhaseGenTimer::_isSetup = false;
const char * PhaseGenTimer::_logTag = "PhaseGenTimer";

gptimer_handle_t PhaseGenTimer::_timer = NULL;
gptimer_config_t PhaseGenTimer::_timerConfig = {};

void PhaseGenTimer::setup() {
    if (_isSetup) return;
    _timerConfig = {
        .clk_src = GPTIMER_CLK_SRC_APB,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = APB_CLK_FREQ / PG_MIN_CLOCK_DIVIDER, 
        .intr_priority = 0,
        .flags = {
            .intr_shared = true,
        }
    };
    ESP_LOGD(_logTag, "new_timer()");
    ESP_ERROR_CHECK(gptimer_new_timer(&_timerConfig, &_timer));
    ESP_LOGD(_logTag, "enable()");
    ESP_ERROR_CHECK(gptimer_enable(_timer));
    _isSetup = true;
};

void PhaseGenTimer::startTimer() {
    if (_isStarted) return;
    ESP_LOGD(_logTag, "start()");
    ESP_ERROR_CHECK(gptimer_start(_timer));
    _isStarted = true;
};

void PhaseGenTimer::stopTimer() {
    if (!_isStarted) return;
    ESP_LOGD(_logTag, "stop()");
    ESP_ERROR_CHECK(gptimer_stop(_timer));
    _isStarted = false;
};

void PhaseGenTimer::tearDown() {
    if (!_isSetup) return;
    if (_isStarted) stopTimer();
    ESP_LOGD(_logTag, "del()");
    ESP_ERROR_CHECK(gptimer_disable(_timer));
    ESP_ERROR_CHECK(gptimer_del_timer(_timer));
    _isSetup = false;
};

uint64_t PhaseGenTimer::getTick() {
    if (!_isSetup){
        ESP_LOGE(_logTag, "Timer not setup");
        ESP_ERROR_CHECK(ESP_ERR_INVALID_STATE); 
    }
    uint64_t count;
    ESP_ERROR_CHECK(gptimer_get_raw_count(_timer, &count));
    return(count);
};

void PhaseGenTimer::setTick(uint64_t tick) {   
    ESP_ERROR_CHECK(gptimer_set_raw_count(_timer, tick));
};