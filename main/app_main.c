#include "setup.h"


extern void app_main(void)
{
    setup();
    // ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
    // Update duty to apply the new value
    // ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
}
