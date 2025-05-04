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
#include <stdio.h>
#include <stdlib.h>
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
#define LINE 1
#define COLUMN 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

/* USER CODE BEGIN PV */
BIT PORT;
uint32_t AxisX, AxisY;
uint8_t flag = 1, linerSelect = 4;
char dir[10] = "NONE";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
/* USER CODE BEGIN PFP */
void readJoystick(void);
void rangeJoystickReader(void);
int valueCarrier(uint8_t value);
void infoManager(uint8_t data, uint8_t select);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  readJoystick();
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
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

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
  HAL_GPIO_WritePin(GPIOA, SLCTLINE_03_Pin|SLCTLINE_04_Pin|SLCTLINE_05_Pin|SLCTLINE_08_Pin
                          |SLCTCOLUMN_05_Pin|SLCTCOLUMN_04_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SLCTCOLUMN_03_Pin|SLCTCOLUMN_02_Pin|SLCTLINE_07_Pin|SLCTCOLUMN_01_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SLCTCOLUMN_08_Pin|SLCTCOLUMN_07_Pin|SLCTCOLUMN_06_Pin|SLCTLINE_06_Pin
                          |SLCTLINE_01_Pin|SLCTLINE_02_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SLCTLINE_03_Pin SLCTLINE_04_Pin SLCTLINE_05_Pin SLCTLINE_08_Pin
                           SLCTCOLUMN_05_Pin SLCTCOLUMN_04_Pin */
  GPIO_InitStruct.Pin = SLCTLINE_03_Pin|SLCTLINE_04_Pin|SLCTLINE_05_Pin|SLCTLINE_08_Pin
                          |SLCTCOLUMN_05_Pin|SLCTCOLUMN_04_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SLCTCOLUMN_03_Pin SLCTCOLUMN_02_Pin SLCTLINE_07_Pin SLCTCOLUMN_01_Pin */
  GPIO_InitStruct.Pin = SLCTCOLUMN_03_Pin|SLCTCOLUMN_02_Pin|SLCTLINE_07_Pin|SLCTCOLUMN_01_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SLCTCOLUMN_08_Pin SLCTCOLUMN_07_Pin SLCTCOLUMN_06_Pin SLCTLINE_06_Pin
                           SLCTLINE_01_Pin SLCTLINE_02_Pin */
  GPIO_InitStruct.Pin = SLCTCOLUMN_08_Pin|SLCTCOLUMN_07_Pin|SLCTCOLUMN_06_Pin|SLCTLINE_06_Pin
                          |SLCTLINE_01_Pin|SLCTLINE_02_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// Data bit managers
void infoManager(uint8_t value, uint8_t select){
	int data = 0;
	if (select == LINE) data = valueCarrier(value);
	else data = value;

	PORT.P0 = (data >> 0) & 1;
	PORT.P1 = (data >> 1) & 1;
	PORT.P2 = (data >> 2) & 1;
	PORT.P3 = (data >> 3) & 1;
	PORT.P4 = (data >> 4) & 1;
	PORT.P5 = (data >> 5) & 1;
	PORT.P6 = (data >> 6) & 1;
	PORT.P7 = (data >> 7) & 1;

	if (select == LINE){
		HAL_GPIO_WritePin(SLCTLINE_01_GPIO_Port, SLCTLINE_01_Pin, PORT.P0);
		HAL_GPIO_WritePin(SLCTLINE_02_GPIO_Port, SLCTLINE_02_Pin, PORT.P1);
		HAL_GPIO_WritePin(SLCTLINE_03_GPIO_Port, SLCTLINE_03_Pin, PORT.P2);
		HAL_GPIO_WritePin(SLCTLINE_04_GPIO_Port, SLCTLINE_04_Pin, PORT.P3);
		HAL_GPIO_WritePin(SLCTLINE_05_GPIO_Port, SLCTLINE_05_Pin, PORT.P4);
		HAL_GPIO_WritePin(SLCTLINE_06_GPIO_Port, SLCTLINE_06_Pin, PORT.P5);
		HAL_GPIO_WritePin(SLCTLINE_07_GPIO_Port, SLCTLINE_07_Pin, PORT.P6);
		HAL_GPIO_WritePin(SLCTLINE_08_GPIO_Port, SLCTLINE_08_Pin, PORT.P7);

	} else if (select == COLUMN){
		HAL_GPIO_WritePin(SLCTCOLUMN_01_GPIO_Port, SLCTCOLUMN_01_Pin, !(PORT.P0));
		HAL_GPIO_WritePin(SLCTCOLUMN_02_GPIO_Port, SLCTCOLUMN_02_Pin, !(PORT.P1));
		HAL_GPIO_WritePin(SLCTCOLUMN_03_GPIO_Port, SLCTCOLUMN_03_Pin, !(PORT.P2));
		HAL_GPIO_WritePin(SLCTCOLUMN_04_GPIO_Port, SLCTCOLUMN_04_Pin, !(PORT.P3));
		HAL_GPIO_WritePin(SLCTCOLUMN_05_GPIO_Port, SLCTCOLUMN_05_Pin, !(PORT.P4));
		HAL_GPIO_WritePin(SLCTCOLUMN_06_GPIO_Port, SLCTCOLUMN_06_Pin, !(PORT.P5));
		HAL_GPIO_WritePin(SLCTCOLUMN_07_GPIO_Port, SLCTCOLUMN_07_Pin, !(PORT.P6));
		HAL_GPIO_WritePin(SLCTCOLUMN_08_GPIO_Port, SLCTCOLUMN_08_Pin, !(PORT.P7));
	}
}
int valueCarrier(uint8_t value){
	switch(value){
		case 1:
			return 0x03;
			break;
		case 2:
			return 0x06;
			break;
		case 3:
			return 0x0C;
			break;
		case 4:
			return 0x18;
			break;
		case 5:
			return 0x30;
			break;
		case 6:
			return 0x60;
			break;
		case 7:
			return 0xC0;
			break;
		case 8:
			return 0x80;
			break;
		default:
			return 0x03;
			break;
	}
}

// Data joystick manager
void readJoystick(void){
	HAL_ADC_Start(&hadc);
	for (int i = 0; i < 2; ++i){
		HAL_ADC_PollForConversion(&hadc, 100);
		if (i == 0) AxisY = HAL_ADC_GetValue(&hadc);
		else AxisX = HAL_ADC_GetValue(&hadc);
	}
	rangeJoystickReader();
	HAL_ADC_Stop(&hadc);
}
void rangeJoystickReader(void){
	// LEFT MOVIMENT
	if (AxisX <= 70) infoManager(0x03, COLUMN);
	else if (AxisX <= 700) infoManager(0x06, COLUMN);
	else if (AxisX <= 2000) infoManager(0x0C, COLUMN);
	// RITGH MOVIMENT
	else if (AxisX >= 2940 && AxisX <= 2950) infoManager(0xC0, COLUMN);
	else if (AxisX >= 3600) infoManager(0x60, COLUMN);
	else if (AxisX >= 4000) infoManager(0x30, COLUMN);
	else infoManager(0x18, COLUMN);

	// UP MOVIMENT
	if (AxisY == 4095) infoManager(1, LINE);
	else if (AxisY == 3500) infoManager(2, LINE);
	else if (AxisY == 2900) infoManager(3, LINE);
	// DOWN MOVIMENT
	else if (AxisY <= 70) infoManager(7, LINE);
	else if (AxisY == 1100) infoManager(5, LINE);
	else if (AxisY == 2500) infoManager(6, LINE);
	else infoManager(4, LINE);

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
