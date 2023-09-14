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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stdarg.h"
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
char receiveText[50];
int receiveTextLength = 0;

char myUserName[] = "USER1";
char coUserName[50];

char rxData[5];
char receivedMessage[100];
int receivedIndex = 0;

volatile int isFirstRx = 1;
volatile int isSendable = 1;

int isQuit = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay(uint32_t delay)
{
	HAL_Delay(delay);
}

void printOut(const char * text)
{
	while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == RESET) {}
	HAL_UART_Transmit(&huart3, (uint8_t*) text, strlen(text), 100);
}

void printOutLine(const char * text)
{
	printOut(text);
	printOut("\n\r");
}

void receiveUserInput()
{
	receiveTextLength = 0;
	char ch = 'a';
	while(ch != '\r')
	{
		while(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == RESET) {}
		HAL_UART_Receive(&huart3, (uint8_t*) &ch, 1, 1000);
		//SAVE INPUT TO GLobal STRING
		receiveText[receiveTextLength++]= ch;

		while(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_TC) == RESET) {}
		HAL_UART_Transmit(&huart3, (uint8_t*) &ch, 1, 1000);
	}
	//ADD "/r/n"
	receiveText[receiveTextLength++]= '\n';
	printOut("\n");
}

void sentMessage(char * text)
{
	while(__HAL_UART_GET_FLAG(&huart6,UART_FLAG_TC) == RESET) {}
	HAL_UART_Transmit(&huart6, (uint8_t*)text, strlen(text), 1000);
	isSendable = 0;
}

void inputName()
{
	printOut("\tName: ");
	receiveUserInput();

	// Text require "\r\n"
	sentMessage(receiveText);

	strncpy(myUserName, receiveText, receiveTextLength-2);
	myUserName[receiveTextLength-2] = '\0';
}

void checkCoUserIsReady()
{
	while (isFirstRx) { }
	char text[50];
	sprintf(text,"\t%s is ready\r\n", coUserName);
	printOut(text);
}

void checkQuitStatus(char *text)
{
	if (text[0] == 'q' && text[2] == '\n')
	{
		isQuit = 1;
		isSendable = 0;
    	HAL_UART_DeInit(&huart6);
	}
}

void userInputText()
{
	char text[100];
	sprintf(text,"\t %s => ", myUserName);
	printOut(text);
	receiveUserInput();
}

void showReceivedMessage()
{
	if (strlen(receivedMessage) == 0) {return;}
	char text[100];
	sprintf(text,"\t %s : %s\r\n", coUserName, receivedMessage);
	printOut(text);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (rxData[0] == '\n')
    {
    	HAL_UART_Init(&huart3);
        // End of message received, process it
    	receivedMessage[--receivedIndex] = '\0';
        if (isFirstRx)
        {
        	strcpy(coUserName, receivedMessage);
        	isFirstRx = 0;
        	isSendable = 1;
        } else if (receivedMessage[0] == 'q' && receivedMessage[1] == '\0')
		{
        	isQuit = 1;
        	isSendable = 0;
           	HAL_UART_DeInit(&huart6);
		} else
        {
        	showReceivedMessage();
        	receivedMessage[0]='\0';
        	isSendable = 1;
        }
        // Reset the index for the next message
        receivedIndex = 0;
    } else
    {
    	receivedMessage[receivedIndex++] = rxData[0];
    }

    // Enable UART receive interrupt again
    HAL_UART_Receive_IT(&huart6, (uint8_t*)rxData, 1);
}
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
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
  const char WELCOME_TEXT[] = "Man from U.A.R.T.2!\r\nQuit PRESS q\r\n";
  HAL_UART_Receive_IT(&huart6, (uint8_t*)rxData, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  printOut(WELCOME_TEXT);
	  checkCoUserIsReady();
	  inputName();

	  while(!isQuit)
	  {
//		  while(!isSendable && !isQuit)
//		  {
//		  		  char ch;
//		  		  while(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == RESET&& !isSendable && !isQuit) {}
//		  	  		HAL_UART_Receive(&huart3, (uint8_t*) &ch, 1, 100);
//		  }
		  while(isSendable)
		  {
			  userInputText();
			  sentMessage(receiveText);
			  checkQuitStatus(receiveText);
			  HAL_UART_DeInit(&huart3);
			  delay(100);
		  }
		  delay(10);
	  }
	  HAL_UART_Init(&huart3);
	  printOut("QUIT\r\n");
	  while(1){}
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

void blinkOn(int pinNumber)
{
	uint16_t pins[3] =
	{
			GPIO_PIN_0,
			GPIO_PIN_7,
			GPIO_PIN_14
	};

	HAL_GPIO_WritePin(GPIOB, pins[pinNumber], GPIO_PIN_SET);
}

void blinkOff(int pinNumber)
{
	uint16_t pins[3] =
	{
			GPIO_PIN_0,
			GPIO_PIN_7,
			GPIO_PIN_14
	};

	HAL_GPIO_WritePin(GPIOB, pins[pinNumber], GPIO_PIN_RESET);
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
