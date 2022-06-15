#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "modulo_wifi.h"
#include "modulo_nvs.h"
#include "led.h"
#include "timer.h"

static const char *TAG = "[MAIN] --> ";

void app_main(void)
{
    ESP_LOGI(TAG, "Configurando LED");
    gpio_driver_led_init();

    ESP_LOGI(TAG, "Iniciando TIMERS");
    init_timers();

    ESP_LOGI(TAG, "Iniciando NVS FLASH");
    nvs_init();

    ESP_LOGI(TAG, "Conectando-se a rede Wi-fi");
    wifi_init();
}