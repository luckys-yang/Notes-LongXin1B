#
# Auto-Generated file. Do not edit!
#

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../APP/TEMPERATURE/lm35.c

OBJS += \
./APP/TEMPERATURE/lm35.o

C_DEPS += \
./APP/TEMPERATURE/lm35.d

# Each subdirectory must supply rules for building sources it contributes
APP/TEMPERATURE/%.o: ../APP/TEMPERATURE/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	E:/LongXin/IDE/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1B -DOS_NONE  -O0 -g -Wall -c -fmessage-length=0 -pipe  -I"../" -I"../include" -I"../APP/ALL" -I"../APP/BUZZER" -I"../APP/KEY" -I"../APP/LCD" -I"../APP/LED" -I"../APP/SMG" -I"../APP/TEMPERATURE" -I"../APP/TIM" -I"../APP/XIAOCHUANG" -I"../core/include" -I"../core/mips" -I"../ls1x-drv/include" -I"../src/lkdGui_source/include" -I"../src/lkdGui_source/port" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

