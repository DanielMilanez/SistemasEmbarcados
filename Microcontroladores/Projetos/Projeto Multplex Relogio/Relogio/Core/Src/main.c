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
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// Start count variables.
uint8_t	  dispAtual      = 0,
		  ctr			 = 0,
		  befSetMode     = 1,
		  setMode        = 0,
		  aux            = 0;

uint32_t miliseconds = 0,
		 seconds     = 0,
		 secondsDeca = 0,
		 minutes     = 0,
		 minutesDeca = 0,
		 hours       = 0,
		 hoursDeca   = 0,
		 timeBouncing = 0,
		 befTimeBoucing = 0;

uint8_t disp[][7] = {
						{1,1,1,1,1,1,0}, // 0
						{0,1,1,0,0,0,0}, // 1
						{1,1,0,1,1,0,1}, // 2
						{1,1,1,1,0,0,1}, // 3
						{0,1,1,0,0,1,1}, // 4
						{1,0,1,1,0,1,1}, // 5
						{1,0,1,1,1,1,1}, // 6
						{1,1,1,0,0,0,0}, // 7
						{1,1,1,1,1,1,1}, // 8
						{1,1,1,1,0,1,1}  // 9
					};

int b_hours = 0, b_minutes = 0, b_seconds = 0, b_setmode = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void verify(void);
void btn(void);
void outputDisplay(uint8_t disp);
void draw_disp(uint8_t my_atual_count);
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

  // Start timer.
  HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1){
	  outputDisplay(dispAtual);
	  btn();

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

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (!setMode){
		miliseconds++;
	}
}

void draw_disp(uint8_t my_atual_count){
	HAL_GPIO_WritePin(PORT_A_GPIO_Port, PORT_A_Pin, disp[my_atual_count][0]);
	HAL_GPIO_WritePin(PORT_B_GPIO_Port, PORT_B_Pin, disp[my_atual_count][1]);
	HAL_GPIO_WritePin(PORT_C_GPIO_Port, PORT_C_Pin, disp[my_atual_count][2]);
	HAL_GPIO_WritePin(PORT_D_GPIO_Port, PORT_D_Pin, disp[my_atual_count][3]);
	HAL_GPIO_WritePin(PORT_E_GPIO_Port, PORT_E_Pin, disp[my_atual_count][4]);
	HAL_GPIO_WritePin(PORT_F_GPIO_Port, PORT_F_Pin, disp[my_atual_count][5]);
	HAL_GPIO_WritePin(PORT_G_GPIO_Port, PORT_G_Pin, disp[my_atual_count][6]);
}

