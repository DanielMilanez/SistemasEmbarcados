<div align="center">
    <h2>Geração de ondas usando DAC</h2>
</div>

Iremos realizar a geração de sinais usando o recurso DAC (Conversor Digital Analogico) no microcontrolador STM32L053R8 (Também valido para L052K8T6). Mas antes, precisamos ter de prontidão um osciloscópio para que consigamos vizualizar os sinais gerados pela saida do microcontrolador.

Neste material iremos criar três formas de onda.
- Rampa de tensão
- Dente de serra
- Onda triangular
- Sinal senoidal 

Atente-se as configurações do ***clock interno*** e também configurações do timer que estaremos utilizando para cada um dos exemplos. 


### Rampa de tensão 

Uma rampa de tensão é um valor crescente e que possui uma mudança abrupta quando chega em seu valor máximo. O STM32 consegue com apenas um único canal de DAC, consegue apenas gerar uma única onda por vez, essa onda que é gerada possui suas próprias limitações, tendo seu valor máximo e minimo de 0V a 3.3V.

Nosso objetivo é gerar uma rampa de tensão que vá de 0V ate 3V, utilizaremos o timer configurado de tal forma que gere nossa rampa de tensão a uma frequência de 100Hz.

Para que possamos configurar o valor adequado para a operação de nosso DAC, primeiro precisamos calcular o valor que desejamos alcancar de ARR. 

- CLK = 8Mhz
- f   = 100Hz
- PSC = 8

Considere também a variável Cp, que significa clocks pulsados. Essa variável ficará sendo responsavel pelo incremento do DAC. E como utilizaremos um timer para realizar a chamada do DAC não podemos considerar apenas uma única conversão, mas sim uma taxa de amostragem respectiva a essa conversão, o Cp é nossa taxa de amostragem, ele está diretamente relacionado com nossa taxa de amostragem.

Como queremos fazer uma rampa de tensão, precisamos incrementar este valor positivamente ate atingir o limite que desejamos. Em nosso caso é 3V, com uma regra de 3 simples você consegue descobrir o valor hexadecimal de qualquer outro valor de tensão, basta saber a resolução usada, em nosso caso vamos usar 8bits.

Cp  = 232 (valor equivalente para 3V)

Queremos descobrir nosso valor de ARR e para isso usamos a relação dos nossos parametros conhecidos.

$$
ARR = \frac{CLK}{PSC\cdot F \cdot C_p} 
$$

$$
ARR = \frac{8\,\text{MHz}}{8 \cdot 100 \cdot 232} \approx 43
$$

Descbrimos assim o valor que necessitamos para nosso ARR é 43. Agora o que precisamos fazer, é chamar a função `HAL_TIM_PeriodElapsedCallback` e nela incrementar-mos o valor do nosso Cp.

```C
    uint8_t Cp = 0;

    void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, modulate);

        if (Cp >= 232) Cp = 0; // Limitando Cp para o valor de 3V
        else Cp++;
    }
```

Realize as inicializações devidas tanto o timer que foi configurado para o modo de interrupção `HAL_TIM_Base_Start_IT(&htim)` e lembre-se de inicializar também o DAC `HAL_DAC_Start(&hdac, DAC_CHANEL_1)`.

<div align="center">
    <h3>Sinal gerado:</h3>
    <img src="./images/gerar ondas/Rampa de tensão.png" alt="Matriz8x8.png" width="300" height="200"> 
</div>

### Dente de serra

O processo para reproduzir o formato de onda dente de serra é apenas inverter os valor, ao invés de incrementar ele deverá ser decrementado.

```C
    uint8_t Cp = 232;
    void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, modulate);

        if (Cp <= 0) Cp = 232; // Limitando Cp para o valor de 0V
        else Cp--;
    }
```
<div align="center">
    <h3>Sinal gerado:</h3>
    <img src="./images/gerar ondas/Dente de serra.png" alt="Matriz8x8.png" width="300" height="200"> 
</div>

### Onda Triangular

Considere um sinal de onda com um 1Vpp com uma frequencia de 500mHz partindo de 1V e indo a 2V.

Para gerar-mos essa forma de onda, podemos realizar de duas formas, a primeira é incrementar o valor, ate que cheguemos em uma flag, e depois decrementarmos o valor ate chegar no original, e abaixarmos a flag. Mas ele é um pouco mais trabalhoso para modificar o sinal como bem entendemos.

