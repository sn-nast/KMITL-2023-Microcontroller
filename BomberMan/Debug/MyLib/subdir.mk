################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MyLib/icons.c \
../MyLib/joystick.c \
../MyLib/my_basic.c \
../MyLib/my_lcd.c 

OBJS += \
./MyLib/icons.o \
./MyLib/joystick.o \
./MyLib/my_basic.o \
./MyLib/my_lcd.o 

C_DEPS += \
./MyLib/icons.d \
./MyLib/joystick.d \
./MyLib/my_basic.d \
./MyLib/my_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
MyLib/%.o MyLib/%.su MyLib/%.cyclo: ../MyLib/%.c MyLib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/ILI9341 -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../MyLib -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MyLib

clean-MyLib:
	-$(RM) ./MyLib/icons.cyclo ./MyLib/icons.d ./MyLib/icons.o ./MyLib/icons.su ./MyLib/joystick.cyclo ./MyLib/joystick.d ./MyLib/joystick.o ./MyLib/joystick.su ./MyLib/my_basic.cyclo ./MyLib/my_basic.d ./MyLib/my_basic.o ./MyLib/my_basic.su ./MyLib/my_lcd.cyclo ./MyLib/my_lcd.d ./MyLib/my_lcd.o ./MyLib/my_lcd.su

.PHONY: clean-MyLib

