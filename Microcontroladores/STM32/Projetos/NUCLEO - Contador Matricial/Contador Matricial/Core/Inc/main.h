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
#define SET_BTN_Pin GPIO_PIN_13
#define SET_BTN_GPIO_Port GPIOC
#define PORT_C_Pin GPIO_PIN_5
#define PORT_C_GPIO_Port GPIOA
#define PORT_D_Pin GPIO_PIN_6
#define PORT_D_GPIO_Port GPIOA
#define COLUMN_03_Pin GPIO_PIN_5
#define COLUMN_03_GPIO_Port GPIOC
#define LINE_01_Pin GPIO_PIN_11
#define LINE_01_GPIO_Port GPIOB
#define LINE_02_Pin GPIO_PIN_12
#define LINE_02_GPIO_Port GPIOB
#define COLUMN_02_Pin GPIO_PIN_6
#define COLUMN_02_GPIO_Port GPIOC
#define PORT_F_Pin GPIO_PIN_7
#define PORT_F_GPIO_Port GPIOC
#define COLUMN_01_Pin GPIO_PIN_8
#define COLUMN_01_GPIO_Port GPIOC
#define PORT_G_Pin GPIO_PIN_9
#define PORT_G_GPIO_Port GPIOA
#define DISP_03_Pin GPIO_PIN_10
#define DISP_03_GPIO_Port GPIOA
#define LINE_03_Pin GPIO_PIN_11
#define LINE_03_GPIO_Port GPIOA
#define LINE_04_Pin GPIO_PIN_12
#define LINE_04_GPIO_Port GPIOA
#define DISP_02_Pin GPIO_PIN_3
#define DISP_02_GPIO_Port GPIOB
#define DISP_01_Pin GPIO_PIN_5
#define DISP_01_GPIO_Port GPIOB
#define PORT_E_Pin GPIO_PIN_6
#define PORT_E_GPIO_Port GPIOB
#define PORT_A_Pin GPIO_PIN_8
#define PORT_A_GPIO_Port GPIOB
#define PORT_B_Pin GPIO_PIN_9
#define PORT_B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
