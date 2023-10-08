#include "my_sensor.h"

// For AM2320
void AM2320_setCommand(uint8_t *cmdBuffer)
{
    cmdBuffer[0] = 0x03;
    cmdBuffer[1] = 0x00;
    cmdBuffer[2] = 0x04;
    printOutLine("Set Sensor");
}

void AM2320_startSensor(I2C_HandleTypeDef *hi2c, uint8_t *cmdBuffer, uint8_t *dataBuffer)
{
    // Setting hi2c1: PB8, PB9 - use hi2c1
    const uint8_t SENSOR_ADDRESS = 0x5c << 1;

    HAL_I2C_Master_Transmit(hi2c, SENSOR_ADDRESS, cmdBuffer, 3, 200);
    HAL_I2C_Master_Transmit(hi2c, SENSOR_ADDRESS, cmdBuffer, 3, 200);
    delay(1);
    HAL_I2C_Master_Receive(hi2c, SENSOR_ADDRESS, dataBuffer, 8, 200);
}

void AM2320_getTemperatureAndHumidity(float *temperature, float *humidity, uint8_t dataBuffer[8])
{
    uint16_t Rcrc = dataBuffer[7] << 8;
    Rcrc += dataBuffer[6];
    char text[30];
    if (Rcrc == AM2320_CRC16_2(dataBuffer, 6))
    {
        uint16_t temperatureRawValue = ((dataBuffer[4] & 0x7F) << 8) + dataBuffer[5];
        *temperature = temperatureRawValue / 10.0;
        *temperature = (((dataBuffer[4] & 0x80) >> 7) == 1) ? (*temperature * (-1)) : *temperature;

        uint16_t himdityRawValue = (dataBuffer[2] << 8) + dataBuffer[3];
        *humidity = himdityRawValue / 10.0;
    }
    sprintf(text, "Temperature= %4.1f \t Humidity= %4.1f", *temperature, *humidity);
    printOutLine(text);
}

uint16_t AM2320_CRC16_2(uint8_t *ptr, uint8_t length)
{
    uint16_t crc = 0xFFFF;
    uint8_t s = 0x00;

    while (length--)
    {
        crc ^= *ptr++;
        for (s = 0; s < 8; s++)
        {
            if ((crc & 0x01) != 0)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

void checkI2cAddress(I2C_HandleTypeDef *hi2c)
{
    char text[20];
    for (uint8_t i = 0; i < 128; i++)
    {
        if (HAL_I2C_IsDeviceReady(hi2c, (uint16_t)(i << 1), 3, 5) == HAL_OK)
        {
            sprintf(text, "%2x ", i);
            printOut(text);
        }
        else
        {
            printOut("-- ");
        }

        if (i > 0 && (i + 1) % 16 == 0)
            printOut("\r\n");
    }
    printOutLine("\r\nDONE");
}