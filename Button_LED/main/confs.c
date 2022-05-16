#include <stdio.h>
#include "driver/gpio.h" // Lib de controle das GPIOs
#define LED_VERMELHO GPIO_NUM_25
#define BOTAO_VERMELHO GPIO_NUM_23

#define LED_AZUL GPIO_NUM_26
#define BOTAO_AZUL GPIO_NUM_22

#define LED_AMARELO GPIO_NUM_27
#define BOTAO_AMARELO GPIO_NUM_21

void config_gpios()
{
    // Led Vermelho
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;       // Desativa interrupções
    io_conf.mode = GPIO_MODE_OUTPUT;             // Define como Saida
    io_conf.pull_down_en = 0;                    // Desativa pull down
    io_conf.pull_up_en = 0;                      // Desativa pull up
    io_conf.pin_bit_mask = 1ULL << LED_VERMELHO; // Define a GPIO
    gpio_config(&io_conf);                       // Configura

    // Led Azul
    io_conf.intr_type = GPIO_INTR_DISABLE;   // Desativa interrupções
    io_conf.mode = GPIO_MODE_OUTPUT;         // Define como Saida
    io_conf.pull_down_en = 0;                // Desativa pull down
    io_conf.pull_up_en = 0;                  // Desativa pull up
    io_conf.pin_bit_mask = 1ULL << LED_AZUL; // Define a GPIO
    gpio_config(&io_conf);                   // Configura

    // Led Amarelo
    io_conf.intr_type = GPIO_INTR_DISABLE;      // Desativa interrupções
    io_conf.mode = GPIO_MODE_OUTPUT;            // Define como Saida
    io_conf.pull_down_en = 0;                   // Desativa pull down
    io_conf.pull_up_en = 0;                     // Desativa pull up
    io_conf.pin_bit_mask = 1ULL << LED_AMARELO; // Define a GPIO
    gpio_config(&io_conf);                      // Configura

    // Botão Vermelho
    io_conf.intr_type = GPIO_INTR_DISABLE;         /* desabilita interrupção */
    io_conf.mode = GPIO_MODE_INPUT;                /* define como entrada */
    io_conf.pull_down_en = 0;                      /* desabilita pull_down */
    io_conf.pull_up_en = 1;                        /* habilita pull_up */
    io_conf.pin_bit_mask = 1ULL << BOTAO_VERMELHO; /* seleciona pino 0 */
    gpio_config(&io_conf);                         /* passa configurações na função gpio_conf */

    //gpio_set_direction(LED_VERMELHO, GPIO_MODE_OUTPUT);
}