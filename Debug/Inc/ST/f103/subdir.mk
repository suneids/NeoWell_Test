################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/ST/f103/system_stm32f1xx.c 

OBJS += \
./Inc/ST/f103/system_stm32f1xx.o 

C_DEPS += \
./Inc/ST/f103/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/ST/f103/%.o Inc/ST/f103/%.su Inc/ST/f103/%.cyclo: ../Inc/ST/f103/%.c Inc/ST/f103/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G0 -DSTM32G0B1CBTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-ST-2f-f103

clean-Inc-2f-ST-2f-f103:
	-$(RM) ./Inc/ST/f103/system_stm32f1xx.cyclo ./Inc/ST/f103/system_stm32f1xx.d ./Inc/ST/f103/system_stm32f1xx.o ./Inc/ST/f103/system_stm32f1xx.su

.PHONY: clean-Inc-2f-ST-2f-f103

