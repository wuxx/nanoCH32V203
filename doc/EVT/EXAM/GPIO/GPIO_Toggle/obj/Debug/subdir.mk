################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/debug.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Debug/debug.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

