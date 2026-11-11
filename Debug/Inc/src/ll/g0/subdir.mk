################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/src/ll/g0/adc_g0.c \
../Inc/src/ll/g0/dac_g0.c \
../Inc/src/ll/g0/dma_g0.c \
../Inc/src/ll/g0/fdcan.c \
../Inc/src/ll/g0/flash_ll_g0.c \
../Inc/src/ll/g0/gpio_g0.c \
../Inc/src/ll/g0/i2c_g0.c \
../Inc/src/ll/g0/nvstore_g0.c \
../Inc/src/ll/g0/pwm_g0.c \
../Inc/src/ll/g0/spi_g0.c \
../Inc/src/ll/g0/tim_g0.c \
../Inc/src/ll/g0/usart_g0.c 

OBJS += \
./Inc/src/ll/g0/adc_g0.o \
./Inc/src/ll/g0/dac_g0.o \
./Inc/src/ll/g0/dma_g0.o \
./Inc/src/ll/g0/fdcan.o \
./Inc/src/ll/g0/flash_ll_g0.o \
./Inc/src/ll/g0/gpio_g0.o \
./Inc/src/ll/g0/i2c_g0.o \
./Inc/src/ll/g0/nvstore_g0.o \
./Inc/src/ll/g0/pwm_g0.o \
./Inc/src/ll/g0/spi_g0.o \
./Inc/src/ll/g0/tim_g0.o \
./Inc/src/ll/g0/usart_g0.o 

C_DEPS += \
./Inc/src/ll/g0/adc_g0.d \
./Inc/src/ll/g0/dac_g0.d \
./Inc/src/ll/g0/dma_g0.d \
./Inc/src/ll/g0/fdcan.d \
./Inc/src/ll/g0/flash_ll_g0.d \
./Inc/src/ll/g0/gpio_g0.d \
./Inc/src/ll/g0/i2c_g0.d \
./Inc/src/ll/g0/nvstore_g0.d \
./Inc/src/ll/g0/pwm_g0.d \
./Inc/src/ll/g0/spi_g0.d \
./Inc/src/ll/g0/tim_g0.d \
./Inc/src/ll/g0/usart_g0.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/src/ll/g0/%.o Inc/src/ll/g0/%.su Inc/src/ll/g0/%.cyclo: ../Inc/src/ll/g0/%.c Inc/src/ll/g0/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G0 -DSTM32G0B1CBTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-src-2f-ll-2f-g0

clean-Inc-2f-src-2f-ll-2f-g0:
	-$(RM) ./Inc/src/ll/g0/adc_g0.cyclo ./Inc/src/ll/g0/adc_g0.d ./Inc/src/ll/g0/adc_g0.o ./Inc/src/ll/g0/adc_g0.su ./Inc/src/ll/g0/dac_g0.cyclo ./Inc/src/ll/g0/dac_g0.d ./Inc/src/ll/g0/dac_g0.o ./Inc/src/ll/g0/dac_g0.su ./Inc/src/ll/g0/dma_g0.cyclo ./Inc/src/ll/g0/dma_g0.d ./Inc/src/ll/g0/dma_g0.o ./Inc/src/ll/g0/dma_g0.su ./Inc/src/ll/g0/fdcan.cyclo ./Inc/src/ll/g0/fdcan.d ./Inc/src/ll/g0/fdcan.o ./Inc/src/ll/g0/fdcan.su ./Inc/src/ll/g0/flash_ll_g0.cyclo ./Inc/src/ll/g0/flash_ll_g0.d ./Inc/src/ll/g0/flash_ll_g0.o ./Inc/src/ll/g0/flash_ll_g0.su ./Inc/src/ll/g0/gpio_g0.cyclo ./Inc/src/ll/g0/gpio_g0.d ./Inc/src/ll/g0/gpio_g0.o ./Inc/src/ll/g0/gpio_g0.su ./Inc/src/ll/g0/i2c_g0.cyclo ./Inc/src/ll/g0/i2c_g0.d ./Inc/src/ll/g0/i2c_g0.o ./Inc/src/ll/g0/i2c_g0.su ./Inc/src/ll/g0/nvstore_g0.cyclo ./Inc/src/ll/g0/nvstore_g0.d ./Inc/src/ll/g0/nvstore_g0.o ./Inc/src/ll/g0/nvstore_g0.su ./Inc/src/ll/g0/pwm_g0.cyclo ./Inc/src/ll/g0/pwm_g0.d ./Inc/src/ll/g0/pwm_g0.o ./Inc/src/ll/g0/pwm_g0.su ./Inc/src/ll/g0/spi_g0.cyclo ./Inc/src/ll/g0/spi_g0.d ./Inc/src/ll/g0/spi_g0.o ./Inc/src/ll/g0/spi_g0.su ./Inc/src/ll/g0/tim_g0.cyclo ./Inc/src/ll/g0/tim_g0.d ./Inc/src/ll/g0/tim_g0.o ./Inc/src/ll/g0/tim_g0.su ./Inc/src/ll/g0/usart_g0.cyclo ./Inc/src/ll/g0/usart_g0.d ./Inc/src/ll/g0/usart_g0.o ./Inc/src/ll/g0/usart_g0.su

.PHONY: clean-Inc-2f-src-2f-ll-2f-g0

