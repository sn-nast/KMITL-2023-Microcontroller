#ifndef __MY_SENSOR_H_
#define __MY_SENSOR_H_

#include "string.h"
#include "stdint.h"

#include "i2c.h"
#include "my_basic.h"

void AM2320_setCommand(uint8_t *cmdBuffer);
void AM2320_startSensor(I2C_HandleTypeDef *hi2c, uint8_t *cmdBuffer, uint8_t *dataBuffer);
void AM2320_getTemperatureAndHumidity(float *temperature, float *humidity, uint8_t dataBuffer[8]);
uint16_t AM2320_CRC16_2(uint8_t *ptr, uint8_t length);
void checkI2cAddress(I2C_HandleTypeDef *hi2c);

#endif /* __MY_SENSOR_H_ */