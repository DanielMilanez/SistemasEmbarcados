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
typedef struct {
	unsigned P0: 1,
			 P1: 1,
			 P2: 1,
			 P3: 1,
			 P4: 1,
			 P5: 1,
			 P6: 1,
			 P7: 1;
}PINOUT;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

/* USER CODE BEGIN PV */
PINOUT PORT;
uint16_t AxisX, AxisY;

char State[10] = "UP";

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
/* USER CODE BEGIN PFP */
void Direction(void);
void InfoManager(uint8_t data, uint8_t mode);
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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
	  Direction();
	  InfoManager(0x80, 0);
	  InfoManager(0xE7, 1);
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
  HAL_GPIO_WritePin(GPIOA, SLCT_03_Pin|SLCT_04_Pin|SLCT_05_Pin|SLCT_08_Pin
                          |SLCTRED_05_Pin|SLCTRED_04_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SLCTRED_03_Pin|SLCTRED_02_Pin|SLCT_07_Pin|SLCTRED_01_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SLCTRED_08_Pin|SLCTRED_07_Pin|SLCTRED_06_Pin|SLCT_06_Pin
                          |SLCT_01_Pin|SLCT_02_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SLCT_03_Pin SLCT_04_Pin SLCT_05_Pin SLCT_08_Pin
                           SLCTRED_05_Pin SLCTRED_04_Pin */
  GPIO_InitStruct.Pin = SLCT_03_Pin|SLCT_04_Pin|SLCT_05_Pin|SLCT_08_Pin
                          |SLCTRED_05_Pin|SLCTRED_04_Pin;
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

  /*Configure GPIO pin : SW_BTN_Pin */
  GPIO_InitStruct.Pin = SW_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(SW_BTN_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void Direction(void) {
	HAL_ADC_Start(&hadc);
		for (int i = 0; i < 2; ++i){
			HAL_ADC_PollForConversion(&hadc, 100);
			if (i == 0) AxisY = HAL_ADC_GetValue(&hadc);
			else AxisX = HAL_ADC_GetValue(&hadc);
		}

		if (AxisX == 2940) strcpy(State, "LEFT");
		else if (AxisX <= 60) strcpy(State, "RIGTH");

		if (AxisY <= 60) strcpy(State, "UP");
		else if (AxisY >= 4000) strcpy(State, "DOWN");
	HAL_ADC_Stop(&hadc);
}

void InfoManager(uint8_t data, uint8_t mode){
	PORT.P0 = (data >> 0) & 1;
	PORT.P1 = (data >> 1) & 1;
	PORT.P2 = (data >> 2) & 1;
	PORT.P3 = (data >> 3) & 1;
	PORT.P4 = (data >> 4) & 1;
	PORT.P5 = (data >> 5) & 1;
	PORT.P6 = (data >> 6) & 1;
	PORT.P7 = (data >> 7) & 1;

	if (!mode) {
		HAL_GPIO_WritePin(SLCT_01_GPIO_Port, SLCT_01_Pin, PORT.P0);
		HAL_GPIO_WritePin(SLCT_02_GPIO_Port, SLCT_02_Pin, PORT.P1);
		HAL_GPIO_WritePin(SLCT_03_GPIO_Port, SLCT_03_Pin, PORT.P2);
		HAL_GPIO_WritePin(SLCT_04_GPIO_Port, SLCT_04_Pin, PORT.P3);
		HAL_GPIO_WritePin(SLCT_05_GPIO_Port, SLCT_05_Pin, PORT.P4);
		HAL_GPIO_WritePin(SLCT_06_GPIO_Port, SLCT_06_Pin, PORT.P5);
		HAL_GPIO_WritePin(SLCT_07_GPIO_Port, SLCT_07_Pin, PORT.P6);
		HAL_GPIO_WritePin(SLCT_08_GPIO_Port, SLCT_08_Pin, PORT.P7);

	} else {
		HAL_GPIO_WritePin(SLCTRED_01_GPIO_Port, SLCTRED_01_Pin, PORT.P0);
		HAL_GPIO_WritePin(SLCTRED_02_GPIO_Port, SLCTRED_02_Pin, PORT.P1);
		HAL_GPIO_WritePin(SLCTRED_03_GPIO_Port, SLCTRED_03_Pin, PORT.P2);
		HAL_GPIO_WritePin(SLCTRED_04_GPIO_Port, SLCTRED_04_Pin, PORT.P3);
		HAL_GPIO_WritePin(SLCTRED_05_GPIO_Port, SLCTRED_05_Pin, PORT.P4);
		HAL_GPIO_WritePin(SLCTRED_06_GPIO_Port, SLCTRED_06_Pin, PORT.P5);
		HAL_GPIO_WritePin(SLCTRED_07_GPIO_Port, SLCTRED_07_Pin, PORT.P6);
		HAL_GPIO_WritePin(SLCTRED_08_GPIO_Port, SLCTRED_08_Pin, PORT.P7);
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
