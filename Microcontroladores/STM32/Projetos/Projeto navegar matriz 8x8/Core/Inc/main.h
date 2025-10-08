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
#define SLCT_03_Pin GPIO_PIN_5
#define SLCT_03_GPIO_Port GPIOA
#define SLCT_04_Pin GPIO_PIN_6
#define SLCT_04_GPIO_Port GPIOA
#define SLCT_05_Pin GPIO_PIN_7
#define SLCT_05_GPIO_Port GPIOA
#define SLCTRED_03_Pin GPIO_PIN_5
#define SLCTRED_03_GPIO_Port GPIOC
#define SLCTRED_08_Pin GPIO_PIN_2
#define SLCTRED_08_GPIO_Port GPIOB
#define SLCTRED_07_Pin GPIO_PIN_11
#define SLCTRED_07_GPIO_Port GPIOB
#define SLCTRED_06_Pin GPIO_PIN_12
#define SLCTRED_06_GPIO_Port GPIOB
#define SLCTRED_02_Pin GPIO_PIN_6
#define SLCTRED_02_GPIO_Port GPIOC
#define SLCT_07_Pin GPIO_PIN_7
#define SLCT_07_GPIO_Port GPIOC
#define SLCTRED_01_Pin GPIO_PIN_8
#define SLCTRED_01_GPIO_Port GPIOC
#define SW_BTN_Pin GPIO_PIN_8
#define SW_BTN_GPIO_Port GPIOA
#define SLCT_08_Pin GPIO_PIN_9
#define SLCT_08_GPIO_Port GPIOA
#define SLCTRED_05_Pin GPIO_PIN_11
#define SLCTRED_05_GPIO_Port GPIOA
#define SLCTRED_04_Pin GPIO_PIN_12
#define SLCTRED_04_GPIO_Port GPIOA
#define SLCT_06_Pin GPIO_PIN_6
#define SLCT_06_GPIO_Port GPIOB
#define SLCT_01_Pin GPIO_PIN_8
#define SLCT_01_GPIO_Port GPIOB
#define SLCT_02_Pin GPIO_PIN_9
#define SLCT_02_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
