#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "modulo_wifi.h"
#include "esp_log.h"
#include "timer.h"

#define LED_WIFI GPIO_NUM_14

#define GPIO_OUTPUT_PIN_SEL (1ULL << LED_WIFI)

static const char *TAG = "[LED] --> ";

static bool wifi_level = false;

/// @brief Permite escolher o level do LED_WIFI
/// @param level 0 ou 1
void set_level_led_wifi(uint32_t level)
{
    gpio_set_level(LED_WIFI, level);
}

/// Alterna o level do LED_WIFI
void alternar_led()
{   
    wifi_level = !wifi_level;
    gpio_set_level(LED_WIFI, wifi_level);
}

/// Configura a GPIO do led que indica a coneção com a rede Wi-Fi
esp_err_t gpio_driver_led_init()
{
    esp_err_t ret;

    gpio_config_t io_config;
    //desabilita interrupção
    io_config.intr_type = GPIO_PIN_INTR_DISABLE;
    //configura como output mode
    io_config.mode = GPIO_MODE_OUTPUT;
    //bit maks dos pinos a serem configurados
    io_config.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //desabilita pull-down mode
    io_config.pull_down_en = 0;
    //desabilita pull-up mode
    io_config.pull_up_en = 0;
    //configura o gpio
    ret = gpio_config(&io_config);

    set_level_led_wifi(0);
    
    return ret;
}