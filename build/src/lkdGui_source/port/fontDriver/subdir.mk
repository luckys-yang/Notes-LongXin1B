#
# Auto-Generated file. Do not edit!
#

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/lkdGui_source/port/fontDriver/ASCII_16_32.c \
../src/lkdGui_source/port/fontDriver/ASCII_5_7.c \
../src/lkdGui_source/port/fontDriver/ASCII_64_64.c \
../src/lkdGui_source/port/fontDriver/ASCII_6_12.c \
../src/lkdGui_source/port/fontDriver/ASCII_8_16.c \
../src/lkdGui_source/port/fontDriver/GB2312_12_12.c \
../src/lkdGui_source/port/fontDriver/GB2312_16_16.c \
../src/lkdGui_source/port/fontDriver/GB2312_32_32.c

OBJS += \
./src/lkdGui_source/port/fontDriver/ASCII_16_32.o \
./src/lkdGui_source/port/fontDriver/ASCII_5_7.o \
./src/lkdGui_source/port/fontDriver/ASCII_64_64.o \
./src/lkdGui_source/port/fontDriver/ASCII_6_12.o \
./src/lkdGui_source/port/fontDriver/ASCII_8_16.o \
./src/lkdGui_source/port/fontDriver/GB2312_12_12.o \
./src/lkdGui_source/port/fontDriver/GB2312_16_16.o \
./src/lkdGui_source/port/fontDriver/GB2312_32_32.o

C_DEPS += \
./src/lkdGui_source/port/fontDriver/ASCII_16_32.d \
./src/lkdGui_source/port/fontDriver/ASCII_5_7.d \
./src/lkdGui_source/port/fontDriver/ASCII_64_64.d \
./src/lkdGui_source/port/fontDriver/ASCII_6_12.d \
./src/lkdGui_source/port/fontDriver/ASCII_8_16.d \
./src/lkdGui_source/port/fontDriver/GB2312_12_12.d \
./src/lkdGui_source/port/fontDriver/GB2312_16_16.d \
./src/lkdGui_source/port/fontDriver/GB2312_32_32.d

# Each subdirectory must supply rules for building sources it contributes
src/lkdGui_source/port/fontDriver/%.o: ../src/lkdGui_source/port/fontDriver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	E:/LongXin/IDE/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1B -DOS_NONE  -O0 -g -Wall -c -fmessage-length=0 -pipe -I"../" -I"../include" -I"../APP/ALL" -I"../APP/BH1750" -I"../APP/BUZZER" -I"../APP/FAN" -I"../APP/HMC5883L" -I"../APP/KEY" -I"../APP/LCD" -I"../APP/LED" -I"../APP/LM35" -I"../APP/MOTOR" -I"../APP/MY_ADC" -I"../APP/MY_IIC" -I"../APP/MY_PWM" -I"../APP/MY_RTC" -I"../APP/MY_UART" -I"../APP/RESISTOR" -I"../APP/SMG" -I"../APP/TIM" -I"../APP/ULTRASOUND" -I"../APP/XIAOCHUANG" -I"../core/include" -I"../core/mips" -I"../libc" -I"../ls1x-drv/include" -I"../src/lkdGui_source/include" -I"../src/lkdGui_source/port" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

