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
#define SLCTLINE_03_Pin GPIO_PIN_5
#define SLCTLINE_03_GPIO_Port GPIOA
#define SLCTLINE_04_Pin GPIO_PIN_6
#define SLCTLINE_04_GPIO_Port GPIOA
#define SLCTLINE_05_Pin GPIO_PIN_7
#define SLCTLINE_05_GPIO_Port GPIOA
#define SLCTCOLUMN_03_Pin GPIO_PIN_5
#define SLCTCOLUMN_03_GPIO_Port GPIOC
#define SLCTCOLUMN_08_Pin GPIO_PIN_2
#define SLCTCOLUMN_08_GPIO_Port GPIOB
#define SLCTCOLUMN_07_Pin GPIO_PIN_11
#define SLCTCOLUMN_07_GPIO_Port GPIOB
#define SLCTCOLUMN_06_Pin GPIO_PIN_12
#define SLCTCOLUMN_06_GPIO_Port GPIOB
#define SLCTCOLUMN_02_Pin GPIO_PIN_6
#define SLCTCOLUMN_02_GPIO_Port GPIOC
#define SLCTLINE_07_Pin GPIO_PIN_7
#define SLCTLINE_07_GPIO_Port GPIOC
#define SLCTCOLUMN_01_Pin GPIO_PIN_8
#define SLCTCOLUMN_01_GPIO_Port GPIOC
#define SLCTLINE_08_Pin GPIO_PIN_9
#define SLCTLINE_08_GPIO_Port GPIOA
#define SLCTCOLUMN_05_Pin GPIO_PIN_11
#define SLCTCOLUMN_05_GPIO_Port GPIOA
#define SLCTCOLUMN_04_Pin GPIO_PIN_12
#define SLCTCOLUMN_04_GPIO_Port GPIOA
#define SLCTLINE_06_Pin GPIO_PIN_6
#define SLCTLINE_06_GPIO_Port GPIOB
#define SLCTLINE_01_Pin GPIO_PIN_8
#define SLCTLINE_01_GPIO_Port GPIOB
#define SLCTLINE_02_Pin GPIO_PIN_9
#define SLCTLINE_02_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
