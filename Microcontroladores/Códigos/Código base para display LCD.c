#include <stdio.h>
#include <stdbool.h>

#pragma region // Pinout config  
    unsigned DB0_GPIO_Port,
             DB1_GPIO_Port,
             DB2_GPIO_Port,
             DB3_GPIO_Port,
             DB4_GPIO_Port,
             DB5_GPIO_Port,
             DB6_GPIO_Port,
             DB7_GPIO_Port,

             CLOCK_GPIO_Port, // Enable pin
             RS_GPIO_Port,    // Data or instruct
             RW_GPIO_Port,    // Read or Write

             DB0_Pin,
             DB1_Pin,
             DB2_Pin,
             DB3_Pin,
             DB4_Pin,
             DB5_Pin,
             DB6_Pin,
             DB7_Pin,

             CLOCK_Pin; // Enable pin
             RS_Pin,    // Data or instruct
             RW_Pin;    // Read or Write

    #define GPIO_PIN_RESET 0
    #define GPIO_PIN_SET   1

#pragma endregion

// Bitfild para mascara do byte de informação
typedef struct datap {
	unsigned P0 : 1;
	unsigned P1 : 1;
	unsigned P2 : 1;
	unsigned P3 : 1;
	unsigned P4 : 1;
	unsigned P5 : 1;
	unsigned P6 : 1;
	unsigned P7 : 1;
} datap;

/*---------------------- DECLARAÇÕES ------------------------------*/
void Initialize_LCD(void);
void Mensage(char *atualString);
void Control_LCD (unsigned data, unsigned gate);

/*------------------------ FUNÇÕES --------------------------------*/

// Inicializador
void Initialize_LCD(void){
    /* Inicialização dos caracteres resolução 5x8 */
    Control_LCD(0x30, 0);
    Control_LCD(0x30, 0);
    Control_LCD(0x30, 0);

    /*Comunicação de 8bits disp de 2 ou mais linhas*/
    Control_LCD(0x38, 0);

    Control_LCD(0x0D, 0); // Liga o cursor no modo piscante 
    Control_LCD(0x06, 0); // Desloca o cursor para a direita quando um caracter é inserido
    Control_LCD(0x01, 0); // Limpa a tela do display e desloca o cursor
}


// Para mensagens
void Mensage(char *atual_string){
	for (int i = 0; atual_string[i] != '\0'; ++i){
		Controler_LCD(atual_string[i], 1);
	}
}

// Controle do LCD
void Control_LCD (unsigned data, unsigned gate) {
    datap port;

    // Filtro de informação
    port.P0 = (data >> 0) & 1;
    port.P1 = (data >> 1) & 1;
    port.P2 = (data >> 2) & 1;
    port.P3 = (data >> 3) & 1;
    port.P4 = (data >> 4) & 1;
    port.P5 = (data >> 5) & 1;
    port.P6 = (data >> 6) & 1;
    port.P7 = (data >> 7) & 1;

    // ----------------------------------------------------------- \\ 
    //                CODIGO FUNCIONAL APENAS NA IDE               \\ 
    // ----------------------------------------------------------- \\ 

    if (gate) {
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin,GPIO_PIN_RESET); 
    }

    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin,GPIO_PIN_RESET);

    HAL_GPIO_WritePin(DB0_GPIO_Port, DB0_Pin, port.P0);
    HAL_GPIO_WritePin(DB1_GPIO_Port, DB1_Pin, port.P1);
    HAL_GPIO_WritePin(DB2_GPIO_Port, DB2_Pin, port.P2);
    HAL_GPIO_WritePin(DB3_GPIO_Port, DB3_Pin, port.P3);
    HAL_GPIO_WritePin(DB4_GPIO_Port, DB4_Pin, port.P4);
    HAL_GPIO_WritePin(DB5_GPIO_Port, DB5_Pin, port.P5);
    HAL_GPIO_WritePin(DB6_GPIO_Port, DB6_Pin, port.P6);
    HAL_GPIO_WritePin(DB7_GPIO_Port, DB7_Pin, port.P7);

    HAL_Delay(1);
    HAL_GPIO_WritePin(CLOCK_GPIO_Port, CLOCK_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(CLOCK_GPIO_Port, CLOCK_Pin, GPIO_PIN_RESET);

    // ----------------------------------------------------------- \\ 
}

//    ____
//   /    \  __
//   |__ _|_/__|
//   |_| |_|