# Projeto Semáforo Inteligente - Smart City 🚦

&ensp;Nossa proposta é desenvolver um semáforo que se adapte automaticamente ao fluxo de veículos, detectando a presença de carros e alternando entre diferentes modos de operação, como o "modo noturno". Utilizando um sensor LDR para medir a luminosidade e um sensor de proximidade em uma das ruas, o sistema é projetado para gerenciar o fluxo de maneira eficiente e inteligente.

## Visão Geral do Sistema

### Detecção de Veículos com Sensor de Proximidade
- O sistema possui dois semáforos: um na avenida principal e outro em uma rua menor.
- Um sensor de proximidade é instalado na rua menor, onde ele detecta a chegada de veículos. Quando um carro se aproxima, o sensor de proximidade envia um sinal para o broker que estara conectado com ambos os semáforos, mudando o estado dos dois, que ativa o sinal verde na rua menor, para permitir a passagem do veículo, ativando o vermelho na avenida principal.
- Esse comportamento é controlado por uma estrutura de repetição _while_ no código, que mantém o sinal verde da rua menor ativado enquanto um carro é detectado.

### Gerenciamento do Tempo de Abertura
- Para evitar que o fluxo da rua menor interfira excessivamente no fluxo da avenida principal, o semáforo da rua menor permanece verde por um máximo de 15 segundos, mesmo que haja detecção contínua de veículos. Isso evita que o tráfego da avenida principal seja interrompido por longos períodos.
- Caso não haja veículos na rua menor, o semáforo desta rua permanecerá vermelho, permitindo que o semáforo da avenida fique aberto para facilitar o fluxo contínuo.

### Modo Noturno com Sensor LDR
- O sistema também utiliza um sensor de luz (LDR) para monitorar a intensidade da luz ambiente.
- Quando a luminosidade cai abaixo de um certo nível (indicando o período noturno), o sistema muda automaticamente para o "modo noturno". Nesse modo, os semáforos operam de forma reduzida ou intermitente, otimizando o consumo de energia e ajustando-se às condições noturnas, onde o fluxo de veículos é menor.

## Fluxo de Operação

### Funcionamento Normal (Diurno)
- Durante o dia, o semáforo da avenida principal permanece verde continuamente, a menos que o sensor de proximidade na rua menor detecte um veículo.
- Quando o sensor de proximidade é acionado, o semáforo da rua menor muda para verde, permitindo que os carros passem.
- Um loop _while_ é utilizado para manter o semáforo da rua menor aberto enquanto o sensor detecta a presença do carro.
- Após 15 segundos, o semáforo da rua menor automaticamente volta a ficar vermelho, garantindo que o tráfego na avenida principal não seja interrompido por muito tempo.

### Funcionamento em Modo Noturno
- Quando a luminosidade captada pelo sensor LDR atinge um nível baixo (indicando noite), o sistema muda automaticamente para o "modo noturno".
- Neste modo, o semáforo da rua menor e da avenida podem operar de forma mais simplificada, permitindo a passagem dos veículos de acordo com uma programação reduzida, sem causar retenção desnecessária de veículos.

## Configuração da Interface Online

Uma interface online será desenvolvida para permitir o monitoramento e ajuste do comportamento dos semáforos. Com esta interface, o usuário poderá:
- Ativar ou desativar manualmente o "modo noturno".
- Visualizar em tempo real os dados captados pelo sensor de luz (LDR) e pelo sensor de proximidade.
- Ajustar configurações de operação, como o tempo máximo de abertura do semáforo da rua menor.

## Integração com ESP32 e Ubidots

Para facilitar o monitoramento centralizado e permitir a comunicação entre os semáforos, cada um será equipado com um microcontrolador ESP32, que estará conectado a um dashboard no Ubidots. Essa integração permite:
- Visualizar o status de cada semáforo remotamente.
- Ajustar o comportamento dos semáforos com base nos dados recebidos.
- Otimizar o fluxo de veículos em toda a cidade, tornando o tráfego mais eficiente.

## Documentação e Entrega

Este repositório contém toda a documentação do projeto, incluindo:
- Instruções para montagem física e eletrônica dos semáforos.
- Código do sistema, com a lógica do `while` para detecção de veículos.
- Link para a interface online de controle e monitoramento.
- Vídeo demonstrando o funcionamento do sistema em diferentes condições de tráfego e luminosidade.

### Conclusão

&ensp;Nosso projeto explora como semáforos inteligentes podem melhorar a eficiência do tráfego em cidades modernas. Ao utilizar sensores e modos adaptativos, esse sistema proporciona uma experiência mais fluida para os motoristas, além de reduzir o consumo de energia em horários de menor movimento.
