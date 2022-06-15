## CONECXÃO WI-FI
> Esté código se conecta a uma rede Wi-fi.
>* Enquanto não estiver conectado a rede um LED pisca.

Para isso foi utilizado as biblotécas: `driver/gpio.h` para configuração da ___GPIOs___ - `esp_timer.h`para criação e configuração do timer que faz o ___LED___ piscar. - `esp_wifi.h` para criar e estabeecer uma conexão a uma rede ___Wi-fi___ - `esp_event.h`para monitorar e informar sobre os ___eventos___ de conexão com a rede.

Para acessar a pasta main onde estão os códigos [clique aqui](main)

Ou acessar diretamente o código [main.c](main/main.c)

Você também pode acessar:
[led.c](main/led.c)
[timer.c](main/timer.c)
[modulo_nvs](main/modulo_nvs.c)
[modulo_wifi.c](main/modulo_wifi.c)


Ou volte ao [início](https://github.com/Matheus-Korth/Korth-Treinamento) do diretório.
