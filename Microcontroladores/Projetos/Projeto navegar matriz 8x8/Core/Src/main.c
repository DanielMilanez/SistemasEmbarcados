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
#include <string.h>
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
#define DIM 8

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

/* USER CODE BEGIN PV */
BIT data;
uint32_t axisX, axisY;
char dir[10]= "NONE";

int map[8][8];
int value, lineSelect = 4, columSelect = 4;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
/* USER CODE BEGIN PFP */
void resetMap(void);
void verifyDirection(void);
void informationlLine(int value);
void informationCarrer(int value);
void infoManager(int value, int lineSelector);
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
  /* USER CODE BEGIN 2 */
  resetMap();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {

	  verifyDirection();
	  infoManager(columSelect, lineSelect);
	  HAL_Delay(100);
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
  HAL_GPIO_WritePin(GPIOA, SLCT_03_Pin|SLCT_04_Pin|SLCT_05_Pin|SW_BTN_Pin
                          |SLCT_08_Pin|SLCTRED_05_Pin|SLCTRED_04_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SLCTRED_03_Pin|SLCTRED_02_Pin|SLCT_07_Pin|SLCTRED_01_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SLCTRED_08_Pin|SLCTRED_07_Pin|SLCTRED_06_Pin|SLCT_06_Pin
                          |SLCT_01_Pin|SLCT_02_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SLCT_03_Pin SLCT_04_Pin SLCT_05_Pin SW_BTN_Pin
                           SLCT_08_Pin SLCTRED_05_Pin SLCTRED_04_Pin */
  GPIO_InitStruct.Pin = SLCT_03_Pin|SLCT_04_Pin|SLCT_05_Pin|SW_BTN_Pin
                          |SLCT_08_Pin|SLCTRED_05_Pin|SLCTRED_04_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SLCTRED_03_Pin SLCTRED_02_Pin SLCT_07_Pin SLCTRED_01_Pin */
  GPIO_InitStruct.Pin = SLCTRED_03_Pin|SLCTRED_02_Pin|SLCT_07_Pin|SLCTRED_01_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SLCTRED_08_Pin SLCTRED_07_Pin SLCTRED_06_Pin SLCT_06_Pin
                           SLCT_01_Pin SLCT_02_Pin */
  GPIO_InitStruct.Pin = SLCTRED_08_Pin|SLCTRED_07_Pin|SLCTRED_06_Pin|SLCT_06_Pin
                          |SLCT_01_Pin|SLCT_02_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// Memory alocation managers
void resetMap(void){
	for (int i = 0; i < DIM; ++i){
		for (int j = 0; j < DIM; ++j){
			map[i][j] = 0;
		}
	}
}

// 8x8 Bit Manager
void infoManager(int value, int lineSelector){
	int line = 0, column = 0;

	for (int i = 7; i >= 0; --i){
		if (i == (lineSelector - 1)){
			for (int j = 7; j >= 0; --j){
				map[i][j] = (value >> j) & 1;
			}
		}
	}

	switch(lineSelector){
		case 1: line = 0x01;
				break;
		case 2: line = 0x02;
				break;
		case 3: line = 0x04;
				break;
		case 4: line = 0x08;
				break;
		case 5: line = 0x10;
				break;
		case 6: line = 0x20;
				break;
		case 7: line = 0x40;
				break;
		case 8: line = 0x80;
				break;
	}

	switch(value){
		case 1: column = 0xFE;
				break;
		case 2: column = 0xFC;
				break;
		case 3: column = 0xF3;
				break;
		case 4: column = 0xE7;
				break;
		case 5: column = 0xCF;
				break;
		case 6: column = 0x9F;
				break;
		case 7: column = 0x3F;
				break;
		case 8: column = 0x7F;
				break;
	}

	informationlLine(line);
	informationCarrer(column);
}

void informationlLine(int line){
	HAL_GPIO_WritePin(SLCT_01_GPIO_Port, SLCT_01_Pin, (line >> 0) & 1);
	HAL_GPIO_WritePin(SLCT_02_GPIO_Port, SLCT_02_Pin, (line >> 1) & 1);
	HAL_GPIO_WritePin(SLCT_03_GPIO_Port, SLCT_03_Pin, (line >> 2) & 1);
	HAL_GPIO_WritePin(SLCT_04_GPIO_Port, SLCT_04_Pin, (line >> 3) & 1);
	HAL_GPIO_WritePin(SLCT_05_GPIO_Port, SLCT_05_Pin, (line >> 4) & 1);
	HAL_GPIO_WritePin(SLCT_06_GPIO_Port, SLCT_06_Pin, (line >> 5) & 1);
	HAL_GPIO_WritePin(SLCT_07_GPIO_Port, SLCT_07_Pin, (line >> 6) & 1);
	HAL_GPIO_WritePin(SLCT_08_GPIO_Port, SLCT_08_Pin, (line >> 7) & 1);
}

void informationCarrer(int value){
	data.P0 = (value >> 0) & 1;
	data.P1 = (value >> 1) & 1;
	data.P2 = (value >> 2) & 1;
	data.P3 = (value >> 3) & 1;
	data.P4 = (value >> 4) & 1;
	data.P5 = (value >> 5) & 1;
	data.P6 = (value >> 6) & 1;
	data.P7 = (value >> 7) & 1;

	HAL_GPIO_WritePin(SLCTRED_01_GPIO_Port, SLCTRED_01_Pin, data.P0);
	HAL_GPIO_WritePin(SLCTRED_02_GPIO_Port, SLCTRED_02_Pin, data.P1);
	HAL_GPIO_WritePin(SLCTRED_03_GPIO_Port, SLCTRED_03_Pin, data.P2);
	HAL_GPIO_WritePin(SLCTRED_04_GPIO_Port, SLCTRED_04_Pin, data.P3);
	HAL_GPIO_WritePin(SLCTRED_05_GPIO_Port, SLCTRED_05_Pin, data.P4);
	HAL_GPIO_WritePin(SLCTRED_06_GPIO_Port, SLCTRED_06_Pin, data.P5);
	HAL_GPIO_WritePin(SLCTRED_07_GPIO_Port, SLCTRED_07_Pin, data.P6);
	HAL_GPIO_WritePin(SLCTRED_08_GPIO_Port, SLCTRED_08_Pin, data.P7);
}

void verifyDirection(void){
	int columValueAdd = 0, lineValueAdd = 1;
	HAL_ADC_Start(&hadc);

	for (int i = 0; i < 2; ++i){
	  HAL_ADC_PollForConversion(&hadc, 100);
	  if (i == 0) axisY = HAL_ADC_GetValue(&hadc);
	  else axisX = HAL_ADC_GetValue(&hadc);
	}

	if (axisX <= 70)          strcpy(dir, "LEFT");
	else if ((axisX >= 2900) && (axisX <= 3000))   strcpy(dir, "RIGHT");
	else if (axisY > 4000)   strcpy(dir, "UP");
	else if (axisY <= 70)     strcpy(dir, "DOWN");

	if (strcmp(dir, "UP") == 0 && lineValueAdd != 0) {
	  lineSelect -= lineValueAdd;
	  columValueAdd = 0;
	}
	else if (strcmp(dir, "DOWN") == 0 && lineValueAdd != 0) {
	  lineSelect += lineValueAdd;
	  columValueAdd = 0;
	} else columValueAdd = 1;

	if (strcmp(dir, "RIGHT") == 0 && columValueAdd != 0) {
	  columSelect += columValueAdd;
	  lineValueAdd = 0;
	}
	else if (strcmp(dir, "LEFT") == 0 && columValueAdd != 0) {
	  columSelect -= columValueAdd;
	  lineValueAdd = 0;
	} else lineValueAdd = 1;


	if      (lineSelect >= 9) lineSelect = 1;
	else if (lineSelect <= 0) lineSelect = 8;

	if      (columSelect >= 9) columSelect = 1;
	else if (columSelect <= 0) columSelect = 8;
	HAL_Delay(10);

	HAL_ADC_Stop(&hadc);
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
