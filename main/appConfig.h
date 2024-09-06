#pragma once

#include "math.h"

#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"

// General
#define MOTOR_POLES                 ( (int) 4 )

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
#define PWM_A_ADC_CHANNEL_NUM    ADC_CHANNEL_0
#define PWM_B_HIGH_CHANNEL_NUM   LEDC_CHANNEL_2
#define PWM_B_LOW_CHANNEL_NUM    LEDC_CHANNEL_3
#define PWM_B_ADC_CHANNEL_NUM    ADC_CHANNEL_1
#define PWM_C_HIGH_CHANNEL_NUM   LEDC_CHANNEL_4
#define PWM_C_LOW_CHANNEL_NUM    LEDC_CHANNEL_5
#define PWM_C_ADC_CHANNEL_NUM    ADC_CHANNEL_2

#define PWM_A_PHASE_OFFSET_RAD      ( (float) 0.0 )
#define PWM_B_FWD_PHASE_OFFSET_RAD  ( (float) 2.0 * M_PI / 3.0 )
#define PWM_C_FWD_PHASE_OFFSET_RAD  ( (float) 4.0 * M_PI / 3.0 )
#define PWM_B_REV_PHASE_OFFSET_RAD  ( (float) 4.0 * M_PI / 3.0 )
#define PWM_C_REV_PHASE_OFFSET_RAD  ( (float) 2.0 * M_PI / 3.0 )

// PwmTimer
#define PWM_DUTY_RESOLUTION     LEDC_TIMER_10_BIT
#define PWM_TIMER_MODE          LEDC_LOW_SPEED_MODE
#define PWM_TIMER_NUM           LEDC_TIMER_0
#define PWM_FREQ                10000
#define PWM_PERIOD_SEC          ( 1.0 / PWM_FREQ )
#define PWM_PERIOD_USEC         ( 1000000.0 * PWM_PERIOD_SEC )

// PwmInterrupt
#define PWM_INTR_MIN_CLOCK_DIVIDER  (2)

// TestOutputPin
#define TEST_OUTPUT_GPIO_NUM GPIO_NUM_11

// Adc
#define ADC_BIT_WIDTH           ADC_BITWIDTH_DEFAULT
#define ADC_MAX_VOLTAGE_BINARY  (4000)
#define ADC_MAX_VOLTAGE_FLOAT   (2.75)
#define ADC_MIN_VOLTAGE_BINARY  (250)
#define ADC_MIN_VOLTAGE_FLOAT   (0.2)
#define ADC_RANGE_BINARY        (ADC_MAX_VOLTAGE_BINARY - ADC_MIN_VOLTAGE_BINARY)
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

// WaveformGen
#define WG_SINE_WAVE            ( (int) 0 )
#define WG_SQUARE_WAVE          ( (int) 1 )
#define WG_AMP_FRACT_MAX         ( (float) 1.0 )
#define WG_AMP_FRACT_MIN         ( (float) 0.0 )
#define WG_FREQ_MAX             ( (float) 60.0 )
#define WG_FREQ_MIN             ( (float) 0.1 )

// PID
#define PID_DEFAULT_KP                  ( (float) 0.0002 )
#define PID_DEFAULT_KI                  ( (float) 0.0 )
#define PID_DEFAULT_KD                  ( (float) 0.0 )
#define PID_DEFAULT_INTEGRATOR_SIZE     ( (int) 10 )

// ChargePump
#define CP_TAG                                  "ChargePump"
#define CP_REQUIRES_CHARGE_PUMP                 ( (bool) true )
#define CP_TIME_BETWEEN_CHARGES_USEC            500.0
#define CP_CHARGE_TIME_USEC                     20.0
#define CP_TIME_BETWEEN_CHARGES_IN_PWM_CYCLES   ( (int) ( CP_TIME_BETWEEN_CHARGES_USEC / PWM_PERIOD_USEC ) )
#define CP_CHARGE_TIME_IN_PWM_DUTY_CYCLE        ( CP_CHARGE_TIME_USEC / PWM_PERIOD_USEC ) 

// Wifi
// #define WIFI_SSID   "pollionidesign"
// #define WIFI_PWD    "par00502"
// #define WIFI_SSID   "scoutandjagger"
// #define WIFI_PWD    "ridgebacks"
#define WIFI_SSID   "Elfishawy"
#define WIFI_PWD    "7035251244"

// HttpServer
#define HS_MDNS_HOSTNAME        "motor"
#define HS_MDNS_INSTANCE_NAME   "Esp32 Motor Controller Http Server"
#define HS_MAX_URI_LENGTH       128
#define HS_MAX_PARAM_LENGTH     64
#define HS_MAX_URI_HANDLERS     32

