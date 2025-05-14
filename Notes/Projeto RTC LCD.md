<div align="center">
    <h2>Projeto RTC com LCD</h2>
    <img src="./images/display lcd/display_lcd.webp" alt="display_LCD.png" width="400" height="200">
</div>

## Config

Para a realização deste projeto precisamos nos lembrar de conceitos anteriores, como o `teclado matricial` e o `display LCD` com a configuração de 4 bits no barramento. Em seguida precisamos realizar as configurações necessárias em nosso STM32 Cube IDE.

Primeiro, ative o RCC para que consigamos utilizar o cristal ressonante de *32.742Hz* que está presente na placa, selecione a opção *Crystal/Ceramic Resonator* em `Low Speed Clock (LSE)`

Em seguida ative o timer respectivo ao *RTC*. Habilite a opção `Actvate clock source` e `Actvate calendar`. Em sua árvore de clock selecione a opção LSE para que o RTC fique configurado com o clock gerado pelo cristal. Gere o código.

## Código

Para nossa lógica precisamos nos habituar com alguns conceitos novos, provenientes do RTC (Real Time Clock) algumas funções serão bastante utilizadas, assim como alguns `typedef's` oriundos da biblioteca HAL.

Começe o código inicializando algumas variáveis.

```C
    bitPort PORT; // variável para o barramento de 4 bits
    RTC_TimeTypeDef atualTime; // variável para o tempo atual.
    RTC_DataTypeDef atualDate; // variável para a data atual

    uint8_t atualColumn = 0, atualMenu = 1, flag = 0, atualPos = 0, ctr = 0, x = 0;
    uint32_t day, month, year, seconds, minutes, hours;
    uint32_t timeBounce = 0, brefTime = 0, pause = 0;

    char keyResponse = '\0';
    char KeyMap[4][3] = {{'1', '2', '3'},
                        {'4', '5', '6'},
                        {'7', '8', '9'},
                        {'*', '0', '#'}};

    char firstLine[25];  // Informação enviada para a primeira linha do LCD.
    char secondLine[25]; // Informação enviada para a segunda linha do LCD.
    char str_temp[5];    // String temporária para a verificação das variáveis.

```

Agora declare algumas funções que iremos utilizar, durante a explicação, vou me abster de comentários a respeito de funções já abordadas em outros documentos. Dexei marcado quais funções vou falar a respeito.

```C
    void Start_lcd(void);
    void Info_limit(void); // X
    void Menu_manager(void); // X
    void Verify_press(void);
    void Keyboard_check(void);
    void Altern_selection(void); // X
    void Message(char *message); 
    void Info_manager(unsigned data, unsigned rs);
    int Debounce(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin); // X
```

Primeiro vamos falar sobre a função `main`, em nossa funçao main, estamos definindo alguns parametros, e inicalizando algumas variáveis, primeiro começamos inicializando as variáveis de ***data atual*** acessando os parametros da struct que definimos. Setamos um horário e dia genericos para que possamos inicalizar nossa contagem a partir de algum lugar.

Em seguida utilizamos a função `HAL_RTC_SetDate` e `HAL_RTC_SetTime` para que possamos definir os valores que passamos para nossas structs como valores válidos salvos no registrador do RTC.

Dentro de nosso laço de repetição infinito, estamos chamado o `Menu_manager()` para configurar o que será exibido no menu atual, estamos também verificando se houve uma pausa na contagem. Caso haja, eu uso a variável `pause` para evitar receber informações constantes do nosso RTC através das funções `HAL_RTC_GetDate` e `HAL_RTC_GetTime`.

```C 
    int main(void) {
        atualDate.Date  = 1;
        atualDate.Month = 1;
        atualDate.Year  = 1;

        atualTime.Hours   = 0;
        atualTime.Minutes = 0;
        atualTime.Seconds = 0;

        if (HAL_RTC_SetDate(&hrtc, &atualDate, RTC_FORMAT_BIN) != HAL_OK) Error_Handler();
        if (HAL_RTC_SetTime(&hrtc, &atualTime, RTC_FORMAT_BIN) != HAL_OK) Error_Handler();

        Start_lcd();

        while (1){
            Menu_manager();
            Keyboard_check();

            if (!pause){
                HAL_RTC_GetDate(&hrtc, &atualDate, RTC_FORMAT_BIN);
                HAL_RTC_GetTime(&hrtc, &atualTime, RTC_FORMAT_BIN);
            }
        }
    }
```

