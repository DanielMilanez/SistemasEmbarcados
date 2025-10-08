#define DO      3793
#define RE      3405
#define MI      3034
#define FA      2863
#define SOL     2551
#define LA      2273
#define SI      2006
#define DO_ALTO 1896
#define FA_ALTO 1431
#define SOL_ALTO 1275
#define LA_ALTO 1136
#define SI_ALTO 1003

#define DELAY 250

char Tmap[4][3] = {{'1','2','3'},
                   {'4','5','6'},
                   {'7','8','9'},
                   {'*','0','#'}};
                   
char response = 0;

uint8_t atual_column = 0;
uint16_t count_period = 1894;

void Keyboard_check(void){
	switch (atual_column){
		case 0:
			HAL_GPIO_WritePin(COLUMN_01_GPIO_Port, COLUMN_01_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COLUMN_02_GPIO_Port, COLUMN_02_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COLUMN_03_GPIO_Port, COLUMN_03_Pin, GPIO_PIN_SET);
			Line_verify();

			atual_column = 1;
			break;

		case 1:
			HAL_GPIO_WritePin(COLUMN_01_GPIO_Port, COLUMN_01_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COLUMN_02_GPIO_Port, COLUMN_02_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(COLUMN_03_GPIO_Port, COLUMN_03_Pin, GPIO_PIN_SET);
			Line_verify();

			atual_column = 2;
			break;

		case 2:
			HAL_GPIO_WritePin(COLUMN_01_GPIO_Port, COLUMN_01_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COLUMN_02_GPIO_Port, COLUMN_02_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(COLUMN_03_GPIO_Port, COLUMN_03_Pin, GPIO_PIN_RESET);
			Line_verify();

			atual_column = 0;
			break;
	}
}

void Line_verify(void){
	uint8_t bline1 = HAL_GPIO_ReadPin(LINE_01_GPIO_Port, LINE_01_Pin),
			bline2 = HAL_GPIO_ReadPin(LINE_02_GPIO_Port, LINE_02_Pin),
			bline3 = HAL_GPIO_ReadPin(LINE_03_GPIO_Port, LINE_03_Pin),
			bline4 = HAL_GPIO_ReadPin(LINE_04_GPIO_Port, LINE_04_Pin);

	if (!bline1) response = Tmap[0][atual_column];
	else if (!bline2) response = Tmap[1][atual_column];
	else if (!bline3) response = Tmap[2][atual_column];
	else if (!bline4) response = Tmap[3][atual_column];

	switch(response){
		case '1':
			count_period = DO; // DO
			break;

		case '2':
			count_period = RE; // RE
			break;

		case '3':
			count_period = MI; // MI
			break;

		case '4':
			count_period = FA; // FA
			break;

		case '5':
			count_period = SOL; // SOL
			break;

		case '6':
			count_period = LA; // LA
			break;

		case '7':
			count_period = SI; // SI
			break;

		case '8': // Brilha brilha estrelhinha
			Note_tone(DO, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(DO, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(SOL, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(SOL, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(LA, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(LA, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(SOL, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(SOL, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(FA, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(FA, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(MI, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(MI, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(RE, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(RE, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(DO, DELAY);
			HAL_Delay(DELAY);

			Note_tone(FA, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(FA, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(MI, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(MI, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(RE, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(RE, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(DO, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(SOL, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(SOL, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(FA, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(FA, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(MI, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(MI, DELAY);
			HAL_Delay(DELAY / 2);

			Note_tone(RE, DELAY);
			HAL_Delay(DELAY / 2);
			break;

		default:
			count_period = 0;
			break;
	}
	while (!bline1 || !bline2 || !bline3 || !bline4){
		Note_define(count_period);
		bline1 = HAL_GPIO_ReadPin(LINE_01_GPIO_Port, LINE_01_Pin),
		bline2 = HAL_GPIO_ReadPin(LINE_02_GPIO_Port, LINE_02_Pin),
		bline3 = HAL_GPIO_ReadPin(LINE_03_GPIO_Port, LINE_03_Pin),
		bline4 = HAL_GPIO_ReadPin(LINE_04_GPIO_Port, LINE_04_Pin);
	}
	Note_define(count_period);
	HAL_Delay(10);
	response = 0;
}

void Note_define(uint16_t note){
	uint8_t dc = note / 2;
	TIM2 -> CCR1 = dc;
	TIM2 -> ARR  = note;
}

void Note_tone(uint16_t note, uint32_t delay_active){
	Note_define(note);
	HAL_Delay(delay_active);
	Note_define(0);
}
