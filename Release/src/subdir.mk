################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/dac.c \
../src/gdma.c \
../src/gpio.c \
../src/interruptions.c \
../src/main.c \
../src/systick.c \
../src/timers.c \
../src/uart.c 

C_DEPS += \
./src/adc.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/dac.d \
./src/gdma.d \
./src/gpio.d \
./src/interruptions.d \
./src/main.d \
./src/systick.d \
./src/timers.d \
./src/uart.d 

OBJS += \
./src/adc.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/dac.o \
./src/gdma.o \
./src/gpio.o \
./src/interruptions.o \
./src/main.o \
./src/systick.o \
./src/timers.o \
./src/uart.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"D:\Facultad\Electronica Digital 3\worskpace\IngeniaTeam\inc" -I"D:\Facultad\Electronica Digital 3\worskpace\CMSISv2p00_LPC17xx\inc" -Os -fno-common -g -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/adc.d ./src/adc.o ./src/cr_startup_lpc175x_6x.d ./src/cr_startup_lpc175x_6x.o ./src/crp.d ./src/crp.o ./src/dac.d ./src/dac.o ./src/gdma.d ./src/gdma.o ./src/gpio.d ./src/gpio.o ./src/interruptions.d ./src/interruptions.o ./src/main.d ./src/main.o ./src/systick.d ./src/systick.o ./src/timers.d ./src/timers.o ./src/uart.d ./src/uart.o

.PHONY: clean-src

