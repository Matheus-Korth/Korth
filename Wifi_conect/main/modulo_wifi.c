#include <string.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "led.h"
#include "timer.h"

#define WIFI_SSID "Korth"           // Nome da rede wii
#define WIFI_PASS "157935749587452" // Senha da rede wifi
#define MAX_TENTATIVAS 3            // Numero de tentativas de conexão

static const char *TAG = "[WI-FI] --> ";

static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    static int numeroDeTentativas = 0; // Variavel para tentativas de conexões.

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) // Se o Wi-Fi for iniciado...
    {
        esp_wifi_connect(); // Conecta-se ao wi-fi.
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) // Se a conecção falhar...
    {
        if (numeroDeTentativas < MAX_TENTATIVAS) // Se "numeroDeTentativas" for MENOR que "MAX_TENTATIVAS"...
        {
            esp_wifi_connect();   // Conecta-se ao wi-fi novamente.
            numeroDeTentativas++; // Incrementa 1 ao "numeroDeTentativas"
            ESP_LOGI(TAG, "Tentanto conectar novamente ao AP");
        }
        else // Se "numeroDeTentativas" for IGUAL "MAX_TENTATIVAS"...
        {
            ESP_LOGI(TAG, "Falha ao conectar a SSID:%s, Senha:%s", WIFI_SSID, WIFI_PASS);
        }
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) // Se a conexão for estabelecida e um endereço ip for atribuido...
    {
        numeroDeTentativas = 0; // Reseta "numeroDeTentativas".
        stop_led_wifi_timer(); // Para o timer que faz o LED piscar
        set_level_led_wifi(1); // Define o estado do LED como ligado para informar que está conectado a rede Wi-fi.
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;            // Informações da conexão.
        ESP_LOGI(TAG, "Conectado a SSID: %s Senha: %s", WIFI_SSID, WIFI_PASS); // Mostra a rede conectada.
        ESP_LOGI(TAG, "IP atribuído: " IPSTR, IP2STR(&event->ip_info.ip));     // Mostra o IP.
    }
}

/**
 * @brief Inicia o módulo Wi-Fi
 */
void wifi_init(void)
{
    ESP_ERROR_CHECK(esp_netif_init()); // Inicializa a pilha TCP/IP subjacente.

    ESP_ERROR_CHECK(esp_event_loop_create_default()); // Crie um loop de eventos padrão.
    esp_netif_create_default_wifi_sta();              // Cria WIFI STA padrão.

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); // Define as configurações de Wi-Fi padrão.
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));                // Inicia a taréfa de Wi-fi com a configuraçõão padrão.

    // Manipuladores de evento.
    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;

    /* Registras os manipuladores de evento. */
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL, &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL, &instance_got_ip));

    wifi_config_t wifi_config = // Define as configurações do modulo Wi-fi.
        {
            .sta =
                {
                    .ssid = WIFI_SSID,
                    .password = WIFI_PASS,

                    .threshold.authmode = WIFI_AUTH_WPA2_PSK,

                    .pmf_cfg = {
                        .capable = true,
                        .required = false},
                },
        };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));               // Define um mode de operação.
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config)); // Seta as configurações definidas em "wifi_config"
    ESP_ERROR_CHECK(esp_wifi_start());                               // Inicia o módulo Wi-fi.

    start_led_wifi_timer(); // Led do Wi-fi começa a piscas.

    ESP_LOGI(TAG, "Módulo Wi-fi Iniciado.");
}