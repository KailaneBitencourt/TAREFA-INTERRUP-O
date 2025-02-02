// BIBLIOTECAS UTILIZADAS
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "pico/multicore.h"
#include "matrizes.h"

// DEFINIÇÃO DAS GPIO
#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define GPIO_LED_RED 13
#define GPIO_BUTTON_A 5
#define GPIO_BUTTON_B 6
#define tempo 400
#define DEBOUNCE_DELAY_US 200000

// Variável global para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 0; // Intensidade do vermelho
uint8_t led_g = 0; // Intensidade do verde
uint8_t led_b = 20; // Intensidade do azul



volatile int contador = 0; // Contador global

// Função para enviar um pixel ao WS2812
static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

// Função para definir a cor RGB de um pixel
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

// Função para exibir o número nos LEDs
void set_number(int number, uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t color;
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        double brightness = numeros[number][i]; // Obtém o brilho do número
        color = urgb_u32(r * brightness, g * brightness, b * brightness); // Aplica intensidade
        put_pixel(color);
    }
}

// Função para apagar todos os LEDs
void limpa_leds()
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        put_pixel(0);
    }
}

// Função de configuração de pinos
void configuracoes()
{
    gpio_init(GPIO_LED_RED); // Inicializando
    gpio_set_dir(GPIO_LED_RED, GPIO_OUT); // Definindo como saída
    gpio_init(GPIO_BUTTON_A); // Inicializando
    gpio_init(GPIO_BUTTON_B); 
    gpio_set_dir(GPIO_BUTTON_A, GPIO_IN);
    gpio_set_dir(GPIO_BUTTON_B, GPIO_IN); // Botões definidos como entrada
    gpio_pull_up(GPIO_BUTTON_A); // Ativando resistores pull-up internos
    gpio_pull_up(GPIO_BUTTON_B);
}

// Função para piscar o LED vermelho
void led_vermelho()
{
    while (true)
    {
        gpio_put(GPIO_LED_RED, 1);
        sleep_ms(100);
        gpio_put(GPIO_LED_RED, 0);
        sleep_ms(100);
    }
}


// Função de interrupção única para ambos os botões
void interrupcao(uint gpio, uint32_t events) {

    static volatile uint64_t last_interrupt_time_a = 0;
    static volatile uint64_t last_interrupt_time_b = 0;
    uint64_t current_time = time_us_64();

    if (gpio == GPIO_BUTTON_A) { // Verifica se foi o botão A
        if (current_time - last_interrupt_time_a > DEBOUNCE_DELAY_US) {
            contador = (contador + 1) % 10;
            last_interrupt_time_a = current_time;
        }
    } else if (gpio == GPIO_BUTTON_B) { // Verifica se foi o botão B
        if (current_time - last_interrupt_time_b > DEBOUNCE_DELAY_US) {
            contador = (contador - 1 + 10) % 10;
            last_interrupt_time_b = current_time;
        }
    }
}
int main()
{
    stdio_init_all();
    configuracoes();

    // Inicia a função led_vermelho() no segundo core
    multicore_launch_core1(led_vermelho);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    // Configura as interrupções para os botões
    gpio_set_irq_enabled_with_callback(GPIO_BUTTON_A, GPIO_IRQ_EDGE_RISE, true, &interrupcao);
    gpio_set_irq_enabled_with_callback(GPIO_BUTTON_B, GPIO_IRQ_EDGE_RISE, true, &interrupcao);

    while (true)
    {
        set_number(contador, led_r, led_g, led_b); // Exibe o número atual
        sleep_ms(tempo);
        limpa_leds(); // Apaga os LEDs
        sleep_ms(tempo);
    }

    return 0;
}
