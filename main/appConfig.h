#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"

// PwmInterruptPin
#define PWM_INTR_PIN_OUT_GPIO_NUM   GPIO_NUM_47
#define PWM_INTR_PIN_IN_GPIO_NUM    GPIO_NUM_48
#define PWM_INTR_PIN_CHANNEL_NUM    LEDC_CHANNEL_6

// PwmPairs
#define PWM_A_HIGH_GPIO_NUM     GPIO_NUM_4
#define PWM_A_LOW_GPIO_NUM      GPIO_NUM_5
#define PWM_B_HIGH_GPIO_NUM     GPIO_NUM_6
#define PWM_B_LOW_GPIO_NUM      GPIO_NUM_7
#define PWM_C_HIGH_GPIO_NUM     GPIO_NUM_9
#define PWM_C_LOW_GPIO_NUM      GPIO_NUM_10

#define PWM_A_HIGH_CHANNEL_NUM   LEDC_CHANNEL_0
#define PWM_A_LOW_CHANNEL_NUM    LEDC_CHANNEL_1
#define PWM_B_HIGH_CHANNEL_NUM   LEDC_CHANNEL_2
#define PWM_B_LOW_CHANNEL_NUM    LEDC_CHANNEL_3
#define PWM_C_HIGH_CHANNEL_NUM   LEDC_CHANNEL_4
#define PWM_C_LOW_CHANNEL_NUM    LEDC_CHANNEL_5

// PwmTimer
#define PWM_DUTY_RESOLUTION     LEDC_TIMER_10_BIT
#define PWM_TIMER_MODE          LEDC_LOW_SPEED_MODE
#define PWM_TIMER_NUM           LEDC_TIMER_0
#define PWM_FREQ                (15000)

// PwmInterrupt
#define PWM_INTR_MIN_CLOCK_DIVIDER  (2)

// TestOutputPin
#define TEST_OUTPUT_GPIO_NUM GPIO_NUM_11

// Adc
#define ADC_BIT_WIDTH           ADC_BITWIDTH_DEFAULT
#define ADC_MAX_VOLTAGE_BINARY  (3430)
#define ADC_MAX_VOLTAGE_FLOAT   (2.75)
#define ADC_CHANNEL_O_GPIO_NUM  GPIO_NUM_1
#define ADC_CHANNEL_1_GPIO_NUM  GPIO_NUM_2
#define ADC_CHANNEL_2_GPIO_NUM  GPIO_NUM_3

// PhaseGen
#define PG_MIN_CLOCK_DIVIDER    (2)
#define PG_TIMER_FREQ_HZ        ( (int) APB_CLK_FREQ / PG_MIN_CLOCK_DIVIDER )
#define PG_TIMER_PERIOD_SEC     ( (float)(1.0 / PG_TIMER_FREQ_HZ) )

#define PG_MAX_FREQ_HZ          ( (float) 100.0 )
#define PG_MIN_PERIOD_SEC       ( (float) 1 / PG_MAX_FREQ_HZ )
#define PG_MIN_PERIOD_TICKS     ( (int) (PG_MIN_PERIOD_SEC / PG_TIMER_PERIOD_SEC) )

#define PG_MIN_FREQ_HZ          ( (float) 0.5 )
#define PG_MAX_PERIOD_SEC       ( (float) 1.0 / PG_MIN_FREQ_HZ )
#define PG_MAX_PERIOD_TICKS     ( (int) (PG_MAX_PERIOD_SEC / PG_TIMER_PERIOD_SEC) )