#include "my_basic.h"

void printOut(const char *text)
{
	while (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_TC) == RESET)
	{
	}
	HAL_UART_Transmit(&huart3, (uint8_t *)text, strlen(text), 100);
}

void printOutLine(const char *text)
{
	printOut(text);
	printOut("\r\n");
}

void delay(uint32_t delay)
{
	HAL_Delay(delay);
}

void receiveUserInput(char *rxData)
{
	while (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == RESET)
	{
	}
	HAL_UART_Receive(&huart3, (uint8_t *)rxData, 1, 100);

	printOutLine(rxData);
}

int average8(int newValue)
{
	static int samples[8];
	static int lastIndex = 0;
	static int total = 0;

	total += newValue - samples[lastIndex];
	samples[lastIndex] = newValue;
	lastIndex = (lastIndex == 7 ? 0 : lastIndex + 1);

	return total >> 3;
}

int average16(int newValue)
{
	static int samples[16];
	static int lastIndex = 0;
	static int total = 0;

	total += newValue - samples[lastIndex];
	samples[lastIndex] = newValue;
	lastIndex = (lastIndex == 15 ? 0 : lastIndex + 1);

	return total >> 4;
}
