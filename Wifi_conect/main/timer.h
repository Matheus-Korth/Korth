#ifndef TIMER_H
#define TIMER_H

#include "esp_err.h"

void stop_led_wifi_timer();

void start_led_wifi_timer();

esp_err_t init_timers();

#endif