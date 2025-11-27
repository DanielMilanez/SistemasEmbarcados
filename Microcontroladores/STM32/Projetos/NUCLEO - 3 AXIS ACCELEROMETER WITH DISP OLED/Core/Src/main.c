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
#include "ssd1306_fonts.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct{
	int second, minutes, hours;
	int day, date, month, year;
}DS3231_TimesTypedef;

typedef enum{
	BCD_TO_DEC = 0x00,
	DEC_TO_BCD = 0x01
}DS3231_ConvertTypedef;

typedef enum {
	CLOCKWISE,
	COUNTERCLOCKWISE
}StepMotor_Typedef;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADRS_DS3231 (0x68 << 1)

#define ADRS_SECONDS 0x00
#define ADRS_MINUTES 0x01
#define ADRS_HOURS   0x02
#define ADRS_DAY	 0x03
#define ADRS_DATE 	 0x04
#define ADRS_MONTH 	 0x05
#define ADRS_YEAR    0x06

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

// Bitmap
const unsigned char bandeira_DF_128x64 [] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x07, 0x80, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x0f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x07, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x07, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x0f, 0x80, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1d, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x18, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xe0, 0x3f, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x98, 0x3f, 0xe0, 0x3f, 0xf0, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x98, 0x7f, 0xc0, 0x1f, 0xf8, 0xef, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x98, 0x7f, 0xc0, 0x1f, 0xf0, 0xef, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x88, 0x3f, 0xe0, 0x3f, 0xe0, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x10, 0x40, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x18, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1d, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x0f, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x07, 0x80, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x07, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x0f, 0x80, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x0f, 0x80, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x07, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x02, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0};

HAL_StatusTypeDef status;
DS3231_TimesTypedef time, time_read;
int32_t encoderValue, lastValue, flag, ang;

int8_t dir, swEncoder, swPresence, press, cliques, return_motor;

uint32_t window, window_time, count, passTime;

uint16_t noiseValue, times, wait_time = 500, send;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
static void MX_ADC_Init(void);
/* USER CODE BEGIN PFP */
HAL_StatusTypeDef DS3231_StartUp(void){
	HAL_StatusTypeDef verify;
	verify = HAL_I2C_IsDeviceReady(&hi2c1, ADRS_DS3231, 4, HAL_MAX_DELAY);
	return verify;
}

int Converter(DS3231_ConvertTypedef mode, int num){
	int result;

	switch(mode){
		case BCD_TO_DEC: result = (int)((num / 16 * 10) + (num % 16)); break;
		case DEC_TO_BCD: result = (int)((num / 10 * 16) + (num % 10)); break;
	}

	return result;
}

void DS3231_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds){
  uint8_t datin[2];

  datin[0] = 0x00;
  datin[1] = Converter(DEC_TO_BCD, seconds);
  HAL_I2C_Master_Transmit(&hi2c1, ADRS_DS3231, datin, 2, 100);

  datin[0] = 0x01;
  datin[1] = Converter(DEC_TO_BCD, minutes);
  HAL_I2C_Master_Transmit(&hi2c1, ADRS_DS3231, datin, 2, 100);

  datin[0] = 0x02;
  datin[1] = Converter(DEC_TO_BCD, hours);
  HAL_I2C_Master_Transmit(&hi2c1, ADRS_DS3231, datin, 2, 100);
}

void DS3231_SetDate(uint8_t date, uint8_t month, uint8_t year){
  uint8_t datin[2];

  datin[0] = 0x04;
  datin[1] = Converter(DEC_TO_BCD, date);
  HAL_I2C_Master_Transmit(&hi2c1, ADRS_DS3231, datin, 2, 100);

  datin[0] = 0x05;
  datin[1] = Converter(DEC_TO_BCD, month);
  HAL_I2C_Master_Transmit(&hi2c1, ADRS_DS3231, datin, 2, 100);

  datin[0] = 0x06;
  datin[1] = Converter(DEC_TO_BCD, year);
  HAL_I2C_Master_Transmit(&hi2c1, ADRS_DS3231, datin, 2, 100);
}

