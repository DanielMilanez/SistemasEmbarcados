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
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef enum {
	temp_res_14_bit = 0,
	temp_res_11_bit = 1
}TR;

typedef enum {
	humid_res_14_bit = 0,
	humid_res_11_bit = 1,
	humid_res_8_bit = 2
}HR;

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
#define DATA 1

#define HDC_1080_ADRS 0x40
#define HDC_CONFIG_REGS 0x02
#define HDC_TEMP_REG_ADRS 0x00
#define HDC_HUMID_REG_ADRS 0x01
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */
BIT PORT;
float temp;
char buffer[20];
uint16_t reg = 0;
uint8_t humi, read_data[2];

uint8_t customChar[] = {0x00, 0x0E, 0x0A, 0x0E, 0x00, 0x00, 0x00, 0x00};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void LCD_START_UP(void);
void LCD_SEND_MESSAGE(char * message);
void LCD_DATA_MANAGER(uint8_t data, uint8_t state);
void LCD_ADD_CHAR(uint8_t locale, uint8_t * customChar);

void HDC1080_INIT(I2C_HandleTypeDef * HI2C_X, TR temp_resolution, HR humid_resolution);
void HDC1080_READ(I2C_HandleTypeDef * HI2C_X, float *temperature, uint8_t *humidy);
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
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  LCD_START_UP();
  LCD_ADD_CHAR(0, customChar);
  HDC1080_INIT(&hi2c1, temp_res_14_bit, humid_res_14_bit);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  LCD_DATA_MANAGER(0x83, INSTRUCTION);
	  LCD_SEND_MESSAGE("SENSOR HDC1080");

	  HDC1080_READ(&hi2c1, &temp, &humi);

	  LCD_DATA_MANAGER(0x94, INSTRUCTION);
	  sprintf(buffer, "TEMP: %.2f", temp);
	  LCD_SEND_MESSAGE(buffer);

	  LCD_DATA_MANAGER(0, DATA);
	  LCD_SEND_MESSAGE("C");

	  LCD_DATA_MANAGER(0xD4, INSTRUCTION);
	  sprintf(buffer, "HUMD: %d%%", humi);
	  LCD_SEND_MESSAGE(buffer);

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RS_Pin|RW_Pin|EN_Pin|DB7_Pin
                          |DB6_Pin|DB5_Pin|DB4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RS_Pin RW_Pin EN_Pin DB7_Pin
                           DB6_Pin DB5_Pin DB4_Pin */
  GPIO_InitStruct.Pin = RS_Pin|RW_Pin|EN_Pin|DB7_Pin
                          |DB6_Pin|DB5_Pin|DB4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void LCD_START_UP(void){
	LCD_DATA_MANAGER(0x33, INSTRUCTION);
	LCD_DATA_MANAGER(0x32, INSTRUCTION);
	LCD_DATA_MANAGER(0x28, INSTRUCTION);
	LCD_DATA_MANAGER(0x0C, INSTRUCTION);
	LCD_DATA_MANAGER(0x06, INSTRUCTION);

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

	HAL_GPIO_WritePin(DB4_GPIO_Port, DB4_Pin, PORT.P4);
	HAL_GPIO_WritePin(DB5_GPIO_Port, DB5_Pin, PORT.P5);
	HAL_GPIO_WritePin(DB6_GPIO_Port, DB6_Pin, PORT.P6);
	HAL_GPIO_WritePin(DB7_GPIO_Port, DB7_Pin, PORT.P7);

	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);

	HAL_GPIO_WritePin(DB4_GPIO_Port, DB4_Pin, PORT.P0);
	HAL_GPIO_WritePin(DB5_GPIO_Port, DB5_Pin, PORT.P1);
	HAL_GPIO_WritePin(DB6_GPIO_Port, DB6_Pin, PORT.P2);
	HAL_GPIO_WritePin(DB7_GPIO_Port, DB7_Pin, PORT.P3);

	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
	HAL_GPIO_TogglePin(EN_GPIO_Port, EN_Pin);
	HAL_Delay(1);
}
void LCD_ADD_CHAR(uint8_t locale, uint8_t * customChar){
	locale &= 0x7;
    LCD_DATA_MANAGER(0x40 | (locale << 3), INSTRUCTION);

	for (int i = 0; i < 8; ++i){
		LCD_DATA_MANAGER(customChar[i], DATA);
	}
}

void HDC1080_INIT(I2C_HandleTypeDef * HI2C_X, TR temp_resolution, HR humid_resolution){
	uint16_t config_reg_value = 0x1000;
	uint8_t data_sed[2];

	if (temp_resolution == temp_res_11_bit) config_reg_value |= (1 << 10);
	if (humid_resolution == humid_res_11_bit) config_reg_value |= (1 << 8);
	else if (humid_resolution == humid_res_8_bit) config_reg_value |= (1 << 9);

	data_sed[0] = (config_reg_value >> 8);
	data_sed[1] = (config_reg_value & 0x00FF);

	HAL_I2C_Mem_Write(HI2C_X, HDC_1080_ADRS << 1, config_reg_value, I2C_MEMADD_SIZE_8BIT, data_sed, 2, 1000);
}
void HDC1080_READ(I2C_HandleTypeDef * HI2C_X, float *temperature, uint8_t *humidity){
	uint8_t receive_data[4];
	uint16_t temp_x, humd_x;
	uint8_t send_data = HDC_TEMP_REG_ADRS;

	HAL_I2C_Master_Transmit(HI2C_X, HDC_1080_ADRS << 1, &send_data, 1, 1000);
	HAL_Delay(15);
	HAL_I2C_Master_Receive(HI2C_X, HDC_1080_ADRS << 1, receive_data, 4, 1000);

	temp_x = ((receive_data[0] << 8) | receive_data[1]);
	humd_x = ((receive_data[2] << 8) | receive_data[3]);

	*temperature = ((temp_x / 65536.0) *165.0) -40.0;
	*humidity = (uint8_t) ((humd_x / 65536.0) * 100.0);
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
