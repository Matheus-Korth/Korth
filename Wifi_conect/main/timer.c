#include "timer.h"
#include "led.h"
#include "esp_timer.h"

#define MSEC_TO_USEC(msec)  (msec*1000) // Define oque é milesegundo.

#define LED_WIFI_TIMER_TIMEOUT  MSEC_TO_USEC(400) //Timer que faz o LED conexão piscar.

static void led_wifi_timer_cb(void* args);

static esp_timer_handle_t led_wifi_timer_handler;

static esp_timer_create_args_t led_wifi_create_args = 
{
    .callback = &led_wifi_timer_cb, // Chama sempre que o tempo "LED_WIFI_TIMER_TIMEOUT" é atingido.
    .name = "LED_WIFI_TIMER",
    .arg = NULL,
};

/// Função que altera o estado do LED.
static void led_wifi_timer_cb(void* args)
{
    alternar_led();
}

/// Para o timer que faz o LED piscar.
void stop_led_wifi_timer()
{
    esp_timer_stop(led_wifi_timer_handler);
}

/// Inicia o timer que faz o LED piscar.
void start_led_wifi_timer()
{
    printf("chego aki");
    esp_timer_start_periodic(led_wifi_timer_handler, LED_WIFI_TIMER_TIMEOUT);
}

/// Cria o timer que faz o LED piscar.
esp_err_t init_timers()
{
    return esp_timer_create(&led_wifi_create_args, &led_wifi_timer_handler);
}