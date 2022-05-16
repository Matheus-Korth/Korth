#include <stdio.h>
#include "confs.h" 
#include "driver/gpio.h" // Lib de controle das GPIOs

#define LED_VERMELHO GPIO_NUM_25
#define BOTAO_VERMELHO GPIO_NUM_23

#define LED_AZUL GPIO_NUM_26
#define BOTAO_AZUL GPIO_NUM_22

#define LED_AMARELO GPIO_NUM_27
#define BOTAO_AMARELO GPIO_NUM_21

void app_main(void)
{
    config_gpios(); // chama a configuração das GPIOs
    while (1)
    {
        int level_vermelho = !gpio_get_level(BOTAO_VERMELHO);
        gpio_set_level(LED_VERMELHO, level_vermelho);

        int level_azul = !gpio_get_level(BOTAO_AZUL);
        gpio_set_level(LED_AZUL, level_azul);

        int level_amarelo = !gpio_get_level(BOTAO_AMARELO);
        gpio_set_level(LED_AMARELO, level_amarelo);
    }
}