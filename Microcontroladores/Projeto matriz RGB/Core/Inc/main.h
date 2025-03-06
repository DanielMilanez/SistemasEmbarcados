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
#define RPIN_03_Pin GPIO_PIN_5
#define RPIN_03_GPIO_Port GPIOA
#define RPIN_04_Pin GPIO_PIN_6
#define RPIN_04_GPIO_Port GPIOA
#define LPIN_03_Pin GPIO_PIN_5
#define LPIN_03_GPIO_Port GPIOC
#define LPIN_09_Pin GPIO_PIN_1
#define LPIN_09_GPIO_Port GPIOB
#define LPIN_08_Pin GPIO_PIN_2
#define LPIN_08_GPIO_Port GPIOB
#define RPIN_09_Pin GPIO_PIN_10
#define RPIN_09_GPIO_Port GPIOB
#define LPIN_07_Pin GPIO_PIN_11
#define LPIN_07_GPIO_Port GPIOB
#define LPIN_06_Pin GPIO_PIN_12
#define LPIN_06_GPIO_Port GPIOB
#define LPIN_12_Pin GPIO_PIN_13
#define LPIN_12_GPIO_Port GPIOB
#define LPIN_11_Pin GPIO_PIN_14
#define LPIN_11_GPIO_Port GPIOB
#define LPIN_10_Pin GPIO_PIN_15
#define LPIN_10_GPIO_Port GPIOB
#define LPIN_02_Pin GPIO_PIN_6
#define LPIN_02_GPIO_Port GPIOC
#define RPIN_06_Pin GPIO_PIN_7
#define RPIN_06_GPIO_Port GPIOC
#define LPIN_01_Pin GPIO_PIN_8
#define LPIN_01_GPIO_Port GPIOC
#define RPIN_08_Pin GPIO_PIN_8
#define RPIN_08_GPIO_Port GPIOA
#define RPIN_07_Pin GPIO_PIN_9
#define RPIN_07_GPIO_Port GPIOA
#define LPIN_05_Pin GPIO_PIN_11
#define LPIN_05_GPIO_Port GPIOA
#define LPIN_04_Pin GPIO_PIN_12
#define LPIN_04_GPIO_Port GPIOA
#define RPIN_12_Pin GPIO_PIN_3
#define RPIN_12_GPIO_Port GPIOB
#define RPIN_10_Pin GPIO_PIN_4
#define RPIN_10_GPIO_Port GPIOB
#define RPIN_11_Pin GPIO_PIN_5
#define RPIN_11_GPIO_Port GPIOB
#define RPIN_05_Pin GPIO_PIN_6
#define RPIN_05_GPIO_Port GPIOB
#define RPIN_01_Pin GPIO_PIN_8
#define RPIN_01_GPIO_Port GPIOB
#define RPIN_02_Pin GPIO_PIN_9
#define RPIN_02_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