Cp = 155 (Correspondente a 2V) 

$$
ARR = \frac{CLK}{PSC\cdot F \cdot C_p} 
$$

$$
ARR = \frac{8\,\text{MHz}}{8 \cdot 0.5 \cdot 155} \approx 12903
$$

E para gerarmos nosso OFFSET basta limitarmos a contagem do valor com nossa flag, que ele automaticamente irá se corrigir. Como desejamos um valor de tensão de 1Vpp partindo de 1V e indo ate 2V colocamos no range maximo o valor do Vpmax e o valor do Vpmin para o valor minimo aceito.

```C
    uint8_t Cp = 0, flag = 0;

    void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, modulate);

        if (!flag) Cp++;
        else Cp--;

        if (Cp >= 155) flag = 1;
        else if (Cp <= 75) flag = 0;
    }
```
<div align="center">
    <h3>Sinal gerado:</h3>
    <img src="./images/gerar ondas/Onda Triangular sem DMA.png" alt="Matriz8x8.png" width="500" height="300"> 
</div>

#### Usando DMA para criar o sinal triangular

Altere as configurações do timer para estar de acordo com 500mHz, não se preocupe com o calculo que utilizamos anteriormente, quando estavamos configurando a rampa de tensão e o dente de serra, aqui isso não é mais necessário. Mas atente-se de habilitar a opção `Update event` no timer, e selecionar a opção `Trigger TIM6` no DAC. Habilite o DMA do DAC no modo circular com as configurações padrões. 

Configure o timer para 500Hz isso gerará o valor que precisamos, vamos agora usar um range maior do que estavamos utilizando anteriormente.

```C
    #define SIZE   1000 // Utilizando 1000 pontos de amostragem
    #define OFFSET 1241
    #define Cp     1241 / 500 // 1241: Valor respectivo a 1V para 12 Bits | 500: Frequencia utilizada

    uint16_t TriangularSine[SIZE];

    HAL_TIM_Base_Start(&htim6);
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *) TriangularSine, SIZE, DAC_ALIGN_12B_R);

    // Percorre a borda de subida
    for (int i = 0; i < SIZE; ++i) TriangularSine[i] = i * Cp + OFFSET;

    // Percorre a borda de descida
    for (int i = 500, j = 500; i < 1000; ++i, --j) TriangularSine[i] = j * Cp + OFFSET;

```

<div align="center">
    <h3>Sinal gerado:</h3>
    <img src="./images/gerar ondas/Onda Triangular com DMA.png" alt="Matriz8x8.png" width="500" height="300"> 
</div>

### Onda Senoidal

Suponha uma onda senoidal com 2Vpp; com um OFFSET de 1V; e com uma frequencia de 10Hz

Agora, neste exemplo precisamos da biblioteca `math.h` para que consigamos realizar o calculo da senoide Adequadamente.

- i = Ponto de amostragem atual, este será o valor que usaremos para percorrer nosso laço de repetição
- res = Resolução de nossa senoide, nela iremos controlar a amplitude do nosso sinal.
- OFFSET = Forma que podemos escurcionar o sinal.

OBS.: O valor resultante nunca poderá ultrapassar o range maximo permitido!

$$
F = \frac{\text{FreqTime}}{C_p}
$$


$$
Sine = \left( \sin(2\pi i) + 1 \right) \cdot (\frac{\text{res} + 1}{2}) + \text{OFFSET}
$$


```C
    #include <math.h>

    #define SIZE 100
    #define PI 3.141593
    #define RES 2482 // Valor equivalente a 2Vpp

    uint16_t TriangularSine[SIZE];

    HAL_TIM_Base_Start(&htim6);
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *) SINE, TriangularSine, DAC_ALIGN_12B_R);

    // Sinal senoidal
    for (int i = 0; i < SIZE; ++i) TriangularSine[i] = (sin((2 * PI / SIZE) * i) + 1) * ((RES + 1) / 2) + OFFSET;

```


<div align="center">
    <h3>Sinal gerado:</h3>
    <img src="./images/gerar ondas/Onda senoidal.png" alt="Matriz8x8.png" width="500" height="300"> 
</div>