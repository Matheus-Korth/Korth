#include <stdio.h>
// Configurações das GPIOs
#include "configs.h"
// Bibliotéca para utilizar GPIOs
#include "driver/gpio.h"
// Bibliotécas FreeRTOS
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
// Definições das Botões e suas GPIOs
#define BOTAO_UM 23
#define BOTAO_DOIS 22
#define BOTAO_TRES 21
// GPIO onde o LED está conectado
#define LED 27

void app_main(void)
{
    config_gpios(); // Configuração das GPIOs
    while (true) // Estrutira de Repetição
    {
        if (gpio_get_level(BOTAO_UM) == false) // BOTAO_UM precionado
        {
            pisca_500(); // Pica LED a cada 500ms
        }
        else if (gpio_get_level(BOTAO_DOIS) == false) // BOTAO_UM precionado
        {
            pisca_1000(); // Pica LED a cada 1s
        }
        else if (gpio_get_level(BOTAO_TRES) == false) // BOTAO_UM precionado
        {
            pisca_1500(); // Pica LED a 1,5s
        }
        else // Nenhum botão precionado
        {
            gpio_set_level(LED, 0); // LED apagado
        }
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}
