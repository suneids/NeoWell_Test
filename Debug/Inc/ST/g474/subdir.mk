################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/ST/g474/system_stm32g4xx.c 

OBJS += \
./Inc/ST/g474/system_stm32g4xx.o 

C_DEPS += \
./Inc/ST/g474/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/ST/g474/%.o Inc/ST/g474/%.su Inc/ST/g474/%.cyclo: ../Inc/ST/g474/%.c Inc/ST/g474/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G0 -DSTM32G0B1CBTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-ST-2f-g474

clean-Inc-2f-ST-2f-g474:
	-$(RM) ./Inc/ST/g474/system_stm32g4xx.cyclo ./Inc/ST/g474/system_stm32g4xx.d ./Inc/ST/g474/system_stm32g4xx.o ./Inc/ST/g474/system_stm32g4xx.su

.PHONY: clean-Inc-2f-ST-2f-g474

