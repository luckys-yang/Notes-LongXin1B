#
# Auto-Generated file. Do not edit!
#

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../libc/string/memchr.c \
../libc/string/memcmp.c \
../libc/string/memcpy.c \
../libc/string/memmove.c \
../libc/string/memset.c \
../libc/string/strcasecmp.c \
../libc/string/strcat.c \
../libc/string/strchr.c \
../libc/string/strcmp.c \
../libc/string/strcpy.c \
../libc/string/strdup.c \
../libc/string/strerror.c \
../libc/string/strlen.c \
../libc/string/strncasecmp.c \
../libc/string/strncat.c \
../libc/string/strncmp.c \
../libc/string/strncpy.c \
../libc/string/strnlen.c

OBJS += \
./libc/string/memchr.o \
./libc/string/memcmp.o \
./libc/string/memcpy.o \
./libc/string/memmove.o \
./libc/string/memset.o \
./libc/string/strcasecmp.o \
./libc/string/strcat.o \
./libc/string/strchr.o \
./libc/string/strcmp.o \
./libc/string/strcpy.o \
./libc/string/strdup.o \
./libc/string/strerror.o \
./libc/string/strlen.o \
./libc/string/strncasecmp.o \
./libc/string/strncat.o \
./libc/string/strncmp.o \
./libc/string/strncpy.o \
./libc/string/strnlen.o

C_DEPS += \
./libc/string/memchr.d \
./libc/string/memcmp.d \
./libc/string/memcpy.d \
./libc/string/memmove.d \
./libc/string/memset.d \
./libc/string/strcasecmp.d \
./libc/string/strcat.d \
./libc/string/strchr.d \
./libc/string/strcmp.d \
./libc/string/strcpy.d \
./libc/string/strdup.d \
./libc/string/strerror.d \
./libc/string/strlen.d \
./libc/string/strncasecmp.d \
./libc/string/strncat.d \
./libc/string/strncmp.d \
./libc/string/strncpy.d \
./libc/string/strnlen.d

# Each subdirectory must supply rules for building sources it contributes
libc/string/%.o: ../libc/string/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: SDE Lite C Compiler'
	E:/LongXin/IDE/LoongIDE/mips-2011.03/bin/mips-sde-elf-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1B -DOS_NONE  -O0 -g -Wall -c -fmessage-length=0 -pipe  -I"../" -I"../include" -I"../" -I"../APP/ALL" -I"../APP/BH1750" -I"../APP/BUZZER" -I"../APP/FAN" -I"../APP/HMC5883L" -I"../APP/KEY" -I"../APP/LCD" -I"../APP/LED" -I"../APP/LM35" -I"../APP/MOTOR" -I"../APP/MY_ADC" -I"../APP/MY_IIC" -I"../APP/MY_PWM" -I"../APP/MY_RTC" -I"../APP/MY_UART" -I"../APP/RESISTOR" -I"../APP/SMG" -I"../APP/TIM" -I"../APP/ULTRASOUND" -I"../APP/XIAOCHUANG" -I"../core/include" -I"../core/mips" -I"../libc" -I"../ls1x-drv/include" -I"../src/lkdGui_source/include" -I"../src/lkdGui_source/port" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

