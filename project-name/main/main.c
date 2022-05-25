#include <stdio.h>
#include "spp_acceptor.h"      // Bibliotéca BT
#include "driver/gpio.h"       // Controle de GPIO.
#include "esp_log.h"           // LOGs (É mais rapido e utiliza menos memória do que printf).
#include "freertos/FreeRTOS.h" // Bibliotéca FreeRTOS.
#include "freertos/task.h"     // FreeRTOS para criação de tasks

#define PULSER GPIO_NUM_5 // Define a GPIO05 como PULSER

#define BYTES_PER_LINE 16
char char_buffer[BYTES_PER_LINE + 1];

float ultimoPulso = 0;         // Variavel local para comparação de novos valores de pulso.
int pulsoAtual = 0;            // Variavel responsavel por atualizar novos pulsos.
int aux = 1;                   // Variavel para intertravamento de comandos.
int pulsoCalibrado = 0;        // Variaverl para armazenar a calibração.
float litros = 0;              // Conversão de pulsos para litros.
float ultimoAbastecimento = 0; // Armazena ultimo abastecimento.

static const char *TAG = ""; // Identificador do log que indica os pulsos.

/*      Taréfa de Calibração     */
TaskHandle_t xTaskHandleCalibracao;
void vTaskCalibracao(void);

/*      Taréfa de Aferição       */
TaskHandle_t xTaskHandleAfericao;
void vTaskAfericao(void);

/*      Taréfa de Abastecimento     */
TaskHandle_t xTaskHandleAbastecimento;
void vTaskAbastecimento(void);

void isr_pulser(void) // Interrupção.
{
    pulsoAtual += 1; // Acrecenta 1 a esta variavel a cada interrupção.
}

void app_main(void)
{
    BT_init(); // inicia o BT

    /*                      Configuração GPIO PULSER                                                              */
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

void comando_BT(int data) // Comandos recebidos pelo Bluetooth
{
    /* Verifica se o comando ja foi executado, ou se esta tentando
    enviar outro comando antes de encerrar a taréfa em andamento.*/
    if (data == 10 || data == 20 || data == 30 || data == 12 || data == 22 || data == 32)
    {
        if (aux != 1)
        {
            if (aux == 2 && data != 12)
            {
                ESP_LOGE(TAG, "Calibração em andamento!\n");
            }
            if (aux == 3)
            {
                ESP_LOGE(TAG, "Aferição em andamento!\n");
            }
            if (aux == 4)
            {
                ESP_LOGE(TAG, "Abastecimento em andamento!\n");
            }
        }
    }
    if (data == 10 && aux == 1) // Inicia a calibração.
    {
        aux = 2;
        xTaskCreate(vTaskCalibracao, "task_Calibrcao", configMINIMAL_STACK_SIZE + 2048, NULL, 2, &xTaskHandleCalibracao);
        ESP_LOGI(TAG, "Calibração inicíada!\n");
    }
    if (data == 12 && aux == 2) // Finaliza calibração.
    {
        aux = 1;
        vTaskDelete(xTaskHandleCalibracao);
        ESP_LOGI(TAG, "Calibração encerrada!\n");
    }
    if (data == 20 && aux == 1) // Inicia aferição
    {
        aux = 3;
        xTaskCreate(vTaskAfericao, "task_Afericao", configMINIMAL_STACK_SIZE + 2048, NULL, 2, &xTaskHandleAfericao);
        ESP_LOGI(TAG, "Aferição inicíada!\n");
    }
    if (data == 22 && aux == 3) // Encerra aferição
    {
        aux = 1;
        vTaskDelete(xTaskHandleAfericao);
        ESP_LOGI(TAG, "Aferição encerrada!\n");
    }
    if (data == 30 && aux == 1) // Inicia tarefa de abastecimento.
    {
        aux = 4;
        xTaskCreate(vTaskAbastecimento, "task_Abastecimento", configMINIMAL_STACK_SIZE + 2048, NULL, 2, &xTaskHandleAbastecimento);
        ESP_LOGI(TAG, "Abastecimento inicíado!\n");
    }
    if (data == 32 && aux == 4) // conclui abastecimento.
    {
        aux = 1;
        vTaskDelete(xTaskHandleAbastecimento);
        ESP_LOGI(TAG, "Abastecimento encerrado!\n");
    }
    if (data == 40 && aux == 1) // Exibe o valor do ultimo abastecimento armazenado.
    {
        ESP_LOGI(TAG, "O ultimo abastecimento foi de %.3f Litros \n", ultimoAbastecimento);
    }
    /* A variavel " aux " foi utilizada para intertravamento dos comandos
    garantindo que apena uma tarefa execute por vez. */
}

void vTaskCalibracao(void) // Taréfa de calibração.
{
    pulsoCalibrado = 0; // Reseta a calibração anterior
    pulsoAtual = 0;     // começa a contabilizar os pulsos novamente.

    while (1) // Estrutura de repetição para atualizar os valores de pulso recebidos pela interrupção.
    {
        if (pulsoCalibrado != pulsoAtual) // Se houver um novo pulso então..
        {
            pulsoCalibrado = pulsoAtual;                                 // Atualiza a variavel de pulsoCalibrado.
            ESP_LOGI(TAG, "Calibrando = %d pulsos. \n", pulsoCalibrado); // Mostra pulsos durante a calibração.
        }
        vTaskDelay(pdMS_TO_TICKS(30)); // Evita crash no ESP32
    }
}

void vTaskAfericao(void) // Taréfa de aferição.
{
    pulsoAtual = 0;
    ultimoPulso = 0;

    while (1)
    {
        if (ultimoPulso != pulsoAtual) // Se houver um novo pulso então..
        {
            float pulsoFloat = pulsoAtual;                      // Armazena em float os pulsos
            litros = pulsoFloat / pulsoCalibrado;               // Converte para litros.
            ultimoPulso = pulsoAtual;                           // Atualiza a variavel de ultimoPulso
            ESP_LOGI(TAG, "Aferição = %.3f Litros \n", litros); // Mostra o valor do pulso atualizado.
        }
        vTaskDelay(pdMS_TO_TICKS(30)); // Evita crash no ESP32
    }
}

void vTaskAbastecimento(void)
{
    pulsoAtual = 0; 
    ultimoPulso = 0;

    while (1)
    {
        if (ultimoPulso != pulsoAtual)
        {
            float pulsoFloat = pulsoAtual;                         // Transforma inteiros em pontos flutuantes
            litros = pulsoFloat / pulsoCalibrado;                  // Define Quantos pulsos representa 1 litro
            ultimoAbastecimento = litros;                          // Salva o ultimo abastecimento
            ultimoPulso = pulsoAtual;                              // Atualiza a variavel de ultimoPulso
            ESP_LOGI(TAG, "Abastecendo = %.3f Litros \n", litros); // Mostra o valor do pulso atualizado.
        }
        vTaskDelay(pdMS_TO_TICKS(30)); // Evita crash no ESP32
    }
}