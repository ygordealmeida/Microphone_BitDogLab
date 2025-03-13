#include <stdio.h>
#include "pico/stdlib.h"
#include "microphone.h"
#include "hardware/adc.h"
#include "hardware/dma.h"


#define MIC_PIN 28
#define ADC_CLOCK 48000000
#define ADC_CYCLES 96



//Caso va usar interrupção é muito importante configurar o handler:
void dma_handler() {
    // Limpa a flag de interrupção do canal DMA
    dma_hw->ints0 = 1u << dma_channel;
    
    // Sinaliza que a transferência foi concluída
    dma_transfer_complete = true;
    adc_run(true);
}


// FUNÇÃO MAIN PARA CAPTURA NÃO BLOQUEANTE

/*
int main() {


    stdio_init_all();
    Mic_InitDMA();
    static uint16_t meubuffer[120000];
    Mic_SampleRate(22000);

    // Iniciar captura sem bloquear
    //Uma pequena pausa para dar tempo de abrir a porta serial
    //Melhoria a fazer: usar um botão para iniciar a captura
    sleep_ms(4000);
    printf("start\n");
    sleep_ms(1000);

    absolute_time_t start_time = get_absolute_time(); // Marca o início

    Mic_ReadBufferDMA_IT(meubuffer, 120000);
    while (true) {
        if (dma_transfer_complete) {
            absolute_time_t end_time = get_absolute_time(); // Marca o fim
            int64_t duration_us = absolute_time_diff_us(start_time, end_time); // Calcula diferença
            printf("Tempo de captura: %.2f s\n", duration_us / 1e6f);
            printf("Taxa real: %.2f ksa/s\n", (sizeof(meubuffer)/sizeof(meubuffer[0])) / (duration_us / 1e6f) / 1000);


            printf("Buffer cheio! Processando dados...\n");

            for (uint32_t i = 0; i < sizeof(meubuffer)/sizeof(meubuffer[0]); i++){
                printf("%d\n", meubuffer[i]);
            }
            printf("finish\n");

            // Reiniciar captura (caso queira continuar coletando)
            dma_transfer_complete = false;
            

        }
        else {
            printf("Aguardando buffer...\n");
            sleep_ms(1000);
        }

        // Outras tarefas podem rodar aqui sem travar a CPU!
    }
}

*/


//FUNCAO MAIN PARA CAPTURA BLOQUEANTE,
//NÃO PRECISA CONFIGURAR O DMA_HANDLER

int main()
{
    stdio_init_all();
    static uint16_t meubuffer[120000];
    //Nesse exemplo você deve abrir a porta serial para ver os valores lidos do microfone
    //A partir da msg "start" você pode gravar o som
    sleep_ms(4000);
    printf("start\n");
    sleep_ms(1000);
    Mic_InitDMA();

    Mic_SampleRate(22000);
    absolute_time_t start_time = get_absolute_time(); // Marca o início
    
    Mic_ReadBufferDMA(meubuffer, sizeof(meubuffer)/sizeof(meubuffer[0]));

    absolute_time_t end_time = get_absolute_time(); // Marca o fim
    int64_t duration_us = absolute_time_diff_us(start_time, end_time); // Calcula diferença


    printf("Tempo de captura: %.2f s\n", duration_us / 1e6f);
    printf("Taxa real: %.2f ksa/s\n", (sizeof(meubuffer)/sizeof(meubuffer[0])) / (duration_us / 1e6f) / 1000);

    //Salve em um arquivo txt o buffer exportado pela porta serial, veja um exemplo na pasta
    for (uint32_t i = 0; i < sizeof(meubuffer)/sizeof(meubuffer[0]); i++){
        printf("%d\n", meubuffer[i]);
    }
    printf("finish\n");


    while (true) {
     }
    
}

