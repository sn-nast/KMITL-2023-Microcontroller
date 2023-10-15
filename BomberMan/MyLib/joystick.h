#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "adc.h"
#include "my_basic.h"
#include "my_lcd.h"

enum MoveDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef struct _Joystick
{
	ADC_HandleTypeDef *adc;
	GpioInfo gpioX;
	GpioInfo gpioY;
} Joystick;

extern ADC_HandleTypeDef *JOYSTICK_ADC;
extern Joystick joystickA;
extern Joystick joystickB;

void startJoystick(uint32_t *positionArray);
enum MoveDirection convertToDirection(uint32_t *positionArray);
void drawPlayer(Point position);
void drawBurstArea(Point position);

#endif /* JOYSTICK_H_ */
