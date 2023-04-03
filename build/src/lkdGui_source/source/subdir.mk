#
# Auto-Generated file. Do not edit!
#

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/lkdGui_source/source/lkdGuiBasic.c \
../src/lkdGui_source/source/lkdGuiColour.c \
../src/lkdGui_source/source/lkdGuiControl.c \
../src/lkdGui_source/source/lkdGuiFont.c \
../src/lkdGui_source/source/lkdGuiMenu.c \
../src/lkdGui_source/source/lkdGuiWin.c

OBJS += \
./src/lkdGui_source/source/lkdGuiBasic.o \
./src/lkdGui_source/source/lkdGuiColour.o \
./src/lkdGui_source/source/lkdGuiControl.o \
./src/lkdGui_source/source/lkdGuiFont.o \
./src/lkdGui_source/source/lkdGuiMenu.o \
./src/lkdGui_source/source/lkdGuiWin.o

C_DEPS += \
./src/lkdGui_source/source/lkdGuiBasic.d \
./src/lkdGui_source/source/lkdGuiColour.d \
./src/lkdGui_source/source/lkdGuiControl.d \
./src/lkdGui_source/source/lkdGuiFont.d \
./src/lkdGui_source/source/lkdGuiMenu.d \
./src/lkdGui_source/source/lkdGuiWin.d

# Each subdirectory must supply rules for building sources it contributes
src/lkdGui_source/source/%.o: ../src/lkdGui_source/source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	E:/LongXin/IDE/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1B -DOS_NONE  -O0 -g -Wall -c -fmessage-length=0 -pipe  -I"../" -I"../include" -I"../" -I"../APP/ALL" -I"../APP/BH1750" -I"../APP/BUZZER" -I"../APP/FAN" -I"../APP/HMC5883L" -I"../APP/KEY" -I"../APP/LCD" -I"../APP/LED" -I"../APP/LM35" -I"../APP/MOTOR" -I"../APP/MY_ADC" -I"../APP/MY_IIC" -I"../APP/MY_PWM" -I"../APP/MY_RTC" -I"../APP/MY_UART" -I"../APP/RESISTOR" -I"../APP/SMG" -I"../APP/TIM" -I"../APP/ULTRASOUND" -I"../APP/XIAOCHUANG" -I"../core/include" -I"../core/mips" -I"../libc" -I"../ls1x-drv/include" -I"../src/lkdGui_source/include" -I"../src/lkdGui_source/port" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

