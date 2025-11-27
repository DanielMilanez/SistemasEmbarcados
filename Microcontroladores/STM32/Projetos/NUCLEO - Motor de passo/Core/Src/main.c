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
#include "stdlib.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum{
	CLOCKWISE = 0x00,
	COUNTERCLOCKWISE = 0x01,
	STOPED
}StepMotor_Typedef;

typedef enum{
	DEC_TO_BCD = 0x00,
	BCD_TO_DEC = 0x01
}ConverterType_Typedef;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_STEPS (513)
#define MAX_ANG (360)
#define FLASH_ADRS (uint32_t *)(0x0800FF80)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */
float targ_ang, count;
uint16_t ang_atual;
StepMotor_Typedef direction;
FLASH_EraseInitTypeDef clearMem;
uint16_t adc_value[2];
uint8_t zero_set;

uint32_t atual_time, bref_time;
float x, y;
float angDeg;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);
static void MX_ADC_Init(void);
/* USER CODE BEGIN PFP */
void MOTOR_Control(void);
void AngInterpreter(void);
void SaveMem(uint16_t data);
void MOTOR_StepClockwise(void);
void MOTOR_StepCounterClockwise(void);
void Keyboard_check(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint32_t Converter(ConverterType_Typedef type_of_convertion, uint32_t number_to_convert);
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
  MX_ADC_Init();
  /* USER CODE BEGIN 2 */

//  ang_atual = *FLASH_ADRS;
//  if(ang_atual >= 360) ang_atual = 0;
//  targ_ang = 0;
//  MOTOR_Control();
//  SaveMem(ang_atual);

//  uint8_t blueSwitch;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
	HAL_ADC_Start(&hadc);
	for(int i = 0; i < 2; i++){
		HAL_ADC_PollForConversion(&hadc, 100);
		if(i == 0) adc_value[0] = HAL_ADC_GetValue(&hadc);
		else adc_value[1] = HAL_ADC_GetValue(&hadc);
	}
	HAL_ADC_Stop(&hadc);
//	  blueSwitch = !(HAL_GPIO_ReadPin(BLUESW_GPIO_Port, BLUESW_Pin));
//	  AngInterpreter();

//	  if(blueSwitch){
//		  while(!(HAL_GPIO_ReadPin(BLUESW_GPIO_Port, BLUESW_Pin)));
//		  SaveMem(ang_atual);
//	  }
//
//	  targ_ang = angDeg;
//	  MOTOR_Control();
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
  htim6.Init.Period = 65535;
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, BOB3_Pin|BOB4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, BOB2_Pin|BOB1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BLUESW_Pin */
  GPIO_InitStruct.Pin = BLUESW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BLUESW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BOB3_Pin BOB4_Pin */
  GPIO_InitStruct.Pin = BOB3_Pin|BOB4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ZERO_SET_Pin */
  GPIO_InitStruct.Pin = ZERO_SET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ZERO_SET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BOB2_Pin BOB1_Pin */
  GPIO_InitStruct.Pin = BOB2_Pin|BOB1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void MOTOR_Control(void){
	int step, diff;

	diff = (int)(targ_ang - ang_atual + 540) % 360 - 180;
	step = abs(diff) * MAX_STEPS / MAX_ANG;

	if(diff == 0) direction = STOPED;
	else if(diff > 0) direction = CLOCKWISE;
	else direction = COUNTERCLOCKWISE;

	for(int i = 0; i < step; ++i){
		if(direction == CLOCKWISE) MOTOR_StepClockwise();
		else if (direction == COUNTERCLOCKWISE) MOTOR_StepCounterClockwise();
		else break;
	}

	ang_atual = (int)((ang_atual + diff + 360) % 360);

}
void MOTOR_StepClockwise(void){
	HAL_GPIO_WritePin(BOB1_GPIO_Port, BOB1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BOB2_GPIO_Port, BOB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB3_GPIO_Port, BOB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB4_GPIO_Port, BOB4_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);

	HAL_GPIO_WritePin(BOB1_GPIO_Port, BOB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB2_GPIO_Port, BOB2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BOB3_GPIO_Port, BOB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB4_GPIO_Port, BOB4_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);

	HAL_GPIO_WritePin(BOB1_GPIO_Port, BOB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB2_GPIO_Port, BOB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB3_GPIO_Port, BOB3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BOB4_GPIO_Port, BOB4_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);

	HAL_GPIO_WritePin(BOB1_GPIO_Port, BOB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB2_GPIO_Port, BOB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB3_GPIO_Port, BOB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB4_GPIO_Port, BOB4_Pin, GPIO_PIN_SET);
	HAL_Delay(1);

	HAL_GPIO_WritePin(BOB1_GPIO_Port, BOB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB2_GPIO_Port, BOB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB3_GPIO_Port, BOB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB4_GPIO_Port, BOB4_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}
void MOTOR_StepCounterClockwise(void){
	HAL_GPIO_WritePin(BOB1_GPIO_Port, BOB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB2_GPIO_Port, BOB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB3_GPIO_Port, BOB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB4_GPIO_Port, BOB4_Pin, GPIO_PIN_SET);
	HAL_Delay(1);

	HAL_GPIO_WritePin(BOB1_GPIO_Port, BOB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB2_GPIO_Port, BOB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB3_GPIO_Port, BOB3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BOB4_GPIO_Port, BOB4_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);

	HAL_GPIO_WritePin(BOB1_GPIO_Port, BOB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB2_GPIO_Port, BOB2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BOB3_GPIO_Port, BOB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB4_GPIO_Port, BOB4_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);

	HAL_GPIO_WritePin(BOB1_GPIO_Port, BOB1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BOB2_GPIO_Port, BOB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB3_GPIO_Port, BOB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB4_GPIO_Port, BOB4_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);

	HAL_GPIO_WritePin(BOB1_GPIO_Port, BOB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB2_GPIO_Port, BOB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB3_GPIO_Port, BOB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BOB4_GPIO_Port, BOB4_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}

void AngInterpreter(void){
	uint16_t ref = 4095;

	if(adc_value[0] > 3000 && adc_value[0] < 3400) y = y;
	else if (adc_value[1] > 3000 && adc_value[1] < 3200) x = x;
	else if (adc_value[0] > 3400) y = (adc_value[0] * 5 ) / ref;
	else if (adc_value[0] < 3000) y = -(adc_value[0] * 5 ) / ref;
	else if (adc_value[1] > 3200) x = (adc_value[1] * 5 ) / ref;
	else if (adc_value[1] < 3000) x = (adc_value[1] * 5 ) / ref;

    float angRad = atan2(y, x);
	angDeg = angRad * (180.0 / M_PI);
	if (angDeg < 0) angDeg += 360.0;
}

uint32_t Converter(ConverterType_Typedef type_of_convertion, uint32_t number_to_convert){
	switch(type_of_convertion){
		case BCD_TO_DEC:
			return (number_to_convert / 16 * 10) + (number_to_convert % 16);
			break;

		case DEC_TO_BCD:
			return (number_to_convert / 10 * 16) + (number_to_convert % 10);
			break;
	}

	return 0;
}

void Keyboard_check(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	zero_set = !(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));

	if(zero_set) {
		x = 0;
		y = 0;
	}

	HAL_ADC_Start(&hadc);
	for(int i = 0; i < 2; i++){
		HAL_ADC_PollForConversion(&hadc, 100);
		if(i == 0) adc_value[0] = HAL_ADC_GetValue(&hadc);
		else adc_value[1] = HAL_ADC_GetValue(&hadc);
	}
	HAL_ADC_Stop(&hadc);


}

void SaveMem(uint16_t data){
	uint32_t PagErr;

	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();

	clearMem.TypeErase = FLASH_TYPEERASE_PAGES;
	clearMem.PageAddress = 0x0800FF80;
	clearMem.NbPages = 1;

	HAL_FLASHEx_Erase(&clearMem, &PagErr);

	HAL_FLASH_Program(FLASH_TYPEPROGRAMDATA_HALFWORD, 0x0800FF80, data);
	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
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
