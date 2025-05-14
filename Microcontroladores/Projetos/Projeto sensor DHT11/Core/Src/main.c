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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct{
	unsigned P0: 1,
			 P1: 1,
			 P2: 1,
			 P3: 1,
			 P4: 1,
			 P5: 1,
			 P6: 1,
			 P7: 1;
}PORT;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */
PORT bit;
uint32_t tempResult, umidResult;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */
void DHTExitSet(void);
void DHTInputSet(void);

void StartLCD(void);
void DataManager(int data, int rs);
void MessageManager(char * message);
void DHTInterpreter(void);

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
  HAL_TIM_Base_Start(&htim6);
  StartLCD();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1){
	  MessageManager("Hello world!");
      DataManager(0x80, 0);
      DHTInterpreter();

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
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
  htim6.Init.Prescaler = 8-1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 0xFFFF-1;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, EN_Pin|D0_Pin|D1_Pin|DHT11_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D2_Pin|RS_Pin|RW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : EN_Pin D0_Pin D1_Pin DHT11_Pin */
  GPIO_InitStruct.Pin = EN_Pin|D0_Pin|D1_Pin|DHT11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : D3_Pin */
  GPIO_InitStruct.Pin = D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(D3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : D2_Pin RS_Pin RW_Pin */
  GPIO_InitStruct.Pin = D2_Pin|RS_Pin|RW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void DataManager(int data, int rs){
	bit.P0 = (data >> 0) & 1;
	bit.P1 = (data >> 1) & 1;
	bit.P2 = (data >> 2) & 1;
	bit.P3 = (data >> 3) & 1;
	bit.P4 = (data >> 4) & 1;
	bit.P5 = (data >> 5) & 1;
	bit.P6 = (data >> 6) & 1;
	bit.P7 = (data >> 7) & 1;

	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, rs);
	HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, RESET);

	HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, bit.P4);
	HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, bit.P5);
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, bit.P6);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, bit.P7);

	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);

	HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, bit.P0);
	HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, bit.P1);
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, bit.P2);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, bit.P3);

	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
}

void StartLCD(void){
	HAL_Delay(20);
	DataManager(0x33, 0);
	DataManager(0x32, 0);

	DataManager(0x28, 0);

	DataManager(0x0C, 0);
	DataManager(0x06, 0);
	DataManager(0x01, 0);

	HAL_Delay(2);
}

void MessageManager(char * message){
	for (int i = 0; message[i] != '\0'; ++i){
		DataManager(message[i], 1);
	}
}

/*--------------------------------------------*/
/*   			DHT 11 CODE					  */
/*--------------------------------------------*/

// Interpretador de DHT11
void DHTInterpreter(void){
	uint16_t read[2], data[42], tmph = 0, umidh = 0;
	uint8_t  bits[40];

	HAL_Delay(500);

	// Definição de pino como saida --> entrada.
	DHTExitSet();
	DHTInputSet();

	// Zerando temporizador.
	__HAL_TIM_SET_COUNTER(&htim6, 0);

	// Lendo valores do sinal.
	for (int i = 0; i < 42; ++i){
		while(!HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)) read[0] = __HAL_TIM_GET_COUNTER(&htim6);
		while( HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)) read[1] = __HAL_TIM_GET_COUNTER(&htim6);

		data[i] = read[1] - read[0];
	}

	// Definição de bits com base no tempo.
	for (int i = 0; i < 40; ++i){
		if 	    ((data[i + 2] >= 20) && (data[i + 2] <= 32)) bits[i] = 0;
		else if ((data[i + 2 >= 65]) && (data[i + 2] <= 75)) bits[i] = 1;
	}

	// Calculo.
	for (int i = 0; i < 8; ++i){
		tmph  += bits[i + 16] << (7 - i);
		umidh += bits[i] 	  << (7 - i);
	}

	// Atribuição.
	tempResult = tmph;
	umidResult = umidh;
}

// Definição de pino como saida.
void DHTExitSet(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Setando pino como modo de saida.
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);

	// Enviando informação para inicialização da comunicação.
	HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_RESET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_SET);

}

// Definição de pino como entrada.
void DHTInputSet(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // Setando pino como modo de entrada.
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}
/*--------------------------------------------*/

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
