<div align="center">
    <h2>Projeto display LCD</h2>
    <img src="./images/display lcd/display_lcd.webp" alt="display_LCD.png" width="400" height="200">
</div>

Trabalhar com displays LCDs é relativamente facil, a única coisa que nos devemos preocupar de fato, é com sua inicialização, pois, dependendo do display, e da forma como você o inicializa, isso pode ocasionar em problemas.

Ao todo o display possui 16 pinos, cada um deles, é responsável por realizar uma tarefa, atente-se ao pino 03, este é responsável por regular o contraste do que esta sendo exibido no display LCD, ligamos este pino a um `trimpot`, não há bem um valor definido, o valor é regulado no momento de teste.

<div align="center">

| PINO | NOME | FUNÇÃO                 |
| :--: | :--: | ---------------------- |
|  01  | GND  | ALIMENTAÇÃO NEGATIVA   |
|  02  | VCC  | ALIMENTAÇÃO POSITIVA   |
|  03  |  V0  | REGULADOR DE CONTRASTE |
|  04  |  RS  | REGISTRO / SELETOR     |
|  05  | R/W  | LER / ESCRITA          |
|  06  |  E   | HABILITA               |
|  07  |  D0  | PINO DE COMUNICAÇÃO    |
|  08  |  D1  | PINO DE COMUNICAÇÃO    |
|  09  |  D2  | PINO DE COMUNICAÇÃO    |
|  10  |  D3  | PINO DE COMUNICAÇÃO    |
|  11  |  D4  | PINO DE COMUNICAÇÃO    |
|  12  |  D5  | PINO DE COMUNICAÇÃO    |
|  13  |  D6  | PINO DE COMUNICAÇÃO    |
|  14  |  D7  | PINO DE COMUNICAÇÃO    |
|  15  |  A   | ANODO LED DE FUNDO     |
|  16  |  K   | CATODO LED DE FUNDO    |

</div>

Internamente o display LCD possui um microcontrolador responsável por manipula-lo, o que iremos fazer é enviar informações em código hexadecimal para este display interpretar e desenhar a informação na tela.

Começaremos nosso código criando uma forma de interpretarmos o que iremos enviar para nosso display, para isso criaremos uma mascara de bits, lembrando que a informação que enviaremos serão nos pinos de comunicação.

```C
typedef struct {
	unsigned P0 : 1;
	unsigned P1 : 1;
	unsigned P2 : 1;
	unsigned P3 : 1;
	unsigned P4 : 1;
	unsigned P5 : 1;
	unsigned P6 : 1;
	unsigned P7 : 1;
} data_port;

data_port PORT;
```

Criaremos assim uma função intitulada `Info_manager` que irá gerenciar as informações que passamos para nosso display, ela receberá dois parametros.

- `data` sendo nosso código hexadecimal.
- `rs` sendo nosso seletor de modo.

A porta RS possui dois estados, enviando um sinal para o microcontrolador interno do LCD ele interpretará essa porta como uma instrução para ele, desta forma podemos selecionar entre dois estados, `utilizaremos 0` para quando a informação (data) enviada é um comando, por exemplo, limpar a tela, `utilizaremos o 1` para quando a informação enviada é um valor que queremos que seja exibido na tela.

```C
void Info_manager(unsigned data, unsigned rs) {
    // Filtro de informação
    PORT.P0 = (data >> 0) & 1;
    PORT.P1 = (data >> 1) & 1;
    PORT.P2 = (data >> 2) & 1;
    PORT.P3 = (data >> 3) & 1;
    PORT.P4 = (data >> 4) & 1;
    PORT.P5 = (data >> 5) & 1;
    PORT.P6 = (data >> 6) & 1;
    PORT.P7 = (data >> 7) & 1;

    // Chave seletora para modo de operação
    if (rs) {
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin,GPIO_PIN_RESET);
    }

    // Selecionado modo de leitura
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin,GPIO_PIN_RESET);

    // Interpretando informação hexadecimal para o barramento
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, port.P0);
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, port.P1);
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, port.P2);
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, port.P3);
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, port.P4);
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, port.P5);
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, port.P6);
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, port.P7);

    // Passando informações do barramento para o microcontrolador interno
    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
}
```

