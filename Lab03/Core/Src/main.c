/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"
#include "string.h"
#include "stdbool.h"

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
	int isQuit = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  int isQuit2 = 0;
	  while(!isQuit2){
		  MenuCommand(&isQuit2);
	  }
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


void MenuCommand(int *isQuit) {

	char introCommand[] =
			"Display Blinking LED PRESS (1, 2)\r\nDisplay Group Members PRESS m \r\nQuit PRESS q \r\n";

	 PrintOut(introCommand);

	while (!*isQuit) {
		char command;
		UserInput(&command);
		CheckCommand(command, &isQuit);
	}

}

void UserInput(char *inputChar) {
	PrintOut("\tInput =>");

	char input;
	while(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == RESET){}
	HAL_UART_Receive(&huart3, (uint8_t*) &input, 1, 1000);
	Delay();

	PrintOutLine(&input);
	*inputChar = input;
}

void CheckCommand(char inputChar, int *isQuit) {
	char memberText[] =
			"64010989\n\rAttaphon Plianprasert\n\r64011113\n\rNatchanon Bunyachawaset\n\r641264\n\rVoraphol Promwan\n\r";

	if (inputChar == '1') {
//		BlinkLed(1);
	}
	else if (inputChar == '2') {
//		BlinkLed(2);
	}
	else if (inputChar == 'm') {
		PrintOut(memberText);
	}
	else if (inputChar == 'q') {
		*isQuit = 1;
		PrintOutLine("QUIT");
	}
	else {
		PrintOutLine("Unknown Command");
	}

}

void BlinkLed(int ledNum){
	uint16_t pin = ledNum == 1? GPIO_PIN_8 : GPIO_PIN_9;
//	for (int n = 0; n < 3; n++) {
//		HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_RESET);
//		HAL_Delay(300);
//		HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_SET);
//		HAL_delay(300);
//	}
}

void PrintOut(char text[]){
	while(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_TC) == RESET){}
	HAL_UART_Transmit(&huart3, (uint8_t*) text, strlen(text), 1000);
	Delay();
}

void PrintOutLine(char text[]){
	PrintOut(text);
	PrintOut("\n\r");
}

void Delay() {
	HAL_Delay(10);
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

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
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
