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
}BIT;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define INSTRUCTION 0
#define DATA  1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

/* USER CODE BEGIN PV */
BIT PORT;
uint16_t adc_value_set[2], adc_read;
uint8_t locale = 0, bars = 0;
uint16_t compare_value = 0;

unsigned char BATTERY_CHAR[6][8] = {
		{0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F}, // Battery back off
		{0x1F, 0x10, 0x17, 0x17, 0x17, 0x17, 0x10, 0x1F}, // Battery back ON
		{0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F}, // Battery middle off
		{0x1F, 0x00, 0x0E, 0x0E, 0x0E, 0x0E, 0x00, 0x1F}, // Battery middle ON
		{0x1E, 0x02, 0x03, 0x01, 0x01, 0x03, 0x02, 0x1E}, // Battery front off
		{0x1E, 0x02, 0x1B, 0x19, 0x19, 0x1B, 0x02, 0x1E}  // Battery front ON
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC_Init(void);
/* USER CODE BEGIN PFP */

void LCD_STARTUP(void);
void LCD_SEND_MESSAGE(char * message);
void LCD_DATA_MANAGER(uint8_t data, uint8_t state);
void LCD_CREATE_CHAR(uint8_t ADDRS, unsigned char * data, uint8_t select);

uint8_t VERIFY_ADC_VALUE(void);
uint8_t LCD_INTERPRETER_LOCALE(uint8_t row, uint8_t column);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){
	adc_read = HAL_ADC_GetValue(hadc);
}

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
  MX_DMA_Init();
  MX_ADC_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADC_Start_DMA(&hadc, (uint32_t *) adc_value_set, 2);
  LCD_STARTUP();

  LCD_CREATE_CHAR(0,  (unsigned char*) BATTERY_CHAR , 0);
  LCD_CREATE_CHAR(1,  (unsigned char*) BATTERY_CHAR , 1);
  LCD_CREATE_CHAR(2,  (unsigned char*) BATTERY_CHAR , 2);
  LCD_CREATE_CHAR(3,  (unsigned char*) BATTERY_CHAR , 3);
  LCD_CREATE_CHAR(4,  (unsigned char*) BATTERY_CHAR , 4);
  LCD_CREATE_CHAR(5,  (unsigned char*) BATTERY_CHAR , 5);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
	locale = LCD_INTERPRETER_LOCALE(1, 4);
	LCD_DATA_MANAGER(locale, INSTRUCTION);
	LCD_SEND_MESSAGE("LOAD || TESTER");

	bars = VERIFY_ADC_VALUE();

	locale = LCD_INTERPRETER_LOCALE(5, 8);
	LCD_DATA_MANAGER(locale, INSTRUCTION);

	switch (bars){
		case 0:
			LCD_DATA_MANAGER(0x00, DATA);
			LCD_DATA_MANAGER(0x02, DATA);
			LCD_DATA_MANAGER(0x02, DATA);
			LCD_DATA_MANAGER(0x02, DATA);
			LCD_DATA_MANAGER(0x04, DATA);
			break;
		case 1:
			LCD_DATA_MANAGER(0x01, DATA);
			LCD_DATA_MANAGER(0x02, DATA);
			LCD_DATA_MANAGER(0x02, DATA);
			LCD_DATA_MANAGER(0x02, DATA);
			LCD_DATA_MANAGER(0x04, DATA);
			break;
		case 2:
			LCD_DATA_MANAGER(0x01, DATA);
			LCD_DATA_MANAGER(0x03, DATA);
			LCD_DATA_MANAGER(0x02, DATA);
			LCD_DATA_MANAGER(0x02, DATA);
			LCD_DATA_MANAGER(0x04, DATA);
			break;
		case 3:
			LCD_DATA_MANAGER(0x01, DATA);
			LCD_DATA_MANAGER(0x03, DATA);
			LCD_DATA_MANAGER(0x03, DATA);
			LCD_DATA_MANAGER(0x02, DATA);
			LCD_DATA_MANAGER(0x04, DATA);
			break;
		case 4:
			LCD_DATA_MANAGER(0x01, DATA);
			LCD_DATA_MANAGER(0x03, DATA);
			LCD_DATA_MANAGER(0x03, DATA);
			LCD_DATA_MANAGER(0x03, DATA);
			LCD_DATA_MANAGER(0x04, DATA);
			break;
		case 5:
			LCD_DATA_MANAGER(0x01, DATA);
			LCD_DATA_MANAGER(0x03, DATA);
			LCD_DATA_MANAGER(0x03, DATA);
			LCD_DATA_MANAGER(0x03, DATA);
			LCD_DATA_MANAGER(0x05, DATA);
			break;
	}

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
  hadc.Init.DMAContinuousRequests = ENABLE;
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
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

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

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RS_Pin|RW_Pin|EN_Pin|D7_Pin
                          |D6_Pin|D5_Pin|D4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RS_Pin RW_Pin EN_Pin D7_Pin
                           D6_Pin D5_Pin D4_Pin */
  GPIO_InitStruct.Pin = RS_Pin|RW_Pin|EN_Pin|D7_Pin
                          |D6_Pin|D5_Pin|D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void LCD_STARTUP(void){
	LCD_DATA_MANAGER(0x33, INSTRUCTION);
	LCD_DATA_MANAGER(0x32, INSTRUCTION);

	LCD_DATA_MANAGER(0x28, INSTRUCTION);

	LCD_DATA_MANAGER(0x0C, INSTRUCTION);
	LCD_DATA_MANAGER(0x06, INSTRUCTION);
	LCD_DATA_MANAGER(0x01, INSTRUCTION);

	HAL_Delay(2);
}

