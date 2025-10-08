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
#define CLOCK_Pin GPIO_PIN_5
#define CLOCK_GPIO_Port GPIOA
#define SELETOR_C_Pin GPIO_PIN_5
#define SELETOR_C_GPIO_Port GPIOC
#define PORT_F_Pin GPIO_PIN_1
#define PORT_F_GPIO_Port GPIOB
#define PORT_E_Pin GPIO_PIN_2
#define PORT_E_GPIO_Port GPIOB
#define PORT_D_Pin GPIO_PIN_11
#define PORT_D_GPIO_Port GPIOB
#define PORT_C_Pin GPIO_PIN_12
#define PORT_C_GPIO_Port GPIOB
#define PORT_G_Pin GPIO_PIN_15
#define PORT_G_GPIO_Port GPIOB
#define SELETOR_A_Pin GPIO_PIN_6
#define SELETOR_A_GPIO_Port GPIOC
#define SELETOR_B_Pin GPIO_PIN_8
#define SELETOR_B_GPIO_Port GPIOC
#define BTN_Minutos_Pin GPIO_PIN_8
#define BTN_Minutos_GPIO_Port GPIOA
#define BTN_Horas_Pin GPIO_PIN_9
#define BTN_Horas_GPIO_Port GPIOA
#define PORT_B_Pin GPIO_PIN_11
#define PORT_B_GPIO_Port GPIOA
#define PORT_A_Pin GPIO_PIN_12
#define PORT_A_GPIO_Port GPIOA
#define BTN_Seconds_Pin GPIO_PIN_5
#define BTN_Seconds_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
