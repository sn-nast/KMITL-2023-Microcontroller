#include "my_gpio.h"

void writePin(GPIO_TypeDef *pinGroup, uint16_t pinNumber, GPIO_PinState pinState)
{
    HAL_GPIO_WritePin(pinGroup, pinNumber, pinState);
}

uint8_t isPinSet(GPIO_TypeDef *pinGroup, uint16_t pinNumber)
{
    return (uint8_t)(HAL_GPIO_ReadPin(pinGroup, pinNumber) == GPIO_PIN_SET);
}

uint8_t isPinSetByPinType(GpioPin* gpioPin)
{
    return (uint8_t)(HAL_GPIO_ReadPin(gpioPin->pinGroup, gpioPin->pin) == GPIO_PIN_SET);
}
