#ifndef LED_H
#define LED_H

#include "driver/gpio.h"

esp_err_t gpio_driver_led_init();

void alternar_led();

void set_level_led_wifi(uint32_t level);

#endif