void LCD_SEND_MESSAGE(char * message){
	for (int i = 0; message[i] != '\0'; ++i){
		LCD_DATA_MANAGER(message[i], DATA);
	}
}
void LCD_DATA_MANAGER(uint8_t data, uint8_t state){
	PORT.P0 = (data >> 0) & 1;
	PORT.P1 = (data >> 1) & 1;
	PORT.P2 = (data >> 2) & 1;
	PORT.P3 = (data >> 3) & 1;
	PORT.P4 = (data >> 4) & 1;
	PORT.P5 = (data >> 5) & 1;
	PORT.P6 = (data >> 6) & 1;
	PORT.P7 = (data >> 7) & 1;

	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, state);
	HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, PORT.P4);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, PORT.P5);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, PORT.P6);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, PORT.P7);

	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);

	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, PORT.P0);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, PORT.P1);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, PORT.P2);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, PORT.P3);

	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
}


void LCD_CREATE_CHAR(uint8_t ADDRS, unsigned char* data, uint8_t select){
	switch (ADDRS){
		case 0: LCD_DATA_MANAGER(0x40 + 0,  INSTRUCTION); break;
		case 1: LCD_DATA_MANAGER(0x40 + 8,  INSTRUCTION); break;
		case 2: LCD_DATA_MANAGER(0x40 + 16, INSTRUCTION); break;
		case 3: LCD_DATA_MANAGER(0x40 + 24, INSTRUCTION); break;
		case 4: LCD_DATA_MANAGER(0x40 + 32, INSTRUCTION); break;
		case 5: LCD_DATA_MANAGER(0x40 + 40, INSTRUCTION); break;
		case 6: LCD_DATA_MANAGER(0x40 + 48, INSTRUCTION); break;
		case 7: LCD_DATA_MANAGER(0x40 + 56, INSTRUCTION); break;
	}

	for (int i = 0; i < 8; ++i) LCD_DATA_MANAGER(BATTERY_CHAR[select][i], DATA);
}

