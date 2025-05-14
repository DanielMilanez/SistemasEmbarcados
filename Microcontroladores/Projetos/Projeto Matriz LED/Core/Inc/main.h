/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BLUE_BTN_Pin GPIO_PIN_13
#define BLUE_BTN_GPIO_Port GPIOC
#define SELETOR_03_Pin GPIO_PIN_5
#define SELETOR_03_GPIO_Port GPIOA
#define SELETOR_04_Pin GPIO_PIN_6
#define SELETOR_04_GPIO_Port GPIOA
#define SELETOR_05_Pin GPIO_PIN_7
#define SELETOR_05_GPIO_Port GPIOA
#define COLUMN_RED_08_Pin GPIO_PIN_4
#define COLUMN_RED_08_GPIO_Port GPIOC
#define COLUMN_RED_03_Pin GPIO_PIN_5
#define COLUMN_RED_03_GPIO_Port GPIOC
#define COLUMN_RED_07_Pin GPIO_PIN_11
#define COLUMN_RED_07_GPIO_Port GPIOB
#define COLUMN_RED_06_Pin GPIO_PIN_12
#define COLUMN_RED_06_GPIO_Port GPIOB
#define COLUMN_RED_02_Pin GPIO_PIN_6
#define COLUMN_RED_02_GPIO_Port GPIOC
#define SELETOR_07_Pin GPIO_PIN_7
#define SELETOR_07_GPIO_Port GPIOC
#define COLUMN_RED_01_Pin GPIO_PIN_8
#define COLUMN_RED_01_GPIO_Port GPIOC
#define SELETOR_08_Pin GPIO_PIN_9
#define SELETOR_08_GPIO_Port GPIOA
#define COLUMN_RED_05_Pin GPIO_PIN_11
#define COLUMN_RED_05_GPIO_Port GPIOA
#define COLUMN_RED_04_Pin GPIO_PIN_12
#define COLUMN_RED_04_GPIO_Port GPIOA
#define SELETOR_06_Pin GPIO_PIN_6
#define SELETOR_06_GPIO_Port GPIOB
#define SELETOR_01_Pin GPIO_PIN_8
#define SELETOR_01_GPIO_Port GPIOB
#define SELETOR_02_Pin GPIO_PIN_9
#define SELETOR_02_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
