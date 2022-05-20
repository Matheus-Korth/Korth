#include <stdio.h>
#include "driver/gpio.h"       // Controle de GPIO.
#include "esp_log.h"           // LOGs (É mais rapido e utiliza menos memória do que printf).
#include "freertos/FreeRTOS.h" // Bibliotéca FreeRTOS.
#include "freertos/task.h"     // FreeRTOS para criação de tasks

#define PULSER GPIO_NUM_5 // Define a GPIO05 como PULSER

int pulsoAtual = 0; // Variavel responsavel por atualizar novos pulsos.

static const char *TAG = ":MAIN:"; // Identificador do log que indica os pulsos.

TaskHandle_t xTaskHandleContador;
void vTaskContador(void);

void isr_pulser(void) // Interrupção.
{
    pulsoAtual += 1; // Acrecenta 1 a esta variavel a cada interrupção.
}

void app_main(void)
{
    // Cria a task responsavel por contar interrupções geradas pelo GPIO PULSER.
    xTaskCreate(vTaskContador, "task_Contador", configMINIMAL_STACK_SIZE + 2048, NULL, 10, &xTaskHandleContador);
    vTaskDelay(pdMS_TO_TICKS(10)); // Pequeno delay antes de criar a interrupção.

    gpio_config_t io_conf;                     // Estrutura de configuração de gpio_config
    io_conf.intr_type = GPIO_PIN_INTR_POSEDGE; // Interrupção HABILITADA e configurada como borda de sinal ASCENDENTE.
    io_conf.pin_bit_mask = (1ULL << PULSER);   // Define PULSER como a GPIO
    io_conf.mode = GPIO_MODE_INPUT;            // Configura como INPUT
    io_conf.pull_down_en = 0;                  // Desativa pull down
    io_conf.pull_up_en = 0;                    // Desativa pull up
    gpio_config(&io_conf);                     // Configura a GPIO com os parâmetros io_conf.

    gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3); // Vetor de Interrupção.
    gpio_isr_handler_add(PULSER, isr_pulser, NULL); // GPIO, Void que será chamado durante as interrupções, NULL.
}

void vTaskContador(void) // Task para contar os pulsos.
{
    int ultimoPulso = 0; // Variavel local para comparação de novos valores de pulso.

    while (1) // Estrutura de repetição para atualizar os valores de pulso recebidos pela interrupção.
    {
        if (ultimoPulso != pulsoAtual) // Se houver um novo pulso então..
        {
            ultimoPulso = pulsoAtual;                               // Atualiza a variavel de ultimoPulso
            ESP_LOGI(TAG, "Numero de pulsos = %d \n", ultimoPulso); // Mostra o valor do pulso atualizado.
        }
        vTaskDelay(pdMS_TO_TICKS(10)); // Evita crash no ESP32
    }
}