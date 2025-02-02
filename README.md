# Projeto de Interrupções - BitDogLab

### Objetivos
Neste projeto, o objetivo é:
- **Compreender o funcionamento e a aplicação de interrupções** em microcontroladores.
- **Identificar e corrigir o fenômeno de bouncing em botões**, implementando debouncing via software.
- **Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812**.
- **Estudar o uso de resistores de pull-up internos** em botões de acionamento.
- **Desenvolver um projeto funcional**, combinando hardware e software.

### Descrição do Projeto

Este projeto utiliza os seguintes componentes conectados à placa **BitDogLab**:

- **Matriz 5x5 de LEDs (endereçáveis)** WS2812 conectada à **GPIO 7**.
- **LED RGB**, com os pinos conectados às **GPIOs 11, 12 e 13**.
- **Botão A** conectado à **GPIO 5**.
- **Botão B** conectado à **GPIO 6**.

### Funcionalidades do Projeto

1. **LED vermelho piscando:** O LED vermelho do LED RGB deve piscar continuamente **5 vezes por segundo**.
2. **Incremento e decremento na matriz de LEDs:**
   - O **botão A** deve **incrementar** o número exibido na matriz de LEDs cada vez que for pressionado.
   - O **botão B** deve **decrementar** o número exibido na matriz de LEDs cada vez que for pressionado.
3. **Efeitos visuais com WS2812:**
   - Os LEDs WS2812 devem ser usados para criar **efeitos visuais** representando números de 0 a 9.
   - A formatação dos números deve ser clara, como caracteres em estilo digital (ex.: segmentos iluminados formando números).
   - Alternativamente, é permitido um estilo criativo, desde que o número seja claramente identificável.

### Requisitos do Projeto

1. **Uso de interrupções (IRQ):** Todas as funcionalidades relacionadas aos botões devem ser implementadas utilizando **rotinas de interrupção**.
2. **Debouncing:** É obrigatório implementar o **tratamento do bouncing** dos botões via software.
3. **Controle de LEDs:** O projeto deve incluir o uso de **LEDs comuns** e **LEDs WS2812**, demonstrando o domínio de diferentes tipos de controle.
4. **Organização do código:** O código deve estar **bem estruturado** e **comentado** para facilitar o entendimento.

### VÍDEO DO CÓDIGO

https://youtube.com/shorts/0dsVMNzgvsI?feature=share
