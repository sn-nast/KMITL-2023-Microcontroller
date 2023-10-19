#include "joystick.h"
#include "icons.h"

ADC_HandleTypeDef *JOYSTICK_ADC = &hadc3;

Joystick joystickA = {
		&hadc3,
		{ GPIOF, GPIO_PIN_3 },
		{ GPIOF, GPIO_PIN_4 },
};

Joystick joystickB = {
		&hadc3,
		{ GPIOC, GPIO_PIN_0 },
		{ GPIOC, GPIO_PIN_3 },
};

void startJoystick(uint32_t *positionArray)
{
	HAL_ADC_Start_DMA(JOYSTICK_ADC, positionArray, 2);
}

enum MoveDirection convertToDirection(uint32_t *positionArray)
{
//	static uint16_t MIN = 0;
//	static uint16_t MAX = 4096;
//	static uint16_t HALF = 4096 / 2;
	static uint16_t MIN_HALF = 4096 / 4;
	static uint16_t MAX_HALF = 3 * (4096 / 4);

	Point position = {
			positionArray[0],
			positionArray[1]
	};

	enum MoveDirection direction;
	if (position.x <= MIN_HALF)
	{
		direction = LEFT;
	} else if (position.x >= MAX_HALF)
	{
		direction = RIGHT;
	} else if (position.y <= MIN_HALF)
	{
		direction = UP;
	} else if (position.y >= MAX_HALF)
	{
		direction = DOWN;
	}

	return direction;
}

void drawPlayer(Point position)
{
	playerIcon_1.drawPoint = position;
	drawImageAtPoint(playerIcon_1, SCREEN_ROTATION);
}

void drawBurstArea(Point position)
{
	Rectangle burstArea = {
			position.x,
			position.y,
			position.x + ICON_WIDTH,
			position.y + ICON_HEIGHT,
	};
	drawFilledRectangleAtCoord(burstArea, BURST_AREA_ICON);
}

