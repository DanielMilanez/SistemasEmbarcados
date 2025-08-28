## Como utilizar o LPTIM no STM32

Assim como outras técnicas de baixo consumo, o uso do LPTIM (Low Power Timer) tem como objetivo otimizar o consumo energético e prolongar a vida útil da bateria.

O LPTIM é um temporizador de 16 bits com características específicas para operação em baixo consumo, destacando-se por:

- Operação em Modos de Baixo Consumo: Funciona mesmo quando o microcontrolador está em modo STOP, utilizando fontes de clock de baixo consumo como LSI (Low-Speed Internal) ou LSE (Low-Speed External) 

- Fontes de Clock Flexíveis: Pode ser alimentado por diversas fontes de clock, incluindo LSI, LSE, HSI ou APB 

- Modos de Operação: Suporta diferentes modos, como PWM, contagem assíncrona, timeout e captura de pulsos, permitindo versatilidade em aplicações de baixo consumo .
ST

A serie de microcontroladores STM32L0xxx possui algumas features, que são descritas de acordo com o [application notes](https://www.st.com/resource/en/application_note/an4865-lowpower-timer-lptim-applicative-use-cases-on-stm32-mcus-and-mpus-stmicroelectronics.pdf).

### Comparação entre TIM x LPTIM modos de funcionamento

|Periferico|Run mode|Low-power run|Low-power Sleep|Stop|
|----------|:------:|:-----------:|:-------------:|:--:|
|TIM       |  X     |    X        |       -       | -  |
|LPTIM     |  X     |    X        |       X       | X  |


### Domínios de clock do LPTIM

O LPTIM possui dois domínios de clock, o que significa que ele pode ser configurado por dois "grupos geradores de clock":

- Domínio de clock APB (Advanced Peripheral Bus): contém a interface APB e todas as funções principais dos periféricos, como registradores e sinais conectados à CPU. Este é o domínio utilizado pelo TIM padrão.

- Domínio de clock do KERNEL: pode ser sincronizado pela fonte de clock APB ou por outras fontes internas, incluindo LSE, LSI, MSIK e HSI. Também pode ser sincronizado a partir de uma fonte externa através da entrada 1 do timer.

Sua caracteristica principal é continuar funcionando em modos de baixo consumo de energia com quase todas as fontes de clock desativadas.

|Modo |HSI|LSI|LSE|PCLK|Clock externo|
|:---:|:-:|:-:|:-:|:--:|:-----------:|
|RUN  | X | X | X | X  | X           |
|SLEEP| X | X | X | X  | X           |
|STOP | - | X | X | -  | X           |

Por isso, é fundamental escolher corretamente qual fonte de clock utilizar para cada modo de operação. Por exemplo, para uso no modo STOP com fonte interna, o LSI é a fonte indicada.

### Modos de operação do LPTIM

O LPTIM oferece diversos modos de operação, entre eles:

- PWM (Modulação por Largura de Pulso): Gera um sinal PWM com frequência e duty cycle configuráveis.

- Contagem Assíncrona: Conta pulsos de uma fonte externa, útil para medir frequências ou eventos.

- Timeout: Gera uma interrupção após um tempo pré-determinado, permitindo acordar o microcontrolador de modos de baixo consumo.

- Input capture: Captura a duração de pulsos de uma fonte externa, útil para medições precisas de tempo.

## Como configurar o LPTIM para gerar um PWM

Na aba ***Pinout & Configuration***, procure e habilite o periférico LPTIM1, ou o LPTIM2 se disponível. Em seguida configure os pinos conforme a funcionalidade que deseja usar (PWM out, input capture etc) em nosso caso iremos utilizar o PWM output.

Configure as opções do LPTIM, que são semelhantes ao TIM padrão, diferenciando-se principalmente pela escolha da fonte de clock, que deve ser compatível com o modo de baixo consumo desejado.

1. Clock source: Escolha entre APB, LSE, LSI, etc.
1. Prescaler: Ajuste para o valor que desejar.
1. Counter source: Interno ou externo
1. Trigger source: Via software flag ou externo.
1. Ative interrupções se desejar.

Abra a configurações das fontes de clock (LSE, LSI):

- No clock configuration, verifique que as fontes LSE ou LSI estão ativdas, caso as utilize para o LPTIM.
- Caso contrário e você esteja utilizando o APB ao invés do KERNEL ajuste os clocks ABP conforme o necessário.

Algo relevante para se ressaltar é a forma como devemos utilizar as funções do LPTIM. Como ele é focado em baixo consumo, ele utiliza fontes de clock "lentas" como o LSI (~32 kHz) ou o LSE (32.768 kHz), ou então o clock externo. Justamente por isso, ele é um periférico pensado para contagem de longos tempos e uma operação eficiente.

Desta forma, é comum trabalhar diretamente manipulando os ticks do timer, pois cada tick representa uma unidade de tempo baseada na frequência do clock selecionado. Para controlar o tempo de operação do LPTIM, você deve configurar o número de ticks que ele deve contar até gerar um evento (como uma interrupção ou mudança de estado no PWM).

Por exemplo, se o LPTIM estiver configurado para rodar com uma fonte de 32.768 kHz (LSE) e você definir 32.768 ticks, o timer contará exatamente 1 segundo antes de disparar o evento. Se precisar de tempos maiores, basta multiplicar a quantidade de ticks.

Esse método direto de manipular ticks dá ao projetista controle preciso sobre o tempo, mesmo em condições de baixo consumo, onde as fontes de clock são mais lentas e o consumo de energia é crítico.

Além disso, essa abordagem é essencial porque no modo de baixo consumo o microcontrolador pode estar desligado ou com clocks principais desabilitados, e o LPTIM permanece ativo contando ticks da sua fonte de clock de baixa frequência.

Portanto, para aproveitar ao máximo o LPTIM, é fundamental entender e trabalhar com a noção de ticks, o que permite ajustar o temporizador para os tempos exatos desejados, otimizando a duração da operação e o consumo de energia do sistema.

### Gerando PWM com LPTIM

Após a configuração do timer, apenas habilite o funcionamento do LPTIM. Ressalto que o LPTIM não possui múltiplos canais para geração do PWM, portanto não é necessário

```C
int main(void){

    // Bloco de inicialização padrão do CUBE MX
    // User code
    HAL_LPTIM_PWM_Start(&hlptim1, 1000, 500); // Condigurando um PWM de 1000 ticks e 50% de duty
    // End user code
    while(1){

    }
}
```

### Contagem usando LPTIM

Esta função funcionará de forma semelhante à `PeriodeElaspsedCalback` do timer convencional.

```C

// User Code
void HAL_LPTIM_CompareMatchCallback(LPTIM_HandleTypedef *hlptim){
    if(hlptim->Instance == LPTIM1){

    }
}
// End user code

int main(void){

    // Bloco de inicialização padrão do CUBE MX
    // User code
    HAL_LPTIM_TimeOut_Start_IT(&hlptim1, 1000); // Habilitando uma interrupção para 1000 ticks
    // End user code

    while(1){

    }
}

```

### Input capture usando LPTIM

Aqui a chamada da função e sua configuração não diferem da configuração do timer padrão. Aqui é relevante definir o channel.

```C
// User Code
void HAL_LPTIM_IC_CaptureCallback(LPTIM_HandleTypedef *hlptim){
    if(hlptim->Instance == LPTIM1){
        uint32_t capture = HAL_LPTIM_IC_GetCapture(&hlptim1, LPTIM_CHANNEL_1);
    }
}
// End user code

int main(void){

    // Bloco de inicialização padrão do CUBE MX
    // User code
    HAL_LPTIM_IC_Start_IT(&hlptim1, LPTIM_CHANNEL_1);
    // End user code

    while(1){

    }
}

```


