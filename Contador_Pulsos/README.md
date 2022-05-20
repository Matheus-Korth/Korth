## Manipulação de GPIO 4
> Criar um código que incremente um contador.
>* Cada vez que um pulso é capturado na entrada do GPIO.

Para isso foi utilizado as biblotécas: `driver/gpio.h` para criação da ___interrupção___ e configuração da ___GPIOs___ - `freertos/FreeRTOS.h` e `freertos/task.h` utilizado para criar uma taréfa de ___contagem de pulsos___. - `esp_log` para indicar os pulsos contabilizados no monitor serial.

Para acessar a pasta main onde estão os códigos [clique aqui](main)

Ou acessar diretamente o código [main.c](main/main.c)

Ou volte ao [início](https://github.com/Matheus-Korth/Korth-Treinamento) do diretório.
