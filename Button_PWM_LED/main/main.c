#include <stdio.h>
#include "configs.h"

// Bibliotécas FreeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Bibliotéca para uso das funções ledc
#include "driver/ledc.h"

// Bibliotéca para uso das GPIOs
#include "driver/gpio.h"

// Definições das Botões e suas GPIOs
#define BOTAO_UM 23   // ciclo de trabalho 50%
#define BOTAO_DOIS 22 // ciclo de trabalho 75%
#define BOTAO_TRES 21 // ciclo de trabalho 100%

// Definições do timer
#define LEDC_GPIO 27             // GPIO
#define LEDC_FADE_TIME 1200      // Tempo maximo do fade
#define LEDC_RESOLUTION_50 511   // Ciclo de Trabgalho em 50% -- ((2^10)-1)*50%
#define LEDC_RESOLUTION_75 767   // Ciclo de Trabgalho em 75% -- ((2^10)-1)*70%
#define LEDC_RESOLUTION_100 1023 // Ciclo de Trabgalho em 100% -- ((2^10)-1)
#define LEDC_FREQ 5000           // Frequência do temporizador LEDC em (Hz)

void app_main(void)
{
    /* Configurações do timer
    Insere as variaveis de configuração definidas no topo ao timer */
    ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,    // Modo de Velocidade -> LOW
        .duty_resolution = LEDC_TIMER_10_BIT, // Resolução do do ciclo de trabalho (2^10 = 1024 valores)
        .timer_num = LEDC_TIMER_0,            // Utilizado o TIMER 0
        .freq_hz = LEDC_FREQ,                 // Frequência de operação do sinal PWM
        .clk_cfg = LEDC_AUTO_CLK              // Seleção automatica da fonte geradora do clock (interna ou externa)
    };
    ledc_timer_config(&timer); // Configura o timer

    /*Configurações do canal PWM
    Seleção de pino para controle, modo e timer*/
    ledc_channel_config_t canal_LEDC = {
        .gpio_num = LEDC_GPIO,             // Seleciona o pino para atuar o PWM
        .speed_mode = LEDC_LOW_SPEED_MODE, // Modo de Velocidade -> LOW
        .channel = LEDC_CHANNEL_0,         // canal
        .timer_sel = LEDC_TIMER_0,         // Índice de temporizador 0 a 3
        .duty = 0,                         // define o dever de ledc
        .hpoint = 0                        // define hpoint
    };
    ledc_channel_config(&canal_LEDC); // Configura o canal

    ledc_fade_func_install(0); // Inicializa o serviço do Fade
    configura_gpios();         // Configuração das GPIOs

    while (true) // Estrutira de Repetição
    {
        if (gpio_get_level(BOTAO_UM) == false) // Ciclo de trabalho 50%
        {
            ledc_set_fade_time_and_start(canal_LEDC.speed_mode, canal_LEDC.channel, 0, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE);
            ledc_set_fade_time_and_start(canal_LEDC.speed_mode, canal_LEDC.channel, LEDC_RESOLUTION_50, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE);
            ledc_set_fade_time_and_start(canal_LEDC.speed_mode, canal_LEDC.channel, 0, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE);
        }
        else if (gpio_get_level(BOTAO_DOIS) == false) // Ciclo de trabalho 75%
        {
            ledc_set_fade_time_and_start(canal_LEDC.speed_mode, canal_LEDC.channel, 0, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE);
            ledc_set_fade_time_and_start(canal_LEDC.speed_mode, canal_LEDC.channel, LEDC_RESOLUTION_75, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE);
            ledc_set_fade_time_and_start(canal_LEDC.speed_mode, canal_LEDC.channel, 0, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE);
        }
        else if (gpio_get_level(BOTAO_TRES) == false) // Ciclo de trabalho 100%
        {
            ledc_set_fade_time_and_start(canal_LEDC.speed_mode, canal_LEDC.channel, 0, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE);
            ledc_set_fade_time_and_start(canal_LEDC.speed_mode, canal_LEDC.channel, LEDC_RESOLUTION_100, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE);
            ledc_set_fade_time_and_start(canal_LEDC.speed_mode, canal_LEDC.channel, 0, LEDC_FADE_TIME, LEDC_FADE_WAIT_DONE);
        }
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}