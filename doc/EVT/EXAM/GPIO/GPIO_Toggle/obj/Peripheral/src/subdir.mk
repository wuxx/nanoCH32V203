################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_adc.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_bkp.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_can.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_crc.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_dbgmcu.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_dma.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_exti.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_flash.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_gpio.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_i2c.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_iwdg.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_misc.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_opa.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_pwr.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_rcc.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_rtc.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_spi.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_tim.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_usart.c \
F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_wwdg.c 

OBJS += \
./Peripheral/src/ch32v20x_adc.o \
./Peripheral/src/ch32v20x_bkp.o \
./Peripheral/src/ch32v20x_can.o \
./Peripheral/src/ch32v20x_crc.o \
./Peripheral/src/ch32v20x_dbgmcu.o \
./Peripheral/src/ch32v20x_dma.o \
./Peripheral/src/ch32v20x_exti.o \
./Peripheral/src/ch32v20x_flash.o \
./Peripheral/src/ch32v20x_gpio.o \
./Peripheral/src/ch32v20x_i2c.o \
./Peripheral/src/ch32v20x_iwdg.o \
./Peripheral/src/ch32v20x_misc.o \
./Peripheral/src/ch32v20x_opa.o \
./Peripheral/src/ch32v20x_pwr.o \
./Peripheral/src/ch32v20x_rcc.o \
./Peripheral/src/ch32v20x_rtc.o \
./Peripheral/src/ch32v20x_spi.o \
./Peripheral/src/ch32v20x_tim.o \
./Peripheral/src/ch32v20x_usart.o \
./Peripheral/src/ch32v20x_wwdg.o 

C_DEPS += \
./Peripheral/src/ch32v20x_adc.d \
./Peripheral/src/ch32v20x_bkp.d \
./Peripheral/src/ch32v20x_can.d \
./Peripheral/src/ch32v20x_crc.d \
./Peripheral/src/ch32v20x_dbgmcu.d \
./Peripheral/src/ch32v20x_dma.d \
./Peripheral/src/ch32v20x_exti.d \
./Peripheral/src/ch32v20x_flash.d \
./Peripheral/src/ch32v20x_gpio.d \
./Peripheral/src/ch32v20x_i2c.d \
./Peripheral/src/ch32v20x_iwdg.d \
./Peripheral/src/ch32v20x_misc.d \
./Peripheral/src/ch32v20x_opa.d \
./Peripheral/src/ch32v20x_pwr.d \
./Peripheral/src/ch32v20x_rcc.d \
./Peripheral/src/ch32v20x_rtc.d \
./Peripheral/src/ch32v20x_spi.d \
./Peripheral/src/ch32v20x_tim.d \
./Peripheral/src/ch32v20x_usart.d \
./Peripheral/src/ch32v20x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/ch32v20x_adc.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_bkp.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_bkp.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_can.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_can.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_crc.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_crc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_dbgmcu.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_dbgmcu.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_dma.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_dma.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_exti.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_flash.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_gpio.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_i2c.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_i2c.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_iwdg.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_iwdg.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_misc.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_misc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_opa.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_opa.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_pwr.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_pwr.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_rcc.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_rcc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_rtc.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_rtc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_spi.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_tim.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_tim.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_usart.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_usart.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v20x_wwdg.o: F:/oss/nanoCH32V203/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_wwdg.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Debug" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Core" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\GPIO\GPIO_Toggle\User" -I"F:\oss\nanoCH32V203\doc\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

