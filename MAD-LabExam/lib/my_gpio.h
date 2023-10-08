#ifndef __MY_GPIO_H_
#define __MY_GPIO_H_

#include "my_basic.h"
#include "gpio.h"

void writePin(GPIO_TypeDef *pinGroup, uint16_t pinNumber, GPIO_PinState pinState);
uint8_t isPinSet(GPIO_TypeDef *pinGroup, uint16_t pinNumber);
uint8_t isPinSetByPinType(GpioPin *gpioPin);

#endif /* __MY_GPIO_H_ */