void DS3231_GetValues(void){
	uint8_t date[7];

	HAL_I2C_Mem_Read(&hi2c1, ADRS_DS3231, 0x00, 1, date, 7, HAL_MAX_DELAY);

	time_read.second  = Converter(BCD_TO_DEC, date[0]);
	time_read.minutes = Converter(BCD_TO_DEC, date[1]);
	time_read.hours   = Converter(BCD_TO_DEC, date[2]);
	time_read.day     = Converter(BCD_TO_DEC, date[3]);
	time_read.date    = Converter(BCD_TO_DEC, date[4]);
	time_read.month   = Converter(BCD_TO_DEC, date[5]);
	time_read.year    = Converter(BCD_TO_DEC, date[6]);

	HAL_Delay(5);
}

void ENCODER_Interpreter(void){
	encoderValue = TIM2->CNT;

	if(encoderValue < lastValue) dir = -1;
	else if (encoderValue > lastValue) dir = 1;
	else if (encoderValue == lastValue) dir = 0;

	lastValue = encoderValue;
}

void Keyboard_check(void){
	swEncoder  = !(HAL_GPIO_ReadPin(SW_ENCODER_GPIO_Port, SW_ENCODER_Pin));
	swPresence = !(HAL_GPIO_ReadPin(PRESENCE_SENSOR_GPIO_Port, PRESENCE_SENSOR_Pin));

	uint32_t now = HAL_GetTick();

	if((now - passTime) > 20){
		if(swEncoder) {
			if(!window){
				window = 1;
				window_time = now;
				cliques = 1;
			}

			else {
				if((now - window_time) < wait_time) cliques++;
				else {
					window_time = now;
					cliques = 1;
				}
			}
		}

		while(!(HAL_GPIO_ReadPin(SW_ENCODER_GPIO_Port, SW_ENCODER_Pin)));
	}

	passTime = now;
}

void NoiseSensor(void){
	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, 100);
	noiseValue = HAL_ADC_GetValue(&hadc);
	HAL_ADC_Stop(&hadc);
}

void NoiseInterpreter(void){
	if(noiseValue < 300) {
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_RESET);
	}

	if(noiseValue > 300 && noiseValue < 400) {
			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_RESET);
		}

	if(noiseValue > 400 && noiseValue < 500) {
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_RESET);
	}

	if(noiseValue > 500 && noiseValue < 600) {
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_RESET);
	}

	if(noiseValue > 600 && noiseValue < 700) {
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_RESET);
	}

	if(noiseValue > 700 && noiseValue < 800) {
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_RESET);
	}


	if(noiseValue > 800 && noiseValue < 900) {
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_RESET);
	}

	if(noiseValue > 900 && noiseValue < 1000) {
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_RESET);
	}

	if(noiseValue > 1000 && noiseValue < 1100) {
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_RESET);
	}

	if(noiseValue > 1100 && noiseValue < 1200) {
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_RESET);
	}

	if(noiseValue > 1200) {
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_SET);
	}
}
//
//void StepClockwise(void){
//	HAL_GPIO_WritePin(BOB01_GPIO_Port, BOB01_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(BOB02_GPIO_Port, BOB02_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB03_GPIO_Port, BOB03_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB04_GPIO_Port, BOB04_Pin, GPIO_PIN_RESET);
//	HAL_Delay(10);
//
//	HAL_GPIO_WritePin(BOB01_GPIO_Port, BOB01_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB02_GPIO_Port, BOB02_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(BOB03_GPIO_Port, BOB03_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB04_GPIO_Port, BOB04_Pin, GPIO_PIN_RESET);
//	HAL_Delay(10);
//
//	HAL_GPIO_WritePin(BOB01_GPIO_Port, BOB01_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB02_GPIO_Port, BOB02_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB03_GPIO_Port, BOB03_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(BOB04_GPIO_Port, BOB04_Pin, GPIO_PIN_RESET);
//	HAL_Delay(10);
//
//	HAL_GPIO_WritePin(BOB01_GPIO_Port, BOB01_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB02_GPIO_Port, BOB02_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB03_GPIO_Port, BOB03_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB04_GPIO_Port, BOB04_Pin, GPIO_PIN_SET);
//	HAL_Delay(10);
//}