Agora precisamos criar uma função para a inicialização do nosso display LCD, todo display LCD precisa dessa inicialização para que ele possa se preparar para interpretar cada informação passada para ele, em nosso caso estamos utilizando uma comunicação com 8 pinos, mas você poderia fazer isso utiliziando 4 pinos, iremos utilizar um display 16x2 mas você pode usar um 20x4.

De fato não importa o que você está utilizando, ou a forma como você o utiliza, o que irá mudar é a inicialização, e apenas isso. Vamos criar uma função chamada `Start` que não vai receber nenhum parametro. Há a necessidade de repetir a informação três vezes no inicio para que haja a garantia que ela foi transmitida.

```C
void Start(void){
    HAL_Delay(40);
    // Comunicação de 8 pinos no barramento
    Info_manager(0x30, 0);
    Info_manager(0x30, 0);

    Info_manager(0x38, 0);

    // Desabilitando o cursor no modo piscante
    Info_manager(0x0C, 0);

    // Fazendo com que ele se desloque para a direita quando
    // uma informação nova é introduzida
    Info_manager(0x06, 0);

    // Limpando a tela do display
    Info_manager(0x01, 0);
}
```

Para que o display consiga interpretar as informações de inicialização é necessário que ele receba as informações, exatamente nessa ordem. Por fim precisamos apenas ter um interpretador de strings, e desta forma conseguimos passar mensagens para nosso display, criaremos então uma nova função chamada `Mensage` que receberá de parametro uma variável do tipo ponteiro do tipo char.

```C
void Mensage(char *mensage){
    for (int i = 0; mensage[i] != '\0'; ++i){
        Info_manager(mensage[i], 1); // Solicitando que o caractere seja escrito
    }
}
```

Por fim, basta chamar esta função `Mensage` no loop infinito principal que a mensagem será exibida na tela do LCD.

```C
int main(void){
    while(1){
        Mensage("Hello world!");

        // Fazendo com que o cursor volte para a casa inicial
        Info_manager(0x80, 0);
    }
}
```

---

<div align="center">
    Código alternativo para caso a inicialização seja feito utilizando apenas 4 pinos no barramento.
</div>

<br><br>

Neste caso é necessário atentar-se que tanto o pino 7 e o pino 0 de comunicação são MSB e LSB respectivamente, por isso como estamos apenas utilizando 4 pinos para comunicação, primeiro enviaremos os bits mais significativos pelo barramento, e depois enviaremos os menos significativos.

```C
void Info_manager(unsigned data, unsigned rs) {
    // Filtro de informação
    PORT.P0 = (data >> 0) & 1;
    PORT.P1 = (data >> 1) & 1;
    PORT.P2 = (data >> 2) & 1;
    PORT.P3 = (data >> 3) & 1;
    PORT.P4 = (data >> 4) & 1;
    PORT.P5 = (data >> 5) & 1;
    PORT.P6 = (data >> 6) & 1;
    PORT.P7 = (data >> 7) & 1;

    // Chave seletora para modo de operação
    if (rs) {
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin,GPIO_PIN_RESET);
    }

    // Selecionado modo de leitura
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin,GPIO_PIN_RESET);

    // Interpretando informação hexadecimal para o barramento
    HAL_GPIO_WritePin(D4_GPIO_Port, GPIO_Pin, port.P4);
    HAL_GPIO_WritePin(D5_GPIO_Port, GPIO_Pin, port.P5);
    HAL_GPIO_WritePin(D6_GPIO_Port, GPIO_Pin, port.P6);
    HAL_GPIO_WritePin(D7_GPIO_Port, GPIO_Pin, port.P7);

    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(D4_GPIO_Port, GPIO_Pin, port.P0);
    HAL_GPIO_WritePin(D5_GPIO_Port, GPIO_Pin, port.P1);
    HAL_GPIO_WritePin(D6_GPIO_Port, GPIO_Pin, port.P2);
    HAL_GPIO_WritePin(D7_GPIO_Port, GPIO_Pin, port.P3);

    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
}

void Start(void){
    HAL_Delay(40);
    // Modo 4 bits - Enviar primeiro o comando 0x33 e depois 0x32
    Info_manager(0x33, 0);  
    Info_manager(0x32, 0);  

    Info_manager(0x28, 0);

    Info_manager(0x0C, 0);
    Info_manager(0x06, 0);
    Info_manager(0x01, 0);

    HAL_Delay(2);
}
```
