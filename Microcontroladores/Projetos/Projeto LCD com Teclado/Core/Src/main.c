/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef struct filter{
	unsigned P0 : 1;
	unsigned P1 : 1;
	unsigned P2 : 1;
	unsigned P3 : 1;
	unsigned P4 : 1;
	unsigned P5 : 1;
	unsigned P6 : 1;
	unsigned P7 : 1;
} filter;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DELAY_TIME 20
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */
filter port;

uint8_t atualColumn = 0,
		bline_1,
		bline_2,
		bline_3,
		bline_4,
		word_count = 0,
		logonAble = 0,
		atualMenu = 1,
		flag = 1;

char response = 0,
		login = 0;

char password[5] = "";
char tmap[4][3] = {
					{'1', '2', '3'},
					{'4', '5', '6'},
					{'7', '8', '9'},
					{'*', '0', '#'}
				  };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */

// Funções para o teclado
void Keyboard_check(void);
void Line_verify(uint8_t atual_column);

// Funções para o LCD
void Start_LCD(void);
void Menu_system(void);
void Process_Password(void);
void Mensage_LCD(char *mensage);
void Controler_LCD(uint8_t data, uint8_t gate);

// Configurações para o LCD

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim6);
  HAL_Delay(DELAY_TIME);
  Start_LCD();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
	  Keyboard_check();
	  Menu_system();
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 12000;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, EN_Pin|RW_Pin|DB1_Pin|RS_Pin
                          |COLUMN_01_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DB4_Pin|DB7_Pin|DB5_Pin|DB6_Pin
                          |DB0_Pin|COLUMN_02_Pin|COLUMN_03_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DB3_Pin|DB2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : EN_Pin RW_Pin RS_Pin */
  GPIO_InitStruct.Pin = EN_Pin|RW_Pin|RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DB4_Pin DB7_Pin DB5_Pin DB6_Pin
                           DB0_Pin COLUMN_02_Pin COLUMN_03_Pin */
  GPIO_InitStruct.Pin = DB4_Pin|DB7_Pin|DB5_Pin|DB6_Pin
                          |DB0_Pin|COLUMN_02_Pin|COLUMN_03_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LINE_04_Pin LINE_03_Pin */
  GPIO_InitStruct.Pin = LINE_04_Pin|LINE_03_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : DB1_Pin COLUMN_01_Pin */
  GPIO_InitStruct.Pin = DB1_Pin|COLUMN_01_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DB3_Pin DB2_Pin */
  GPIO_InitStruct.Pin = DB3_Pin|DB2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LINE_02_Pin LINE_01_Pin */
  GPIO_InitStruct.Pin = LINE_02_Pin|LINE_01_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

}

// Funções para o LCD
void Start_LCD(void){
	Controler_LCD(0x33, 0);
	Controler_LCD(0x32, 0);
	Controler_LCD(0x28, 0);

//	Controler_LCD(0x0F, 0); // 0x0D
	Controler_LCD(0x0C, 0);
	Controler_LCD(0x06, 0);
	Controler_LCD(0x01, 0);
}

// Funções para o teclado
void Keyboard_check(void){
	switch(atualColumn){
		case 0:
			HAL_GPIO_WritePin(COLUMN_01_GPIO_Port, COLUMN_01_Pin, 0);
			HAL_GPIO_WritePin(COLUMN_02_GPIO_Port, COLUMN_02_Pin, 1);
			HAL_GPIO_WritePin(COLUMN_03_GPIO_Port, COLUMN_03_Pin, 1);
			Line_verify(0);
			atualColumn = 1;
			break;

		case 1:
			HAL_GPIO_WritePin(COLUMN_01_GPIO_Port, COLUMN_01_Pin, 1);
			HAL_GPIO_WritePin(COLUMN_02_GPIO_Port, COLUMN_02_Pin, 0);
			HAL_GPIO_WritePin(COLUMN_03_GPIO_Port, COLUMN_03_Pin, 1);
			Line_verify(1);
			atualColumn = 2;
			break;

		case 2:
			HAL_GPIO_WritePin(COLUMN_01_GPIO_Port, COLUMN_01_Pin, 1);
			HAL_GPIO_WritePin(COLUMN_02_GPIO_Port, COLUMN_02_Pin, 1);
			HAL_GPIO_WritePin(COLUMN_03_GPIO_Port, COLUMN_03_Pin, 0);
			Line_verify(2);
			atualColumn = 0;
			break;
	}
}

