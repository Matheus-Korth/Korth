#include <stdio.h>

// Bibliotécas FreeRTOS
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Bibliotéca para uso das GPIOs
#include "driver/gpio.h"

// Definições das Botões e suas GPIOs
#define BOTAO_UM 23
#define BOTAO_DOIS 22
#define BOTAO_TRES 21

void configura_gpios()
{
    // Botão Um
    gpio_config_t io_conf;
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