Na função `Debounce`, nos a chamaremos de maneira indireta, ela é chamada pela função `Verify_press` que esta por sua vez, é chamada pela função `Keyboard_check`, a função *Debounce* recebe apenas dois parametros, o GPIO e o PIN respectivos. Interno nela ela verifica se o pino foi precionado por mais de 20ms, caso tenha sido, ele executa a função, e verifica novamente se o botão está sendo precionado, ele mantém o estado evitando multiplos apertos apenas segurando o botão, caso contrário, o botão não tenha sido precionado por pelo menos 20ms, ele não executa o código. 

```C
int Debouce(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
    uint8_t press = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
    uint8_t result = 0;

    if (!press){
        timeBounce = HAL_GetTick();

        if ((timeBounce - brefTime) > 20){
        	result = 1;
        }

        brefTime = timeBounce;
        while (!HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));
    }

    return result;
}

```

Função `Altern_selection`, ela é chamada de maneira indireta, desta vez, ela é chamada pela função `Menu_manager`, com esta função, verificamos nossa posição atual na tela, quando estamos no modo de edição de informações, e com essa posição, conseguimos salvar a informação correspondente ao trecho que estamos editando, em nossas variáveis temporais.

```C
    void Altern_selection(void){
        switch(id_char){
            case 0:
                Info_manager(0x88, 0); // Primeira coluna, da primeira linha, a ser editada DH (Decimal Horas)
                flag = 1;
                break;

            case 1:
                Info_manager(0x89, 0); // Segunda coluna, da primeira linha,  a ser editada UH (Unidade Horas)
                flag = 1;
                break;

            case 2:
                Info_manager(0x8B, 0); // Terceira coluna, da primeira linha,  a ser editada Dm
                flag = 1;
                break;

            case 3:
                Info_manager(0x8C, 0); // Quarta coluna, da primeira linha,  a ser editada Um
                flag = 1;
                break;

            case 4:
                Info_manager(0x8E, 0); // Quinta coluna, da primeira linha,  a ser editada Ds
                flag = 1;
                break;

            case 5:
                Info_manager(0x8F, 0); // Sexta coluna, da primeira linha,  a ser editada Us
                flag = 1;
                break;

            case 6:
                Info_manager(0xC4, 0); // Primeira coluna, da segunda linha, a ser editada DD (Dcimal Dia)
                flag = 1;
                break;

            case 7:
                Info_manager(0xC5, 0); // Segunda coluna, da segunda linha, a ser editada UD (Unidade Dia)
                flag = 1;
                break;

            case 8:
                Info_manager(0xC7, 0); // Terceira coluna, da segunda linha, a ser editada DM
                flag = 1;
                break;

            case 9:
                Info_manager(0xC8, 0); // Terceira coluna, da segunda linha, a ser editada UM
                flag = 1;
                break;

            case 10:
                Info_manager(0xCA, 0); // Quarta coluna, da segunda linha, a ser editada  DA
                flag = 1;
                break;

            case 11:
                Info_manager(0xCB, 0); // Quinta coluna, da segunda linha, a ser editada  UA
                flag = 1;
                break;

            default:
                Info_manager(0x88, 0); 
                id_char = 0;
                break;
        }
    }
```

Função `Info_limit`, está função é responsável por evitar que nossas incerções sejam indevidas, por exemplo, suponha que você deseja inserir informações em nosso relógio, na configuração hh:mm:ss entretanto você digita 36:89:79, isso que foi digitado não condiz com o que desejamos implementar, queremos apenas um calentário simples que exiba a hora atual e o dia atual inseridos pelo usuário, por isso precisamos de um limitador.