// Verificando botão precionado
void Line_verify(uint8_t atual_column) {
	bline_1 = HAL_GPIO_ReadPin(LINE_01_GPIO_Port, LINE_01_Pin);
	bline_2 = HAL_GPIO_ReadPin(LINE_02_GPIO_Port, LINE_02_Pin);
	bline_3 = HAL_GPIO_ReadPin(LINE_03_GPIO_Port, LINE_03_Pin);
	bline_4 = HAL_GPIO_ReadPin(LINE_04_GPIO_Port, LINE_04_Pin);

    if (!bline_1){
    	response = tmap[0][atual_column];
    	logonAble = 1;
    }
    else if (!bline_2) {
    	response = tmap[1][atual_column];
       	logonAble = 1;
    }
    else if (!bline_3){
    	response = tmap[2][atual_column];
       	logonAble = 1;
    }
    else if (!bline_4) {
    	response = tmap[3][atual_column];
       	logonAble = 1;
    }

    else logonAble = 0;
    if (logonAble) Process_Password();
}

// Função para processar a entrada da senha
void Process_Password(void) {
	if (!flag){
		if (logonAble && word_count < 4) {  // Limite de 4 caracteres
			password[word_count] = response;
			word_count++;
			password[word_count] = '\0';  // Adiciona o terminador de string

			for (uint8_t i = 0; i < word_count; i++) {
				Mensage_LCD("*");  // Exibe um asterisco para cada caractere digitado
				HAL_Delay(50);
			}
		}


		if (word_count == 4) {  // Após 4 caracteres, verifica a senha
			if (login == '1') {
				if (strcmp(password, "8922") == 0) atualMenu = 3;
				else atualMenu = 4;
			}

			if (login == '2') {
				if (strcmp(password, "1698") == 0) atualMenu = 3;
				else atualMenu = 4;
			}

			// Resetando variáveis
			flag = 1;
			word_count = 0;
			logonAble = 0;
			response = ' ';
			login = '0';
			memset(password, 0, sizeof(password));
			Controler_LCD(0x01, 0);  // Limpa a tela
		}
	} else {
		flag = 0;
	}
}

// Controle para exibição de informações unarias no LCD
void Controler_LCD(uint8_t data, uint8_t gate){
	port.P0 = (data >> 0) & 1;
	port.P1 = (data >> 1) & 1;
	port.P2 = (data >> 2) & 1;
	port.P3 = (data >> 3) & 1;
	port.P4 = (data >> 4) & 1;
	port.P5 = (data >> 5) & 1;
	port.P6 = (data >> 6) & 1;
	port.P7 = (data >> 7) & 1;

	if (gate){
		HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
	}


	HAL_GPIO_WritePin(DB4_GPIO_Port, DB4_Pin, port.P4);
	HAL_GPIO_WritePin(DB5_GPIO_Port, DB5_Pin, port.P5);
	HAL_GPIO_WritePin(DB6_GPIO_Port, DB6_Pin, port.P6);
	HAL_GPIO_WritePin(DB7_GPIO_Port, DB7_Pin, port.P7);

	HAL_Delay(1);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(DB4_GPIO_Port, DB4_Pin, port.P0);
	HAL_GPIO_WritePin(DB5_GPIO_Port, DB5_Pin, port.P1);
	HAL_GPIO_WritePin(DB6_GPIO_Port, DB6_Pin, port.P2);
	HAL_GPIO_WritePin(DB7_GPIO_Port, DB7_Pin, port.P3);

	HAL_Delay(1);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);

}

// Exibindo informações compostas no LCD
void Mensage_LCD(char *mensage){
	for (int i = 0; mensage[i] != '\0'; ++i){
		Controler_LCD(mensage[i], 1);
	}
}

// Sistema de menu e paginação
void Menu_system(void){
	switch(atualMenu){
		case 1:
			Keyboard_check();
			Controler_LCD(0x80, 0);
			Mensage_LCD("Informe o login");

			Controler_LCD(0xC0, 0);
			Mensage_LCD(">> ");
			login = response;
			char login_str[2] = {login, '\0'};
			Mensage_LCD(login_str);
			HAL_Delay(50);

			if (login == '1' || login == '2') {
				atualMenu = 2;
				logonAble = 1;
				Controler_LCD(0x01, 0);
			}

			break;

		case 2:
			if (login == '1'){
				Controler_LCD(0x80, 0);
				Mensage_LCD("Login: ");
				Mensage_LCD("Guto");
			}

			if (login == '2'){
				Controler_LCD(0x80, 0);
				Mensage_LCD("Login: ");
				Mensage_LCD("Jhon");
			}
		    Controler_LCD(0xC0, 0);
		    Mensage_LCD("Senha: ");
			break;

		case 3:
			Controler_LCD(0x80, 0);
			Mensage_LCD("Sucesso!!!");

			Controler_LCD(0xC0, 0);
			Mensage_LCD("Bem-Vindo");

            HAL_Delay(5000);
            Controler_LCD(0x01, 0);

            atualMenu = 1;
			break;

		case 4:
            Controler_LCD(0x01, 0);
            Controler_LCD(0x80, 0);

            Mensage_LCD("Senha incorreta");
            HAL_Delay(2000);

            Controler_LCD(0x01, 0);
            atualMenu = 1;

			break;
	}
}


//    ____
//   /    \  __
//   |__ _|_/__|
//   |_| |_|


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
