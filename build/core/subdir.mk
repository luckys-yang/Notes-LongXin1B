#
# Auto-Generated file. Do not edit!
#

# Add inputs and outputs from these tool invocations to the build variables
ASM_SRCS += \
../core/cache.S \
../core/irq_s.S \
../core/mips_timer.S \
../core/start.S \
../core/tlb.S

C_SRCS += \
../core/bsp_start.c \
../core/exception.c \
../core/inittlb.c \
../core/irq.c \
../core/tick.c

STARTO += ./core/start.o

OBJS += \
./core/bsp_start.o \
./core/cache.o \
./core/exception.o \
./core/inittlb.o \
./core/irq.o \
./core/irq_s.o \
./core/mips_timer.o \
./core/tick.o \
./core/tlb.o

ASM_DEPS += \
./core/cache.d \
./core/irq_s.d \
./core/mips_timer.d \
./core/start.d \
./core/tlb.d

C_DEPS += \
./core/bsp_start.d \
./core/exception.d \
./core/inittlb.d \
./core/irq.d \
./core/tick.d

# Each subdirectory must supply rules for building sources it contributes
core/%.o: ../core/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	E:/LongXin/IDE/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1B -DOS_NONE  -O0 -g -Wall -c -fmessage-length=0 -pipe -I"../" -I"../include" -I"../core/mips" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

core/%.o: ../core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	E:/LongXin/IDE/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1B -DOS_NONE  -O0 -g -Wall -c -fmessage-length=0 -pipe -I"../" -I"../include" -I"../APP/ALL" -I"../APP/BH1750" -I"../APP/BUZZER" -I"../APP/FAN" -I"../APP/HMC5883L" -I"../APP/KEY" -I"../APP/LCD" -I"../APP/LED" -I"../APP/LM35" -I"../APP/MOTOR" -I"../APP/MY_ADC" -I"../APP/MY_IIC" -I"../APP/MY_PWM" -I"../APP/MY_RTC" -I"../APP/MY_UART" -I"../APP/RESISTOR" -I"../APP/SMG" -I"../APP/TIM" -I"../APP/ULTRASOUND" -I"../APP/XIAOCHUANG" -I"../core/include" -I"../core/mips" -I"../libc" -I"../ls1x-drv/include" -I"../src/lkdGui_source/include" -I"../src/lkdGui_source/port" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

