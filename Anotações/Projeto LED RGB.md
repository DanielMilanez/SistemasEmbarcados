<div align="center">
    <h2>Projeto LED RGB controlado por PWM</h2>
    <img src="./images/led rgb pwm/led_rgb.png" alt="led_rgb.png" width="200" height="200">

    Para que possamos trabalhar com este LED RGB primeiro precisamos indetificar se ele é cátodo comum ou anodo comum.

</div>

<div align="center">
    <img src="./images/led rgb pwm/demonstrativo_catodo_anodo.png" alt="demonstrativo.png" width="400" height="200">
</div>

Quando nos referenciamos a um led catodo comum estamos dizendo que seus pinos de cores são ativos em `baixo`, quando dizemos que ele é um anodo comum significa que seus pinos de cores são ativos em `alto`. Em nosso caso estamos utilizando um LED catodo comum, o que singifica que nossa lógica de ativação do mesmo será invertida.

Começamos nosso código primeiro definindo duas macros de pre-processamento, constantes simbolicas.

```C
#define ON 0     // Para que possamos ligar o led precisamos desligar o pino
#define OFF 200  // Lógica invertida.
#define DELAY 5  // Tempo para troca suave
```

Nosso objetivo é reproduzir um passeio de cores, fazendo com que o led, altere gradativamente de tom para tom, para isso iremos usar bastante o laço de repetição `while`.

Primeira coisa que iremos fazer é zerar os valore de duty cicle dos nossos registradores, como estamos trabalhando com 3, canais RGB, respectivamente, é importante inicializalos em seu estado desligado para que não haja erros.

```C
int main(void){
    // Inicio das funções de timer
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

    // Zerando valor de duty diretamente com o registrador
    TIM2 -> CCR1 = OFF;
    TIM2 -> CCR2 = OFF;
    TIM2 -> CCR3 = OFF;
}
```

Em seguida precisamos ligar lentamente a cor vermelha, ela estará fora do loop infito para que não haja repetição de código.

```C
int main(void){
    /*Configurações iniciais de inicialzação do timer*/

    // Ligando cor vermelha
        while (dcRed != ON){
            dcRed--;
            TIM2 -> CCR1 = dcRed;
            HAL_Delay(DELAY);
        }
}
```

Agora precisamos realizar nosso passeio entre as cores, para isso vamos usar uma lógica simples, primeiro incrementamos uma cor e reduzimos outra em simultaneo, desta forma, criaremos uma variação suave.

```C
/*INICIALIZAÇÃO*/

 while (1) {
        // Ligando cor verde, desligando lentamente o vermelho
        while (dcGreen != ON){
            dcGreen--;
            dcRed++;
            TIM2->CCR1 = dcRed;
            TIM2->CCR2 = dcGreen;
            HAL_Delay(DELAY);
	    }

        // Ligando cor azul, desligando lentamente o verde
        while (dcBlue != ON){
            dcBlue--;
            dcGreen++;
            TIM2->CCR2 = dcGreen;
            TIM22->CCR1 = dcBlue;
            HAL_Delay(DELAY_TIME);
	    }

        // Desligando o azul, ligando lentamente o vermelho
        while (dcBlue != OFF){
            dcBlue++;
            dcRed--;
            TIM2->CCR1 = dcRed;
            TIM22->CCR1 = dcBlue;
            HAL_Delay(DELAY_TIME);
	    }
    }
```