uint8_t LCD_INTERPRETER_LOCALE(uint8_t row, uint8_t column){
	if ((row == 1) && (column <= 13)){
		switch (column){
			case 1: column = 0x80; break;
			case 2: column = 0x81; break;
			case 3: column = 0x82; break;
			case 4: column = 0x83; break;
			case 5: column = 0x84; break;
			case 6: column = 0x85; break;
			case 7: column = 0x86; break;
			case 8: column = 0x87; break;
			case 9: column = 0x88; break;
			case 10: column = 0x89; break;
			case 11: column = 0x8A; break;
			case 12: column = 0x8B; break;
			case 13: column = 0x8C; break;
			case 14: column = 0x8D; break;
			case 15: column = 0x8E; break;
			case 16: column = 0x8F; break;
			case 17: column = 0x90; break;
			case 18: column = 0x91; break;
			case 19: column = 0x92; break;
			case 20: column = 0x93; break;
		}
	}

	else if ((row == 2) && (column <= 13)){
		switch (column){
			case 1: column = 0xC0; break;
			case 2: column = 0xC1; break;
			case 3: column = 0xC2; break;
			case 4: column = 0xC3; break;
			case 5: column = 0xC4; break;
			case 6: column = 0xC5; break;
			case 7: column = 0xC6; break;
			case 8: column = 0xC7; break;
			case 9: column = 0xC8; break;
			case 10: column = 0xC9; break;
			case 11: column = 0xCA; break;
			case 12: column = 0xCB; break;
			case 13: column = 0xCC; break;
			case 14: column = 0xCD; break;
			case 15: column = 0xCE; break;
			case 16: column = 0xCF; break;
			case 17: column = 0xD0; break;
			case 18: column = 0xD1; break;
			case 19: column = 0xD2; break;
			case 20: column = 0xD3; break;
		}
	}

	else if ((row == 3) && (column <= 13)){
		switch (column){
			case 1: column = 0x94; break;
			case 2: column = 0x95; break;
			case 3: column = 0x96; break;
			case 4: column = 0x97; break;
			case 5: column = 0x98; break;
			case 6: column = 0x99; break;
			case 7: column = 0x9A; break;
			case 8: column = 0x9B; break;
			case 9: column = 0x9C; break;
			case 10: column = 0x9D; break;
			case 11: column = 0x9E; break;
			case 12: column = 0x9F; break;
			case 13: column = 0xA0; break;
			case 14: column = 0xA1; break;
			case 15: column = 0xA2; break;
			case 16: column = 0xA3; break;
			case 17: column = 0xA4; break;
			case 18: column = 0xA5; break;
			case 19: column = 0xA6; break;
			case 20: column = 0xA7; break;
		}
	}

	else if ((row == 4) && (column <= 13)){
		switch (column){
			case 1: column = 0xD4; break;
			case 2: column = 0xD5; break;
			case 3: column = 0xD6; break;
			case 4: column = 0xD7; break;
			case 5: column = 0xD8; break;
			case 6: column = 0xD9; break;
			case 7: column = 0xDA; break;
			case 8: column = 0xDB; break;
			case 9: column = 0xDC; break;
			case 10: column = 0xDD; break;
			case 11: column = 0xDE; break;
			case 12: column = 0xDF; break;
			case 13: column = 0xE0; break;
			case 14: column = 0xE1; break;
			case 15: column = 0xE2; break;
			case 16: column = 0xE3; break;
			case 17: column = 0xE4; break;
			case 18: column = 0xE5; break;
			case 19: column = 0xE6; break;
			case 20: column = 0xE7; break;
		}
	}

	return column;
}

uint8_t VERIFY_ADC_VALUE(void){
	uint8_t value;
	uint16_t fundamental = 819;

	if (adc_read < 70) compare_value = 0;
	else if(adc_read > 70 && adc_read <= fundamental * 2) compare_value = fundamental;
	else if(adc_read >= fundamental * 2 && adc_read < fundamental * 3) compare_value = fundamental * 2;
	else if(adc_read >= fundamental * 3 && adc_read < fundamental * 4) compare_value = fundamental * 3;
	else if(adc_read >= fundamental * 4 && adc_read < fundamental * 5) compare_value = fundamental * 4;
	else if(adc_read == fundamental * 5) compare_value = 819 * 5;

	for (int i = 1; i < 6; ++i){
		if (fundamental * i == compare_value){
			value = i;
			break;
		}
	}
	return value;
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
