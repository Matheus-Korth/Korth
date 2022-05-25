#include <stdio.h>
#include "config.h"
#include "driver/gpio.h"       // Controle de GPIO.
#include "esp_log.h"           // LOGs (É mais rapido e utiliza menos memória do que printf).
#include "freertos/FreeRTOS.h" // Bibliotéca FreeRTOS.
#include "freertos/task.h"     // FreeRTOS para criação de tasks

#define PULSER GPIO_NUM_5 // Define a GPIO05 como PULSER
#define BOTAO GPIO_NUM_27

bool calibrar = false;
int pulsoAtual = 0;  // Variavel responsavel por atualizar novos pulsos.
int ultimoPulso = 0; // Variavel local para comparação de novos valores de pulso.
float pulsoCalibrado = 0;
float litro = 0;

static const char *TAG = ":MAIN:"; // Identificador do log que indica os pulsos.

TaskHandle_t xTaskHandleContador;
void vTaskContador(void);

TaskHandle_t xTaskHandleCalibracao;
void vTaskCalibracao(void);

void isr_pulser(void) // Interrupção.
{
    pulsoAtual += 1; // Acrecenta 1 a esta variavel a cada interrupção.
}

void app_main(void)
{
    // Cria a task responsavel por contar interrupções geradas pelo GPIO PULSER.
    //xTaskCreate(vTaskContador, "Contador", configMINIMAL_STACK_SIZE + 2048, NULL, 5, &xTaskHandleContador);
    vTaskDelay(pdMS_TO_TICKS(10)); // Pequeno delay antes de criar a interrupção.

    gpio_config_t io_conf;                     // Estrutura de configuração de gpio_config
    io_conf.intr_type = GPIO_PIN_INTR_POSEDGE; // Interrupção HABILITADA e configurada como borda de sinal ASCENDENTE.
    io_conf.pin_bit_mask = (1ULL << PULSER);   // Define PULSER como a GPIO
    io_conf.mode = GPIO_MODE_INPUT;            // Configura como INPUT
    io_conf.pull_down_en = 0;                  // Desativa pull down
    io_conf.pull_up_en = 0;                    // Desativa pull up
    gpio_config(&io_conf);                     // Configura a GPIO com os parâmetros io_conf.

    // Botão
    io_conf.intr_type = GPIO_INTR_DISABLE; /* desabilita interrupção */
    io_conf.mode = GPIO_MODE_INPUT;        /* define como entrada */
    io_conf.pull_down_en = 0;              /* desabilita pull_down */
    io_conf.pull_up_en = 1;                /* habilita pull_up */
    io_conf.pin_bit_mask = 1ULL << BOTAO;  /* seleciona pino 0 */
    gpio_config(&io_conf);                 /* passa configurações na função gpio_conf */

    gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3); // Vetor de Interrupção.
    gpio_isr_handler_add(PULSER, isr_pulser, NULL); // GPIO, Void que será chamado durante as interrupções, NULL.

    while (1)
    {
        if (gpio_get_level(BOTAO) != 1 && (calibrar == false))
        {
            if (calibrar == false)
            {
                calibrar = true;
                ESP_LOGI(TAG, "Calibração iniciada!");
                xTaskCreate(vTaskCalibracao, "task_Calibracao", configMINIMAL_STACK_SIZE + 2048, NULL, 5, &xTaskHandleCalibracao);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
        }
        if (gpio_get_level(BOTAO) != 1 && (calibrar == true))
        {
            if (calibrar == true)
            {
                calibrar = false;
                ESP_LOGI(TAG, "Calibrado com sucesso");
                vTaskDelete(xTaskHandleCalibracao);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(30)); // Evita crash no ESP32
    }
}

void vTaskCalibracao(void)
{
    while (1)
    {
        
    }
    
}

void vTaskContador(void) // Task para contar os pulsos.
{
    float ultimoPulso = 0; // Variavel local para comparação de novos valores de pulso.
    float litros = 0;

    while (1) // Estrutura de repetição para atualizar os valores de pulso recebidos pela interrupção.
    {

        if (ultimoPulso != pulsoAtual) // Se houver um novo pulso então..
        {
            ultimoPulso = pulsoAtual;                               // Atualiza a variavel de ultimoPulso
            pulsoCalibrado /= 20;
            ultimoPulso = ultimoPulso / pulsoCalibrado;
            ESP_LOGI(TAG, "Numero de pulsos = %.2f \n", ultimoPulso); // Mostra o valor do pulso atualizado.
        }
        vTaskDelay(pdMS_TO_TICKS(30)); // Evita crash no ESP32
    }
}