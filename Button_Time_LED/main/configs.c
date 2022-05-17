#include <stdio.h>
#include "driver/gpio.h" // Lib de controle das GPIOs
// Bibliotécas FreeRTOS
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
// Definições das Botões e suas GPIOs
#define BOTAO_UM 23
#define BOTAO_DOIS 22
#define BOTAO_TRES 21
// GPIO onde o LED está conectado
#define LED 27

void pisca_500()
{
    gpio_set_level(LED, 1);
    vTaskDelay(500 / portTICK_RATE_MS);
    gpio_set_level(LED, 0);
    vTaskDelay(500 / portTICK_RATE_MS);
}

void pisca_1000()
{
    gpio_set_level(LED, 1);
    vTaskDelay(1000 / portTICK_RATE_MS);
    gpio_set_level(LED, 0);
    vTaskDelay(1000 / portTICK_RATE_MS);
}

void pisca_1500()
{
    gpio_set_level(LED, 1);
    vTaskDelay(1500 / portTICK_RATE_MS);
    gpio_set_level(LED, 0);
    vTaskDelay(1500 / portTICK_RATE_MS);
}

void config_gpios()
{
    // LED
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LED);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    // Botão Um
    io_conf.intr_type = GPIO_INTR_DISABLE;     /* desabilita interrupção */
    io_conf.mode = GPIO_MODE_INPUT;            /* define como entrada */
    io_conf.pull_down_en = 0;                  /* desabilita pull_down */
    io_conf.pull_up_en = 1;                    /* habilita pull_up */
    io_conf.pin_bit_mask = (1ULL << BOTAO_UM); /* seleciona pino 0 */
    gpio_config(&io_conf);                     /* passa configurações na função gpio_conf */

    // Botão Dois
    io_conf.intr_type = GPIO_INTR_DISABLE;       /* desabilita interrupção */
    io_conf.mode = GPIO_MODE_INPUT;              /* define como entrada */
    io_conf.pull_down_en = 0;                    /* desabilita pull_down */
    io_conf.pull_up_en = 1;                      /* habilita pull_up */
    io_conf.pin_bit_mask = (1ULL << BOTAO_DOIS); /* seleciona pino 0 */
    gpio_config(&io_conf);                       /* passa configurações na função gpio_conf */

    // Botão Tres
    io_conf.intr_type = GPIO_INTR_DISABLE;       /* desabilita interrupção */
    io_conf.mode = GPIO_MODE_INPUT;              /* define como entrada */
    io_conf.pull_down_en = 0;                    /* desabilita pull_down */
    io_conf.pull_up_en = 1;                      /* habilita pull_up */
    io_conf.pin_bit_mask = (1ULL << BOTAO_TRES); /* seleciona pino 0 */
    gpio_config(&io_conf);                       /* passa configurações na função gpio_conf */
}