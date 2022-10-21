################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Startup/startup_ch32v20x_D6.S 

OBJS += \
./Startup/startup_ch32v20x_D6.o 

S_UPPER_DEPS += \
./Startup/startup_ch32v20x_D6.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/startup_ch32v20x_D6.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Startup/startup_ch32v20x_D6.S
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -x assembler -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

