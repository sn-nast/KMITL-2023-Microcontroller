#include "my_adc.h"

void adcPolling(ADC_HandleTypeDef *hadc, uint32_t adcValue)
{
    HAL_ADC_Start(hadc);

    while(1)
    {
        while(HAL_ADC_PollForConversion(hadc, 100) != HAL_OK);
        adcValue = HAL_ADC_GetValue(hadc);
    }
}