```C
    void Info_limit(void){
        switch(id_char){
            case 0:
                // Com base na resposta do teclado sobrescreva-o
                if (keyResponse >= '3') keyResponse = '2';
                break;

            case 1:
                // Com base na resposta do teclado e no valor passado sobrescreva-o
                if (keyResponse >= '4' && str_temp[0] == '2') keyResponse = '3';
                break;

            case 2:
            case 4:
                if (keyResponse >= '6') keyResponse = '5';
                break;

            case 6:
                if (keyResponse >= '4') keyResponse = '3';
                break;

            case 7:
                if (keyResponse >= '4' && str_temp[0] == '3') keyResponse = '0';
                break;

            case 8:
                if (keyResponse >= '2') keyResponse = '1';
                break;

            case 9:
                if (keyResponse >= '3' && str_temp[0] == '1') keyResponse = '2';
                break;
        }
    }
```

Função `Menu_manager`, essa função é o cerebro por de trás de tudo, nela temos desde a paginação de nossas telas, e gerenciamento de informações que estão sendo salvas / modificadas e exibidas na mesma. Primeiramente realizamos uma verificação para saber em qual menu estamos, depois precetamos o valor de horas, minutos e segundos em nossas respectivas variáveis, e em seguida pedimos para exibir esses valores em uma string que será enviada para a função `Message`, fazemos o mesmo para o dia, mês e ano.

Isso fizemos na primeira tela, na segunda, realizaremos a seguinte lógica, quando o usuário precionar o botão *"#"* os valores que estão pre-setados serão mantidos e enviados como valores estaticos para o novo menu, em seguida o usuário poderá navegar por esse menu com base na localização atual do cursor, e alterar os valores, esses valores alterados, são salvos no formato de string de tamanho dois, depois serão salvos em variáveis quando realizar-mos a conversão usando a função `atoi`.

Nossa variável `ctr` servirá como nosso controle de envio, onde ela verifica se os dois "slots" já foram preenchidos, quando isso ocorrer ela envia essas informações para a variável respectiva.

```C
    void Menu_manager(void){
        switch(atualMenu){
            case 1:
                hours   = atualTime.Hours;
                minutes = atualTime.Minutes;
                seconds = atualTime.Seconds;

                sprintf(firstLine, "TM: %02lu:%02lu:%02lu      ", hours, minutes, seconds);
                Info_manager(0x80, 0);
                Message(firstLine);

                day   = atualDate.Date;
                month = atualDate.Month;
                year  = atualDate.Year;

                sprintf(secondLine, "DT: %02lu/%02lu/%02lu     ", day, month, year);
                Info_manager(0xC0, 0);
                Message(secondLine);
                break;

            case 2:
                Altern_selection();
                if (keyResponse == '*') id_char++;

                if ((keyResponse != '\0')&& (keyResponse != '#') && (keyResponse != '*') && (flag)) {
                    Info_limit();
                    Info_manager(keyResponse, 1);
                    str_temp[ctr] = keyResponse;

                    id_char++;
                    ctr++;

                    flag = 0;
                }

                if (ctr == 2){
                    ctr = 0;
                    x = atoi(str_temp);
                }

                if (id_char == 2)  atualTime.Hours   = x;
                else if (id_char == 4)  atualTime.Minutes = x;
                else if (id_char == 6)  atualTime.Seconds = x;
                else if (id_char == 8)  atualDate.Date    = x;
                else if (id_char == 10) atualDate.Month   = x;
                else if (id_char == 0)  atualDate.Year    = x;

                if (HAL_RTC_SetTime(&hrtc, &atualTime, RTC_FORMAT_BIN)!= HAL_OK) Error_Handler();
                if (HAL_RTC_SetDate(&hrtc, &atualDate, RTC_FORMAT_BIN) != HAL_OK) Error_Handler();
                break;
            }

        if (keyResponse == '#') {
            Info_manager(0x01, 0);
            flag = 1;
            atualMenu++;
            if (atualMenu == 2) {
                pause = 1;
                sprintf(firstLine, "SET TM: %02lu:%02lu:%02lu", hours, minutes, seconds);
                sprintf(secondLine, "DT: %02lu/%02lu/%02lu", day, month, year);
            }
            else if (atualMenu >= 3){
                atualMenu = 1;
                pause = 0;
            }

            Message(firstLine);
            Info_manager(0xC0, 0);
            Message(secondLine);

            id_char = 0;
            x = 0;
        }
    }
```