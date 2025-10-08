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
#include <stdio.h>
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct datap {
	unsigned P0 : 1;
	unsigned P1 : 1;
	unsigned P2 : 1;
	unsigned P3 : 1;
	unsigned P4 : 1;
	unsigned P5 : 1;
	unsigned P6 : 1;
	unsigned P7 : 1;
} datap;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DELAY_TIME 20
#define WORD_SIZE 16
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */

uint8_t bouncingTime 	= 0,
		brefBoucingTime = 0,
		count           = 0,
		altern          = 0;

uint8_t contagem = 0;

char words[4][WORD_SIZE] = {
						{"Hello World!"},
						{"I'm Daniel"},
						{":D :P :^ :| :("},
						{"SELETIVA WS DF"}
					};

char atualWord[WORD_SIZE],
	 buffer[20],
	 start[50] = "Contando: ";

//char    atualState      = 0,
//		newState        = 1,
//		aux             = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */

void Refresh(void);
void Initialize_LCD(void);
void Mensage(char *atualString);
void Control_LCD (unsigned data, unsigned gate);

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
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_Delay(DELAY_TIME);
  Initialize_LCD();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  Refresh();
	  strcpy(atualWord, words[count]);
	  Mensage(atualWord);
	  Control_LCD(0x80, 0);

	  Control_LCD(0xC0, 0);
	  Mensage("CONTAGEM: ");

	  Control_LCD(0xCA, 0);
	  sprintf(buffer,"   %d  ", contagem);
	  Mensage(buffer);


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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  htim6.Init.Prescaler = 12000-1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1000-1;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, EN_Pin|RW_Pin|DB1_Pin|RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DB4_Pin|DB7_Pin|DB5_Pin|DB6_Pin
                          |DB0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DB3_Pin|DB2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : EN_Pin RW_Pin DB1_Pin RS_Pin */
  GPIO_InitStruct.Pin = EN_Pin|RW_Pin|DB1_Pin|RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DB4_Pin DB7_Pin DB5_Pin DB6_Pin
                           DB0_Pin */
  GPIO_InitStruct.Pin = DB4_Pin|DB7_Pin|DB5_Pin|DB6_Pin
                          |DB0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : DB3_Pin DB2_Pin */
  GPIO_InitStruct.Pin = DB3_Pin|DB2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BTN_TWIST_Pin */
  GPIO_InitStruct.Pin = BTN_TWIST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BTN_TWIST_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// Inicializador
void Initialize_LCD(void){
    /* Inicialização dos caracteres resolução 5x8 */
    Control_LCD(0x30, 0);
    Control_LCD(0x30, 0);
    Control_LCD(0x30, 0);

    /*Comunicação de 8bits disp de 2 ou mais linhas*/
    Control_LCD(0x38, 0);

    Control_LCD(0x0F, 0); // Liga o cursor no modo piscante
    Control_LCD(0x06, 0); // Desloca o cursor para a direita quando um caracter é inserido
    Control_LCD(0x01, 0); // Limpa a tela do display e desloca o cursor
}


// Para mensagens
void Mensage(char *atual_string){
    for (int i = 0; atual_string[i] != '\0'; i++){
    	if (atual_string[i] == '\0') break;
		Control_LCD(atual_string[i], 1);
    }
}

// Controle do LCD
void Control_LCD(unsigned data, unsigned gate) {
    datap port;

    // Filtro de informação
    port.P0 = (data >> 0) & 1;
    port.P1 = (data >> 1) & 1;
    port.P2 = (data >> 2) & 1;
    port.P3 = (data >> 3) & 1;
    port.P4 = (data >> 4) & 1;
    port.P5 = (data >> 5) & 1;
    port.P6 = (data >> 6) & 1;
    port.P7 = (data >> 7) & 1;

    if (gate) {
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin,GPIO_PIN_RESET);
    }

    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin,GPIO_PIN_RESET);

    HAL_GPIO_WritePin(DB0_GPIO_Port, DB0_Pin, port.P0);
    HAL_GPIO_WritePin(DB1_GPIO_Port, DB1_Pin, port.P1);
    HAL_GPIO_WritePin(DB2_GPIO_Port, DB2_Pin, port.P2);
    HAL_GPIO_WritePin(DB3_GPIO_Port, DB3_Pin, port.P3);
    HAL_GPIO_WritePin(DB4_GPIO_Port, DB4_Pin, port.P4);
    HAL_GPIO_WritePin(DB5_GPIO_Port, DB5_Pin, port.P5);
    HAL_GPIO_WritePin(DB6_GPIO_Port, DB6_Pin, port.P6);
    HAL_GPIO_WritePin(DB7_GPIO_Port, DB7_Pin, port.P7);

    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
}

void Refresh(void){
	uint8_t btwist = HAL_GPIO_ReadPin(BTN_TWIST_GPIO_Port, BTN_TWIST_Pin);

	if (!btwist){
		bouncingTime = HAL_GetTick();
		if ((bouncingTime - brefBoucingTime ) < DELAY_TIME){
			count++;
		    Control_LCD(0x01, 0);
		}

		brefBoucingTime = bouncingTime;
		if (count >= 4) count = 0;

	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	contagem++;
	if (contagem >= 100) contagem = 0;
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
