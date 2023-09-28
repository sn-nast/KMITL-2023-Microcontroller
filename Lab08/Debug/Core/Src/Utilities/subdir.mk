################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Utilities/my_basic.c \
../Core/Src/Utilities/my_lcd.c 

OBJS += \
./Core/Src/Utilities/my_basic.o \
./Core/Src/Utilities/my_lcd.o 

C_DEPS += \
./Core/Src/Utilities/my_basic.d \
./Core/Src/Utilities/my_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Utilities/%.o Core/Src/Utilities/%.su Core/Src/Utilities/%.cyclo: ../Core/Src/Utilities/%.c Core/Src/Utilities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/ILI9341 -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc/Utilities -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Utilities

clean-Core-2f-Src-2f-Utilities:
	-$(RM) ./Core/Src/Utilities/my_basic.cyclo ./Core/Src/Utilities/my_basic.d ./Core/Src/Utilities/my_basic.o ./Core/Src/Utilities/my_basic.su ./Core/Src/Utilities/my_lcd.cyclo ./Core/Src/Utilities/my_lcd.d ./Core/Src/Utilities/my_lcd.o ./Core/Src/Utilities/my_lcd.su

.PHONY: clean-Core-2f-Src-2f-Utilities

