## CONEXÃO BLUETOOTH
> Controle de taréfas via bluetooth.

Para isso foi utilizado as biblotécas: `driver/gpio.h` para criação da ___interrupção___ e configuração da ___GPIOs___ - `freertos/FreeRTOS.h` e `freertos/task.h` utilizado para criar taréfas necessárias para ___Calibrar___, ___Aferir___ e ___Contabilizar___. - `esp_log` para informações no monitor serial. - `spp_acceptor` para criação e controle da comunicação bluetooth.

Para acessar a pasta main onde estão os códigos [clique aqui](main)

Ou acessar diretamente o código [main.c](main/main.c)

Ou volte ao [início](https://github.com/Matheus-Korth/Korth-Treinamento) do diretório.
