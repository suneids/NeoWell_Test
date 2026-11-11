################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/src/SCPI.c \
../Inc/src/modbus.c \
../Inc/src/soft_i2c.c \
../Inc/src/soft_uart.c \
../Inc/src/utilities.c 

OBJS += \
./Inc/src/SCPI.o \
./Inc/src/modbus.o \
./Inc/src/soft_i2c.o \
./Inc/src/soft_uart.o \
./Inc/src/utilities.o 

C_DEPS += \
./Inc/src/SCPI.d \
./Inc/src/modbus.d \
./Inc/src/soft_i2c.d \
./Inc/src/soft_uart.d \
./Inc/src/utilities.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/src/%.o Inc/src/%.su Inc/src/%.cyclo: ../Inc/src/%.c Inc/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G0 -DSTM32G0B1CBTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-src

clean-Inc-2f-src:
	-$(RM) ./Inc/src/SCPI.cyclo ./Inc/src/SCPI.d ./Inc/src/SCPI.o ./Inc/src/SCPI.su ./Inc/src/modbus.cyclo ./Inc/src/modbus.d ./Inc/src/modbus.o ./Inc/src/modbus.su ./Inc/src/soft_i2c.cyclo ./Inc/src/soft_i2c.d ./Inc/src/soft_i2c.o ./Inc/src/soft_i2c.su ./Inc/src/soft_uart.cyclo ./Inc/src/soft_uart.d ./Inc/src/soft_uart.o ./Inc/src/soft_uart.su ./Inc/src/utilities.cyclo ./Inc/src/utilities.d ./Inc/src/utilities.o ./Inc/src/utilities.su

.PHONY: clean-Inc-2f-src

