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
typedef struct {
	unsigned P0: 1;
	unsigned P1: 1;
	unsigned P2: 1;
	unsigned P3: 1;
	unsigned P4: 1;
	unsigned P5: 1;
	unsigned P6: 1;
	unsigned P7: 1;
}PORT;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define INSTRUCTION 0
#define DATA 		1
#define DARW		126
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim22;

/* USER CODE BEGIN PV */
float ANG;

int16_t FLAG_COUNTER,
		PWM_CONTROL,
		VALUE;

uint32_t ATUAL_COUNTER,
		 PASS_COUNTER,
		 PASS_TICK,
		 ATUAL_TICK;

int8_t CTR = 0,
	   OP_CONTROL,
	   ATUAL_MENU,
	   PRESSED,
	   SEG,
	   PASS_SEG,
	   FLAG_TO_COUNT,
	   COUNT_FLAG;

PORT BIT;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM22_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(&htim6 == htim){
		SEG++;
		if(SEG >= 60) SEG = 0;

		if (FLAG_TO_COUNT){
			COUNT_FLAG++;
		}
	}
}

void STARTUP_LCD(void);
void MENU_CONTROL(void);
void ENCODER_READER(void);
void MANAGER_LCD(uint8_t data, uint8_t state);
void SEND_MESSAGE(char *message, uint8_t locale);
void DRAW_CHAR_LCD(uint8_t character, uint8_t locale);
void KEYBOARD_CHECK(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

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
  MX_ADC_Init();
  MX_TIM2_Init();
  MX_TIM22_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
  HAL_TIM_Encoder_Start(&htim22, TIM_CHANNEL_ALL);

  TIM2->CCR1 = 0;

  TIM2->CCR3 = TIM21->ARR / 2;
  TIM2->CCR4 = 0;

  STARTUP_LCD();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
	  KEYBOARD_CHECK(PRESS_GPIO_Port, PRESS_Pin);

	  MENU_CONTROL();
	  ENCODER_READER();
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.OversamplingMode = DISABLE;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime = ADC_SAMPLETIME_160CYCLES_5;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerFrequencyMode = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 500-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

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
  htim6.Init.Prescaler = 8000-1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1000-1;
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
  * @brief TIM22 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM22_Init(void)
{

  /* USER CODE BEGIN TIM22_Init 0 */

  /* USER CODE END TIM22_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM22_Init 1 */

  /* USER CODE END TIM22_Init 1 */
  htim22.Instance = TIM22;
  htim22.Init.Prescaler = 0;
  htim22.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim22.Init.Period = 0xFFFF;
  htim22.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim22.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 8;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 8;
  if (HAL_TIM_Encoder_Init(&htim22, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim22, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM22_Init 2 */

  /* USER CODE END TIM22_Init 2 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D6_Pin|D4_Pin|EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, EN_ENGINE_Pin|D7_Pin|RS_Pin|D5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : D6_Pin D4_Pin EN_Pin */
  GPIO_InitStruct.Pin = D6_Pin|D4_Pin|EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : RW_Pin */
  GPIO_InitStruct.Pin = RW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : EN_ENGINE_Pin D7_Pin RS_Pin D5_Pin */
  GPIO_InitStruct.Pin = EN_ENGINE_Pin|D7_Pin|RS_Pin|D5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PRESS_Pin */
  GPIO_InitStruct.Pin = PRESS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PRESS_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void MENU_CONTROL(void){
	MANAGER_LCD(0x80, INSTRUCTION);

	switch(ATUAL_MENU){
		case 0:
			// SHOW OP CONTROL
			if (CTR == 1 || CTR == -1)  OP_CONTROL += CTR;

			if(OP_CONTROL < 0) OP_CONTROL = 0;


			switch(OP_CONTROL){
				case 0:
					DRAW_CHAR_LCD(DARW, 0x80);
					SEND_MESSAGE(" OP. 01        ", 0x81);
					SEND_MESSAGE("  OP. 02       ", 0xC0);
					break;

				case 1:
					DRAW_CHAR_LCD(DARW, 0xC0);
					SEND_MESSAGE("  OP. 01       ", 0x80);
					SEND_MESSAGE(" OP. 02        ", 0xC1);
					break;

				case 2:
					DRAW_CHAR_LCD(DARW, 0x80);
					SEND_MESSAGE(" CTR. BRILHO    ", 0x81);
					SEND_MESSAGE("  CTR. PONTE H  ", 0xC0);
					break;

				case 3:
					DRAW_CHAR_LCD(DARW, 0xC0);
					SEND_MESSAGE("  CTR. BRILHO   ", 0x80);
					SEND_MESSAGE(" CTR. PONTE H   ", 0xC1);
					break;

			}

			if(OP_CONTROL >= 4) OP_CONTROL = 3;

			// SELECT MENU
			if((OP_CONTROL == 2) && PRESSED == 1){
				ATUAL_MENU = 1;
				SEND_MESSAGE("   CONTROLE DE   ", 0x80);
				SEND_MESSAGE("     BRILHO      ", 0xC0);

				HAL_Delay(2000);

				SEND_MESSAGE("   MANIPULE O  ", 0x80);
				SEND_MESSAGE("  POTENCIOMETRO ", 0xC0);
			}

			if((OP_CONTROL == 3) && PRESSED == 1){
				ATUAL_MENU = 2;
				SEND_MESSAGE("   CONTROLE DA  ", 0x80);
				SEND_MESSAGE("     PONTE H      ", 0xC0);

				HAL_Delay(2000);

				SEND_MESSAGE("   MANIPULE O  ", 0x80);
				SEND_MESSAGE("  POTENCIOMETRO ", 0xC0);
				HAL_TIM_Base_Start_IT(&htim6);
			}


			break;

		case 1:
			HAL_ADC_Start(&hadc);
			HAL_ADC_PollForConversion(&hadc, 100);
			VALUE = HAL_ADC_GetValue(&hadc) / 40.95;
			HAL_ADC_Stop(&hadc);

			PWM_CONTROL = VALUE;

			if(PWM_CONTROL <= 1) PWM_CONTROL = 0;
			TIM2->CCR1 = PWM_CONTROL;

			break;

		case 2:
			KEYBOARD_CHECK(PRESS_GPIO_Port, PRESS_Pin);

			HAL_ADC_Start(&hadc);
			HAL_ADC_PollForConversion(&hadc, 100);
			VALUE = HAL_ADC_GetValue(&hadc);
			HAL_ADC_Stop(&hadc);

			TIM2->CCR3 = VALUE;
			break;

		case 3:
			KEYBOARD_CHECK(PRESS_GPIO_Port, PRESS_Pin);

			HAL_ADC_Start(&hadc);
			HAL_ADC_PollForConversion(&hadc, 100);
			VALUE = HAL_ADC_GetValue(&hadc);
			HAL_ADC_Stop(&hadc);

			TIM2->CCR4 = VALUE;
			break;
	}
}

void DRAW_CHAR_LCD(uint8_t character, uint8_t locale){
	MANAGER_LCD(locale, INSTRUCTION);
	MANAGER_LCD(character, DATA);
}

void ENCODER_READER(void){
	ATUAL_COUNTER = TIM22->CNT; // Puxando contagem precisa do timer

	if (ATUAL_COUNTER > PASS_COUNTER) {
		FLAG_COUNTER = -1;
	}
	else if (ATUAL_COUNTER < PASS_COUNTER){
		FLAG_COUNTER = 1;
	}
	else FLAG_COUNTER = 0;

	PASS_COUNTER = ATUAL_COUNTER;
	ANG += FLAG_COUNTER * 10;
	CTR = FLAG_COUNTER;

	if(ANG > 360) ANG = 0;
	else if(ANG < 1) ANG = 360;
}
void STARTUP_LCD(void){
	MANAGER_LCD(0x33, INSTRUCTION);
	MANAGER_LCD(0x32, INSTRUCTION);
	MANAGER_LCD(0x28, INSTRUCTION);
	MANAGER_LCD(0x0C, INSTRUCTION);
	MANAGER_LCD(0x01, INSTRUCTION);
	HAL_Delay(2);
}
void SEND_MESSAGE(char *message, uint8_t locale){
	MANAGER_LCD(locale, INSTRUCTION);

	for(int i = 0; message[i] != '\0'; ++i){
		MANAGER_LCD(message[i], DATA);
	}
}
void MANAGER_LCD(uint8_t data, uint8_t state){
	BIT.P0 = (data >> 0) & 1;
	BIT.P1 = (data >> 1) & 1;
	BIT.P2 = (data >> 2) & 1;
	BIT.P3 = (data >> 3) & 1;
	BIT.P4 = (data >> 4) & 1;
	BIT.P5 = (data >> 5) & 1;
	BIT.P6 = (data >> 6) & 1;
	BIT.P7 = (data >> 7) & 1;

	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, state);
	HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, BIT.P4);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, BIT.P5);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, BIT.P6);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, BIT.P7);

	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);

	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, BIT.P0);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, BIT.P1);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, BIT.P2);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, BIT.P3);

	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
}
void KEYBOARD_CHECK(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	ATUAL_TICK = HAL_GetTick();

	if ((ATUAL_TICK - PASS_TICK) > 20){
		uint8_t press = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
		if(!press) {
			PRESSED = 1;
		}
		else PRESSED = 0;
	}

	if(ATUAL_MENU == 2 && PRESSED) {
		FLAG_TO_COUNT = PRESSED;

		if(COUNT_FLAG >= 2){
			COUNT_FLAG = 0;
			ATUAL_MENU = 3;
			SEG = 0;
		}
	}
}

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
#ifdef USE_FULL_ASSERT
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
