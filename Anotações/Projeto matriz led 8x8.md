<div align="center">
    <h2>Projeto matriz de led 8x8</h2>
    <img src="./images/matriz 8x8/matriz_8x8.png" alt="Matriz8x8.png" width="200" height="200">
</div>

Para realizar o desenho nesta matriz é necessário realizar uma multplexação entre seus pinos de contato, ao todo essa matriz possui 24 pinos, possuindo 12 pinos a direita, e 12 pinos a esquerda, sendo divididos de grupos de 3x3.

<div align="center">
<p>Cada grupo possui:</p>
<ul>
  <p>Um pino <strong>seletor</strong>, ativo em <strong>alto</strong>.</p>
  <p>Dois pinos de cores (<span style="color:red;">vermelho</span> e <span style="color:green;">verde</span>) ativos em <strong>alto</strong>.</p>
</ul>

| PINO |                FUNÇÃO                | SENTIDO  |
| :--: | :----------------------------------: | :------: |
|  01  |               SELETOR                | DIREITA  |
|  02  |  <span style="color:red">COR</span>  |    --    |
|  03  | <span style="color:green">COR</span> |    --    |
|  04  |               SELETOR                |    --    |
|  05  |  <span style="color:red">COR</span>  |    --    |
|  06  | <span style="color:green">COR</span> |    --    |
|  07  |               SELETOR                |    --    |
|  08  |  <span style="color:red">COR</span>  |    --    |
|  09  | <span style="color:green">COR</span> |    --    |
|  10  |               SELETOR                |    --    |
|  11  |  <span style="color:red">COR</span>  |    --    |
|  12  | <span style="color:green">COR</span> |    --    |
|  13  |               SELETOR                | ESQUERDA |
|  14  |  <span style="color:red">COR</span>  |    --    |
|  15  | <span style="color:green">COR</span> |    --    |
|  16  |               SELETOR                |    --    |
|  17  |  <span style="color:red">COR</span>  |    --    |
|  18  | <span style="color:green">COR</span> |    --    |
|  19  |               SELETOR                |    --    |
|  20  |  <span style="color:red">COR</span>  |    --    |
|  21  | <span style="color:green">COR</span> |    --    |
|  22  |               SELETOR                |    --    |
|  23  |  <span style="color:red">COR</span>  |    --    |
|  24  | <span style="color:green">COR</span> |    --    |

</div>

Temos então 8 pinos seletores, e 16 pinos para cores, onde 8 são para colunas com a cor vermelha e 8 são para colunas com a cor verde. A forma que é realizada a leitrua da coluna respectiva é selecionando um pino de cor correspondente aquele mapeamento, quando o pino de cor for ativo, o pixel da linha atual e da coluna que foi ativa será aceso. Contudo uma coluna pode possuir duas cores, vermelho e verde, a seleção funciona da mesma forma para ambas.

Desenvolvi duas funções, cada uma delas responsável por cuidar de uma parte respectiva, a primeira realiza a leitura de cada linha da matriz, ou seja, ela percorre cada pino seletor, a segunda realiza a leitrua da coluna.

Filtro de comunicação de 8 bits com a matriz 8x8 é necessário, a comunicação com minhas funções é com base em código hexadecimal, para que eu possa criar os desenhos eu utilizo um mapeamento em uma plhanilia do excel, e essa planilha me retorna o valor binário / hexadecimal, com o valor obitido eu consigo passar para minha função.

<div align="center">
    <img src="./images/matriz 8x8/matriz_8x8_mapeamento.png" alt="Matriz8x8.png" width="500" height="300">
</div>

Primeiro precisamos criar um jeito de interpretar cada informação binária passada para cada linha percorrida, para isso usamos o método de mascara de bits.

```C
// INIT
typedef struct PIN{
	unsigned P0: 1,
			 P1: 1,
			 P2: 1,
			 P3: 1,
			 P4: 1,
			 P5: 1,
			 P6: 1,
			 P7: 1;
}filter;

// VARIÁVEL PARA MASCARA
filter PORT

// DENTRO DA FUNÇÃO
PORT.P0 = (valorX >> 0) & 1;
PORT.P1 = (valorX >> 1) & 1;
PORT.P2 = (valorX >> 2) & 1;
PORT.P3 = (valorX >> 3) & 1;
PORT.P4 = (valorX >> 4) & 1;
PORT.P5 = (valorX >> 5) & 1;
PORT.P6 = (valorX >> 6) & 1;
PORT.P7 = (valorX >> 7) & 1;


HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, PORT.P0);
HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, PORT.P1);
HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, PORT.P2);
HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, PORT.P3);
HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, PORT.P4);
HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, PORT.P5);
HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, PORT.P6);
HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, PORT.P7);

```

`valorX` é uma variável onde passamos como parametro para dentro da função, esse parametro será o valor hexadecimal. Com isso podemos ate nos aventurar a criação de animações, a única coisa que precisamos nos preocupar é em relação a duração de cada imagem. Por isso criamos uma nova função que tem como papel manter ativo a animação durante um período de tempo. Intitulei esta função de `Draw_disp`.

```C
void Draw_disp(char frame){
    for (int i = DFRAME; i >= 0; i--){
        Animations(frame, 0);
    }
}
```

Ao chamar uma outra função `Animations` passando como parametro o valor do `frame` onde dizemos para ela qual frame será exibido agora.

```C
void Animations(char select){
	switch(select){
        case '1':
			Seletor_Line(0x80);        // Navegação das linhas
            Seletor_Column(0x7E);      // Informando colunas

			Seletor_Line(0x40);        // Navegação das linhas
			Seletor_Column(0xBD);      // Informando colunas

			Seletor_Line(0x20);        // Navegação das linhas
			Seletor_Column(0xDB);      // Informando colunas

			Seletor_Line(0x10);        // Navegação das linhas
			Seletor_Column(0xE7);      // Informando colunas

			Seletor_Line(0x08);        // Navegação das linhas
			Seletor_Column(0xE7);      // Informando colunas

			Seletor_Line(0x04);        // Navegação das linhas
			Seletor_Column(0xDB);      // Informando colunas

			Seletor_Line(0x02);        // Navegação das linhas
			Seletor_Column(0xBD);      // Informando colunas

			Seletor_Line(0x01);        // Navegação das linhas
			Seletor_Column(0x7E);      // Informando colunas
            break;

        case '2':
            Seletor_Line(0x01);        // Navegação das linhas
            Seletor_Column(0xFF);      // Informando colunas

            Seletor_Line(0x02);        // Navegação das linhas
            Seletor_Column(0x99);      // Informando colunas

            Seletor_Line(0x04);        // Navegação das linhas
            Seletor_Column(0x00);      // Informando colunas

            Seletor_Line(0x08);        // Navegação das linhas
            Seletor_Column(0x00);      // Informando colunas

            Seletor_Line(0x10);        // Navegação das linhas
            Seletor_Column(0x81);      // Informando colunas

            Seletor_Line(0x20);        // Navegação das linhas
            Seletor_Column(0xC3);      // Informando colunas

            Seletor_Line(0x40);        // Navegação das linhas
            Seletor_Column(0xE7);      // Informando colunas

            Seletor_Line(0x80);        // Navegação das linhas
            Seletor_Column(0xFF);      // Informando colunas
            break;
    }
}
```

Por fim para utilizar esta função, basta apenas chamar `Draw_disp` para que os desenhos sejam feitos.

```C
int main(void){
    while(1){
        Draw_disp('1');
		Draw_disp('2');
    }
}
```
