# Biblioteca para Aquisição de Áudio com Microfone

Esta biblioteca (`microphone.c`) foi desenvolvida para facilitar a leitura de dados de um microfone utilizando o ADC de um microcontrolador, Raspberry Pi Pico W (RP2040). O foco principal é oferecer um método eficiente para captura de dados, utilizando DMA (Direct Memory Access) para reduzir o uso da CPU e permitir amostragens de alta taxa sem comprometer o desempenho do sistema.

## Recursos da Biblioteca

A biblioteca inclui as seguintes funcionalidades:

- **Inicialização do ADC e do pino do microfone** (`Mic_Init()`): Configura o ADC para capturar os dados do microfone.
- **Inicialização do ADC e do pino do microfone (Versão DMA)** (`Mic_InitDMA()`): Utiliza o DMA para transferência eficiente dos dados do ADC para um buffer.
- **Ajuste da taxa de amostragem** (`Mic_SampleRate(sample_rate)`): Permite definir a taxa de amostragem do ADC.
- **Leitura dos dados**:
  - `Mic_ReadBuffer(buffer, size)`: Faz a leitura sequencial dos dados sem DMA.
  - `Mic_ReadBufferDMA(buffer, size)`: Usa DMA para transferir os dados do ADC para um buffer de forma eficiente (Programa espera o preenchimento do buffer).
  - `Mic_ReadBufferDMA_IT(buffer, size)`: Usa DMA + Interrupção que sinaliza o fim da transferência, tornando o processo não bloqueante (Programa continua seu fluxo), e permitindo que o usuário realize o processamento desejado após o disparo da interrupção.
- **Compatibilidade com microfones que possuem offset DC**: No exemplo, o microfone da BitDogLab é utilizado, que tem um offset de 1.65V.

## Como Usar a Biblioteca

### Configuração

1. **Inclua a biblioteca no seu projeto:**
   ```c
   #include "microphone.h"
   ```
2. **Inicialize o microfone:**
   ```c
   Mic_Init();
   ```
3. **Inicialize o microfone (Versão pra DMA):**
   ```c
   Mic_InitDMA();
   ```
4. **Defina a taxa de amostragem:**
   ```c
   Mic_SampleRate(22000); // Define 22 kHz como taxa de amostragem
   ```
5. **Leia os dados do microfone:**
   ```c
   uint16_t buffer[1024];  //Buffer para salvar as amostras
   Mic_ReadBufferDMA(buffer, 1024); // Captura 1024 amostras nesse caso utilizando DMA
   ```

## Exemplo de Uso em um Programa
Veja o arquivo "audio_example", onde os dados do microfone são enviados via porta serial. Observe que existem duas main() no programa, uma utilizando Mic_ReadBufferDMA() que aguarda o preenchimento do buffer através do DMA, e outra utiliza Mic_ReadBufferDMA_IT() que não aguarda o preenchimento do buffer, mas dispara uma flag de interrupção ao enche-lo, nesse caso é importante configurar a função dma_handler() que é chamada no finalizar das transferências.

## Processamento dos Dados em Python

Para converter os dados capturados em um arquivo de áudio `.wav`, utilize o script do arquivo `gerarwave`.

Para executar o script você deve ter na pasta do projeto, um arquivo `.txt` contendo os dados do buffer de gravação, enviados via porta serial, o script em python ira gerar 
um arquivo de aúdio `.wav` para reprodução.

Dica: O Visual Studio Code tem uma opção que exporta os dados recebidos via porta serial, "Toggle File Loggin" e "Chose Log File Directory" permitem ativar e escolher o diretório onde devem ser salvos os dados.

![image](https://github.com/user-attachments/assets/01942b79-2714-4041-8851-41d208fec2c7)


O código em python também filtra valores inválidos, então não se preocupe se você tem valores fora de escala, como letras ou valores muito altos!


## Análise do Sinal com FFT

O script em python também pode fazer análise temporal e espectral do sinal de audio

![Espectro](https://github.com/user-attachments/assets/0f71ee05-b72b-459e-a986-090ab450d230)


## Conclusão

Esta biblioteca permite capturar e processar sinais de microfone de forma eficiente, utilizando DMA para maior desempenho. O processamento em Python possibilita converter os dados em um arquivo de áudio, realizar análises espectrais e reproduzir o som capturado. Essa solução é ideal para aplicações como reconhecimento de voz, processamento de sinais e experimentos com aquisição de áudio.