//void StepCounterClockwise(void){
//	HAL_GPIO_WritePin(BOB01_GPIO_Port, BOB01_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB02_GPIO_Port, BOB02_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB03_GPIO_Port, BOB03_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB04_GPIO_Port, BOB04_Pin, GPIO_PIN_SET);
//	HAL_Delay(10);
//
//	HAL_GPIO_WritePin(BOB01_GPIO_Port, BOB01_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB02_GPIO_Port, BOB02_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB03_GPIO_Port, BOB03_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(BOB04_GPIO_Port, BOB04_Pin, GPIO_PIN_RESET);
//	HAL_Delay(10);
//
//	HAL_GPIO_WritePin(BOB01_GPIO_Port, BOB01_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB02_GPIO_Port, BOB02_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(BOB03_GPIO_Port, BOB03_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB04_GPIO_Port, BOB04_Pin, GPIO_PIN_RESET);
//	HAL_Delay(10);
//
//	HAL_GPIO_WritePin(BOB01_GPIO_Port, BOB01_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(BOB02_GPIO_Port, BOB02_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB03_GPIO_Port, BOB03_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(BOB04_GPIO_Port, BOB04_Pin, GPIO_PIN_RESET);
//	HAL_Delay(10);
//}

void SendMotor(void){
//	static int atual_pos;
//	int32_t target_steps, direction, delta;
//
//	target_steps = (int32_t)(ang / 360 * 4096);
//	delta = target_steps - atual_pos;
//
//	if (delta >= 0) direction = CLOCKWISE;
//	else  {
//		direction = COUNTERCLOCKWISE;
//		delta = -delta;
//	}

//	for(int i = 0; i < delta; ++i){
//		if(direction == CLOCKWISE) StepClockwise();
//		else StepCounterClockwise();
//	}

//	atual_pos = target_steps;
}
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
  MX_TIM2_Init();
  MX_ADC_Init();
  /* USER CODE BEGIN 2 */

  time.second = 0;
  time.minutes = 20;
  time.hours = 20;

  time.date = 10;
  time.month = 9;
  time.year = 25;

  status = DS3231_StartUp();
  DS3231_SetTime(20, 06, 0);
  DS3231_SetDate(9, 9, 25);

  ssd1306_Init();

  ssd1306_Fill(White);
  ssd1306_SetCursor(26, 22);
  ssd1306_WriteString("SELETIVA WS", Font_7x10, Black);
  ssd1306_SetCursor(26, 32);
  ssd1306_WriteString("   2025", Font_7x10, Black);
  ssd1306_UpdateScreen();
  HAL_Delay(3000);

  ssd1306_Fill(Black);
  ssd1306_DrawBitmap(0, 0, bandeira_DF_128x64, 128, 64, White);
  ssd1306_UpdateScreen();
  HAL_Delay(3000);

  char buf_time[100];
  char buf_date[100];
  char buf_message[100];

  char hours[6];
  char seconds[6];
  char minutes[6];
  char date[6];
  char month[6];
  char year[6];

  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {

	  Keyboard_check();

	  if(swPresence){
		  sprintf(buf_message, "Mixer");
		  ssd1306_Fill(White);
		  ssd1306_SetCursor(32, 22);
		  ssd1306_WriteString(buf_message, Font_7x10, Black);
		  ssd1306_UpdateScreen();
	  } else {
		  HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LD8_GPIO_Port, LD8_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LD9_GPIO_Port, LD9_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LD10_GPIO_Port, LD10_Pin, GPIO_PIN_RESET);
	  }

	  while(swPresence){
		  NoiseSensor();
		  NoiseInterpreter();
		  Keyboard_check();
	  }

	  if(swEncoder){
		  if(cliques == 2){
			  cliques = 1;
			  wait_time = 500;

			  while(cliques == 1){
				  Keyboard_check();
				  ENCODER_Interpreter();
//				  MotorValue();

				  if(swEncoder) {
					  send = 2;
					  cliques = 1;
					  swEncoder = 0;
					  int8_t  op = 1;

					  while(send == 2) {
						  Keyboard_check();
						  ENCODER_Interpreter();

						  op -= dir;

						  if(op >= 2) op = 0;
						  if(op <= -1) op = 1;

						  sprintf(buf_message, "Deseja enviar?");
						  ssd1306_Fill(White);
						  ssd1306_SetCursor(10, 22);
						  ssd1306_WriteString(buf_message, Font_7x10, Black);

						  if(op == 1) {
							  ssd1306_SetCursor(10, 35);
							  sprintf(buf_message, "> SIM    NAO");
						  }

						  else if(op == 0) {
							  ssd1306_SetCursor(10, 35);
							  sprintf(buf_message, "  SIM  > NAO");
						  }

						  ssd1306_WriteString(buf_message, Font_7x10, Black);
						  ssd1306_UpdateScreen();

						  if(op == 1 && swEncoder == 1) send = 1;
						  else if (op == 0 && swEncoder == 1) send = 0;
					  }

					  if(send == 1) {
						  SendMotor();
						  sprintf(buf_message, "Enviando...");
						  ssd1306_Fill(White);
						  ssd1306_SetCursor(10, 22);
						  ssd1306_WriteString(buf_message, Font_7x10, Black);
						  ssd1306_UpdateScreen();
						  break;
					  }

					  else if(send == 0) {
						  sprintf(buf_message, "Cancelando...");
						  ssd1306_Fill(White);
						  ssd1306_SetCursor(10, 22);
						  ssd1306_WriteString(buf_message, Font_7x10, Black);
						  ssd1306_UpdateScreen();

						  HAL_Delay(2000);
						  break;
					  }
				  }

				  sprintf(buf_message, "Controle motor");
				  ssd1306_Fill(White);
				  ssd1306_SetCursor(10, 22);
				  ssd1306_WriteString(buf_message, Font_7x10, Black);

				  ssd1306_SetCursor(50, 35);
				  sprintf(buf_message, "Ang: %ld", ang);
				  ssd1306_WriteString(buf_message, Font_7x10, Black);
				  ssd1306_UpdateScreen();
			  }

			  wait_time = 500;
		  }
	  }

	  DS3231_GetValues();


	  if(time_read.hours <= 9) sprintf(hours, "0%d", time_read.hours);
	  else sprintf(hours, "%d", time_read.hours);

	  if(time_read.minutes <= 9) sprintf(minutes, "0%d", time_read.minutes);
	  else sprintf(minutes, "%d", time_read.minutes);

	  if(time_read.second <= 9) sprintf(seconds, "0%d", time_read.second);
	  else sprintf(seconds, "%d", time_read.second);

	  if(time_read.date <= 9) sprintf(date, "0%d", time_read.date);
	  else sprintf(date, "%d", time_read.date);

	  if(time_read.month <= 9) sprintf(month, "0%d", time_read.month);
	  else sprintf(month, "%d", time_read.month);

	  if(time_read.year <= 9) sprintf(year, "0%d", time_read.year);
	  else sprintf(year, "%d", time_read.year);

	  sprintf(buf_time, "%s:%s:%s", hours, minutes, seconds);
	  sprintf(buf_date, "%s/%s/%s", date, month, year);

	  ssd1306_Fill(White);
	  ssd1306_SetCursor(30, 22);
	  ssd1306_WriteString(buf_time, Font_7x10, Black);
	  ssd1306_SetCursor(30, 32);
	  ssd1306_WriteString(buf_date, Font_7x10, Black);
	  ssd1306_UpdateScreen();
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
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

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
  hi2c1.Init.Timing = 0x00201D2B;
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 8;
  sConfig.IC2Polarity = TIM_ICPOLARITY_FALLING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 8;
  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  HAL_GPIO_WritePin(GPIOB, LD7_Pin|LD10_Pin|LD8_Pin|LD9_Pin
                          |LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LD4_Pin|LD2_Pin|LD1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD6_Pin|LD5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PRESENCE_SENSOR_Pin */
  GPIO_InitStruct.Pin = PRESENCE_SENSOR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PRESENCE_SENSOR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SW_ENCODER_Pin */
  GPIO_InitStruct.Pin = SW_ENCODER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW_ENCODER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD7_Pin LD10_Pin LD8_Pin LD9_Pin
                           LD3_Pin */
  GPIO_InitStruct.Pin = LD7_Pin|LD10_Pin|LD8_Pin|LD9_Pin
                          |LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD2_Pin LD1_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD2_Pin|LD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LD6_Pin LD5_Pin */
  GPIO_InitStruct.Pin = LD6_Pin|LD5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
