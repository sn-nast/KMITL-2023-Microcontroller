/*
 * my_basic.h
 *
 *  Created on: Sep 28, 2023
 *      Author: sunsu
 */

#ifndef __MY_BASIC_H_
#define __MY_BASIC_H_

#include "usart.h"
#include "string.h"
#include "stdint.h"
#include "stm32f7xx.h"

typedef struct _PwmInfo
{
	TIM_HandleTypeDef *timer;
	uint32_t timerChannel;
	GPIO_TypeDef *pinGroup;
	uint16_t pin;
	float dutyCycle;
} PwmInfo;

typedef struct _GpioPin
{
	GPIO_TypeDef *pinGroup;
	uint16_t pin;
} GpioPin;

void printOut(const char *text);
void printOutLine(const char *text);
void receiveUserInput(char *rxData);
void delay(uint32_t delay);

int average8(int newValue);
int average16(int newValue);

#endif /* MY_BASIC_H_ */