// TelemetryToFile
#define TEL_TAG                 "TelemetryToFile"
#define TEL_NUM_POINTS_STORED   2000

// McPwm
#define MCPWM_TAG                   "McPwm"
#define MCPWM_TIMER_FREQ_HZ         ( (uint32_t) (160 * 1000 * 1000 ) )
#define MCPWM_TIMER_TICK_SEC        ((float) ( 1.0 / MCPWM_TIMER_FREQ_HZ ))
#define MCPWM_TIMER_TICK_USEC       ((float) ( 1000.0 * 1000.0 * MCPWM_TIMER_TICK_SEC ))
#define MCPWM_TIMER_TICKS           ( (u_int32_t) ( MCPWM_TIMER_FREQ_HZ / PWM_FREQ ) )
#define MCPWM_MIN_PW_USEC           ( (u_int32_t) 2 )  
#define MCPWM_MAX_PW_USEC           ( (u_int32_t) ( PWM_PERIOD_USEC - MCPWM_MIN_PW_USEC ) )
#define MCPWM_MIN_PW_TICKS          ( ( uint32_t ) ( MCPWM_MIN_PW_USEC / MCPWM_TIMER_TICK_USEC ) )
#define MCPWM_MAX_PW_TICKS          ( ( uint32_t ) ( MCPWM_MAX_PW_USEC / MCPWM_TIMER_TICK_USEC ) )
#define MCPWM_A_HIGH_GPIO_NUM       PWM_A_HIGH_GPIO_NUM
#define MCPWM_A_LOW_GPIO_NUM        PWM_A_LOW_GPIO_NUM
#define MCPWM_B_HIGH_GPIO_NUM       PWM_B_HIGH_GPIO_NUM
#define MCPWM_B_LOW_GPIO_NUM        PWM_B_LOW_GPIO_NUM
#define MCPWM_C_HIGH_GPIO_NUM       PWM_C_HIGH_GPIO_NUM
#define MCPWM_C_LOW_GPIO_NUM        PWM_C_LOW_GPIO_NUM
#define MCPWM_DEAD_TIME_USEC        ( (float) 2.0 )
#define MCPWM_DEAD_TIME_TICKS       ( (uint32_t) ( MCPWM_DEAD_TIME_USEC / MCPWM_TIMER_TICK_USEC ) )

// RotorSpeed
#define RS_TAG                  "RotorSpeed"
#define RS_QUAD_A_GPIO_NUM      GPIO_NUM_11
#define RS_QUAD_B_GPIO_NUM      GPIO_NUM_12
#define RS_QAUD_TICKS_PER_REV   (float) 48
#define RS_MIN_SPEED_HZ         (float) 0.1
#define RS_MAX_TIME_BETWEEN_TICKS_USEC ( (float) ( 1000000.0 / ( RS_MIN_SPEED_HZ * RS_QAUD_TICKS_PER_REV ) ) )

// Dynamic
#define DYN_TAG                     "Dynamic"
#define DYN_VFD_UPDATE_PERIOD_MS    20
#define DYN_STOPPED_ROTOR_FREQ_HZ   3.0
#define DYN_START_FREQ_HZ           3.0
#define DYN_START_AMP_FRACT         0.6
#define DYN_ACCEL_TO_MIN_SLIP_FRACT 0.2
#define DYN_ACCEL_TO_MIN_AMP_FRACT  0.6
#define DYN_NOT_ABLE_TO_ACCEL_THRESHOLD_SEC 15.0

// Static Torque Measurement
#define STM_TAG              "StaticTorqueMeasurement"
#define STM_ADC_UNIT         ADC_UNIT_1
#define STM_ADC_CHANNEL      ADC_CHANNEL_0
#define STM_ADC_GPIO_PIN     GPIO_NUM_1

// Torque Control
#define TC_TAG                      "TorqueControl"
#define TC_VFD_UPDATE_PERIOD_MS     20

// VFD
#define VFD_TAG                 "VFD"
#define VFD_DEFAULT_MAX_FREQ_HZ         ( (float) 60.0 )

// Go Pedal
#define GP_TAG                  "GoPedal"
#define GP_ADC_UNIT             ADC_UNIT_1
#define GP_ADC_GPIO_NUM_A       GPIO_NUM_2
#define GP_ADC_GPIO_NUM_B       GPIO_NUM_3
#define GP_ADC_CHANNEL_A        ADC_CHANNEL_1
#define GP_ADC_CHANNEL_B        ADC_CHANNEL_2
#define GP_CHAN_A_NORM_FACTOR   ( (float) 1.0 )
#define GP_CHAN_B_NORM_FACTOR   ( (float) 1.0 )
#define GP_CHAN_AGREE_THRESHOLD ( (float) 0.01 )
