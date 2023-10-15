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
#include "tim.h"
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
uint8_t pwm;

char rxInput[5];

typedef struct _Color
{
	TIM_HandleTypeDef * timer;
	uint32_t timerChannel;
	GPIO_TypeDef * pinGroup;
	uint16_t pin;
	float intensity;
	uint8_t pwm;
} Color;

Color red, green, blue;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void generatePwm()
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_Delay(100);
	//HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
//	printOutLine("ABC");
	pwm = (GPIOB->IDR & GPIO_PIN_10) >> 10;
}

void generatePwm2(float dutyCycle)
{
	htim2.Instance -> CCR3 = (10000-1) * dutyCycle;
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_Delay(100);
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
	pwm = (GPIOB->IDR & GPIO_PIN_10) >> 10;
}

void printOut(const char * text)
{
	while(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == RESET) {}
	HAL_UART_Transmit(&huart3, (uint8_t*) text, strlen(text), 100);
}

void printOutLine(const char * text)
{
	printOut(text);
	printOut("\r\n");
}

void setRedIntensity(float dutyCycle) {
	htim4.Instance->CCR1 = (10000 - 1) * dutyCycle;
}

void setGreenIntensity(float dutyCycle)
{
	htim4.Instance -> CCR2 = (10000-1) * dutyCycle;
}

void setBlueIntensity(float dutyCycle)
{
	htim4.Instance -> CCR3 = (10000-1) * dutyCycle;
}

// Color struct
void addIntensity(Color *color)
{
	const float MAX_SCALE = 1.0;
	const float STEP_SCALE = 0.1;

	if (color->intensity >= MAX_SCALE)
	{
		color->intensity = 0.0;
	} else
	{
		color->intensity += STEP_SCALE;
	}
}

void controlRgb_s(char *input)
{
	printOut("input char: ");
	printOutLine(input);

	if (*input == 'r' || *input == 'R')
	{
		addIntensity(&red);
		setRedIntensity(red.intensity);
	} else if (*input == 'g' || *input == 'G')
	{
		addIntensity(&green);
		setGreenIntensity(green.intensity);
	} else if (*input == 'b' || *input == 'B')
	{
		addIntensity(&blue);
		setBlueIntensity(blue.intensity);
	} else {
		printOutLine("\t\t----SKIP----");
	}

	char text[50];
	sprintf(text,"R: %.2f \t G: %.2f \t B: %.2f", red.intensity, green.intensity, blue.intensity);
	printOutLine(text);
}

void setColorInfo()
{
	red.timer = &htim4;
	red.timerChannel = TIM_CHANNEL_1;
	red.pinGroup = GPIOD;
	red.pin = GPIO_PIN_12;
	red.intensity = 0.0;
	red.pwm = 0;

	green.timer = &htim4;
	green.timerChannel = TIM_CHANNEL_2;
	green.pinGroup = GPIOD;
	green.pin = GPIO_PIN_13;
	green.intensity = 0.0;
	green.pwm = 0;

	blue.timer = &htim4;
	blue.timerChannel = TIM_CHANNEL_3;
	blue.pinGroup = GPIOD;
	blue.pin = GPIO_PIN_14;
	blue.intensity = 0.0;
	blue.pwm = 0;
}

void startPwmRgb_s()
{
	HAL_TIM_PWM_Start(red.timer, red.timerChannel);
	HAL_TIM_PWM_Start(green.timer, green.timerChannel);
	HAL_TIM_PWM_Start(blue.timer, blue.timerChannel);

//	Set intensity=0
	setRedIntensity(red.intensity);
	setGreenIntensity(green.intensity);
	setBlueIntensity(blue.intensity);
}

void updatePwmRgb_s()
{
	HAL_TIM_PWM_Stop(red.timer, red.timerChannel);
	HAL_TIM_PWM_Stop(red.timer, red.timerChannel);
	HAL_TIM_PWM_Stop(red.timer, red.timerChannel);

//	not working?
	red.pwm = (red.pinGroup->IDR & red.pin) >> 6;
	green.pwm = (green.pinGroup->IDR & green.pin) >> 7;
	blue.pwm = (blue.pinGroup->IDR & blue.pin) >> 8;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	printOut("INTERRUPT => ");
	controlRgb_s(&rxInput[0]);
	HAL_UART_Receive_IT(&huart3, (uint8_t*)rxInput, 1);
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
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  //Q1-2
  float dutyCycle = 0.5;
  dutyCycle = 0.5;

  // Struct
  setColorInfo();

  // Enable Interrupt
  HAL_UART_Receive_IT(&huart3, (uint8_t*)rxInput, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // Q1-2
//	  generatePwm();
//	  generatePwm2(dutyCycle);

	  startPwmRgb_s();

	  // get value from register
//	  updatePwmRgb_s();
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
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