void verify(void){
	switch (dispAtual){
		case 0:
			HAL_GPIO_WritePin(SELETOR_A_GPIO_Port, SELETOR_A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SELETOR_B_GPIO_Port, SELETOR_B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SELETOR_C_GPIO_Port, SELETOR_C_Pin, GPIO_PIN_RESET);
			break;

		case 1:
			HAL_GPIO_WritePin(SELETOR_A_GPIO_Port, SELETOR_A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SELETOR_B_GPIO_Port, SELETOR_B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SELETOR_C_GPIO_Port, SELETOR_C_Pin, GPIO_PIN_RESET);
			break;

		case 2:
			HAL_GPIO_WritePin(SELETOR_A_GPIO_Port, SELETOR_A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SELETOR_B_GPIO_Port, SELETOR_B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SELETOR_C_GPIO_Port, SELETOR_C_Pin, GPIO_PIN_RESET);
			break;

		case 3:
			HAL_GPIO_WritePin(SELETOR_A_GPIO_Port, SELETOR_A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SELETOR_B_GPIO_Port, SELETOR_B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SELETOR_C_GPIO_Port, SELETOR_C_Pin, GPIO_PIN_RESET);
			break;

		case 4:
			HAL_GPIO_WritePin(SELETOR_A_GPIO_Port, SELETOR_A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SELETOR_B_GPIO_Port, SELETOR_B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SELETOR_C_GPIO_Port, SELETOR_C_Pin, GPIO_PIN_SET);
			break;

		case 5:
			HAL_GPIO_WritePin(SELETOR_A_GPIO_Port, SELETOR_A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SELETOR_B_GPIO_Port, SELETOR_B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SELETOR_C_GPIO_Port, SELETOR_C_Pin, GPIO_PIN_SET);
			break;

		case 6:
			HAL_GPIO_WritePin(SELETOR_A_GPIO_Port, SELETOR_A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SELETOR_B_GPIO_Port, SELETOR_B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(SELETOR_C_GPIO_Port, SELETOR_C_Pin, GPIO_PIN_SET);
			break;
	}
	HAL_GPIO_WritePin(CLOCK_GPIO_Port, CLOCK_Pin, 1);
	HAL_GPIO_WritePin(CLOCK_GPIO_Port, CLOCK_Pin, 0);
	HAL_Delay(1);
}

void outputDisplay(uint8_t disp){
	if (miliseconds >= 100){
		seconds++;
		miliseconds = 0;
	}

	if (seconds >= 10){
		seconds = 0;
		secondsDeca++;
	}

	if (secondsDeca >= 6){
		secondsDeca = 0;
		minutes++;
	}

	if (minutes >= 10){
		minutes = 0;
		minutesDeca++;
	}

	if (minutesDeca >= 6){
		minutesDeca = 0;
		hours++;
	}

	if (hours >= 10){
		hoursDeca++;
		hours = 0;
	}

	if((hoursDeca >= 2) && (hours >= 4)){
		hours = 0;
		hoursDeca = 0;
	}

	switch (disp){
		case 0:
			draw_disp(hoursDeca);
			verify();
			dispAtual = 1;
			break;

		case 1:
			draw_disp(hours);
			verify();
			dispAtual = 2;
			break;

		case 2:
			draw_disp(minutesDeca);
			verify();
			dispAtual = 3;
			break;

		case 3:
			draw_disp(minutes);
			verify();
			dispAtual = 4;
			break;

		case 4:
			draw_disp(secondsDeca);
			verify();
			dispAtual = 5;
			break;

		case 5:
			draw_disp(seconds);
			verify();
			dispAtual = 6;
			break;

		case 6:
			draw_disp((miliseconds / 10));
			verify();
			dispAtual = 0;
			break;
	}
}

void btn(void){
	  switch(ctr) {
	  	  case 0:
	  		  b_hours = HAL_GPIO_ReadPin(BTN_Horas_GPIO_Port, BTN_Horas_Pin);
	  		  ctr = 1;
	  		  break;

	  	  case 1:
	  		  b_minutes = HAL_GPIO_ReadPin(BTN_Minutos_GPIO_Port, BTN_Minutos_Pin);
	  		  ctr = 2;
	  		  break;

	  	  case 2:
	  		  b_seconds = HAL_GPIO_ReadPin(BTN_Seconds_GPIO_Port, BTN_Seconds_Pin);
	  		  ctr = 3;
	  		  break;

	  	  case 3:
	  		  b_setmode = HAL_GPIO_ReadPin(SET_BTN_GPIO_Port, SET_BTN_Pin);
	  		  ctr = 0;
	  		  break;
	  }

	  if (!b_setmode) {
		  timeBouncing = HAL_GetTick();
		  if ((timeBouncing - befTimeBoucing ) > 10){
			  aux = befSetMode;
			  befSetMode = setMode;
			  setMode = aux;
		  }
		  befTimeBoucing = timeBouncing;
	  }

	if (setMode){
	  if (!b_hours) {
	  		timeBouncing = HAL_GetTick();
	  		if ((timeBouncing - befTimeBoucing ) > 10){
	  			hours++;
	  		}

	  		befTimeBoucing = timeBouncing;
	  	}

	  	if (!b_minutes) {
	  		timeBouncing = HAL_GetTick();
	  		if ((timeBouncing - befTimeBoucing ) > 10){
	  			minutes++;
	  		}

	  		befTimeBoucing = timeBouncing;
	  	}

	  	if (!b_seconds) {
		  		timeBouncing = HAL_GetTick();
		  		if ((timeBouncing - befTimeBoucing ) > 10){
		  			seconds++;
		  		}

		  		befTimeBoucing = timeBouncing;
		  	}
	}
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
