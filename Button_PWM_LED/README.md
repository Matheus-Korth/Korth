## Manipulação de GPIO2
>___3 Botões e 1 led onde:___
* botão 1 acende e apaga com ciclo pwm de 50%
* botão 2 acende e apaga com ciclo pwm de 75%
* botão 3 acende e apaga com ciclo pwm de 100%

Para isso foi utilizado as biblotécas: `driver/gpio.h` para configuração das ___GPIOs___ - `freertos/FreeRTOS.h` e `freertos/task.h` utilizando a função ___vTaskDelay___ - bibliotéca `driver/ledc.h` para controlar o ___Ciclo de trabalho___ e criar o efeito de ___esmaecer___ no led.

Para acessar a pasta main onde estão os códigos [clique aqui](main)

Ou acessar diretamente o código [main.c](main/main.c) - [configs.c](main/configs.h)

Ou volte ao [início](https://github.com/Matheus-Korth/Korth-Treinamento) do diretório.
