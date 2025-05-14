<div align="center">
    <h2>Projeto Multplex Teclado</h2>
    <img src="./images/multplex teclado/teclado3x4.png" alt="teclado3x4.png" width="200" height="200">
</div>

A multplexação é um método pelo qual múltiplos sinais, analógicos ou digitais, são combinados em um sinal por meio compartilhado, um barramento, para que possamos realizar a leitura de nosso teclado precisamos realizar uma varredura pelas suas colunas, e realizar a verificação de qual botão respectivo a aquela coluna, usando como base a linha está sendo precionado.

Vá para coluna 1
- Verifique linha 1
- Verifique linha 2
- Verifique linha 3
- Verifique linha 4

Vá para coluna 2
- Verifique linha 1
- Verifique linha 2
- Verifique linha 3
- Verifique linha 4

Vá para coluna 4
- Verifique linha 1
- Verifique linha 2
- Verifique linha 3
- Verifique linha 4

Desta forma conseguimos realizar a varredura de todos os botões presentes no nosso teclado, por fim enviamos nossas informações e valores atuais para uma matriz que atualizará nossa resposta, em uma variável em nosso código, a partir disto nossa resposta será interpretada e uma função poderá ser executada.

Nosso valor de verificação de botão precionado está configurado para pull-up então precisamos enviar sinal baixo para selecionar uma coluna especifica.

```C
// Matriz para teclado
char tmap[4][3] =  {{'1', '2', '3'},
					{'4', '5', '6'},
					{'7', '8', '9'},
					{'*', '0', '#'}};

// Variável resposta
char    response = '\0';

// Variável para navegação
uint8_t atualColumn = 0;

void Keyboard_check(void){
    switch(atualColumn){
		case 0:
            // Ativando coluna 1
			HAL_GPIO_WritePin(COLUM_01_GPIO_Port, COLUM_01_Pin, 0);
			HAL_GPIO_WritePin(COLUM_02_GPIO_Port, COLUM_02_Pin, 1);
			HAL_GPIO_WritePin(COLUM_03_GPIO_Port, COLUM_03_Pin, 1);

            // Verificando se algum botão foi precionado
			Verify_press();

            // Atualizando valor da coluna atual
			atualColumn = 1;
			break;

		case 1:
            // Ativando coluna 2
			HAL_GPIO_WritePin(COLUM_01_GPIO_Port, COLUM_01_Pin, 1);
			HAL_GPIO_WritePin(COLUM_02_GPIO_Port, COLUM_02_Pin, 0);
			HAL_GPIO_WritePin(COLUM_03_GPIO_Port, COLUM_03_Pin, 1);

            // Verificando se algum botão foi precionado
			Verify_press();

            // Atualizando valor da coluna atual
			atualColumn = 2;
			break;

		case 2:
            // Ativando coluna 3
			HAL_GPIO_WritePin(COLUM_01_GPIO_Port, COLUM_01_Pin, 1);
			HAL_GPIO_WritePin(COLUM_02_GPIO_Port, COLUM_02_Pin, 1);
			HAL_GPIO_WritePin(COLUM_03_GPIO_Port, COLUM_03_Pin, 0);

            // Verificando se algum botão foi precionado
			Verify_press();

            // Atualizando valor da coluna atual
			atualColumn = 0;
			break;
	}
}

void Verify_press(void){
    uint16_t btnLine01 =  HAL_GPIO_ReadPin(LINE_01_GPIO_Port, LINE_01_Pin),
             btnLine02 =  HAL_GPIO_ReadPin(LINE_02_GPIO_Port, LINE_02_Pin),
             btnLine03 =  HAL_GPIO_ReadPin(LINE_03_GPIO_Port, LINE_03_Pin),
             btnLine04 =  HAL_GPIO_ReadPin(LINE_04_GPIO_Port, LINE_04_Pin);

    if (!btnLine01) response = tmap[0][atualColumn];
    if (!btnLine02) response = tmap[1][atualColumn];
    if (!btnLine03) response = tmap[2][atualColumn];
    if (!btnLine04) response = tmap[3][atualColumn];
}

```

Mesmo em teclados de membrana, é recomendável implementar técnicas de debounce para garantir leituras precisas e confiáveis, no entando não vi necessidade para esta aplicação, fique livre para implementar o tratamento de debouce da forma que quiser.