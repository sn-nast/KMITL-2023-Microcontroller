################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TestFolder/my_basic.c \
../TestFolder/my_gpio.c \
../TestFolder/my_sensor.c 

OBJS += \
./TestFolder/my_basic.o \
./TestFolder/my_gpio.o \
./TestFolder/my_sensor.o 

C_DEPS += \
./TestFolder/my_basic.d \
./TestFolder/my_gpio.d \
./TestFolder/my_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
TestFolder/%.o TestFolder/%.su TestFolder/%.cyclo: ../TestFolder/%.c TestFolder/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I"D:/A My Project/01 KMITL Project/KMITL-2023-S1-Microcontroller/64011113_exam/MyExamTemplate/TestFolder" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TestFolder

clean-TestFolder:
	-$(RM) ./TestFolder/my_basic.cyclo ./TestFolder/my_basic.d ./TestFolder/my_basic.o ./TestFolder/my_basic.su ./TestFolder/my_gpio.cyclo ./TestFolder/my_gpio.d ./TestFolder/my_gpio.o ./TestFolder/my_gpio.su ./TestFolder/my_sensor.cyclo ./TestFolder/my_sensor.d ./TestFolder/my_sensor.o ./TestFolder/my_sensor.su

.PHONY: clean-TestFolder

