################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/seekfree_libraries/zf_ccu6_pit.c \
../Libraries/seekfree_libraries/zf_eeprom.c \
../Libraries/seekfree_libraries/zf_eru.c \
../Libraries/seekfree_libraries/zf_eru_dma.c \
../Libraries/seekfree_libraries/zf_gpio.c \
../Libraries/seekfree_libraries/zf_gpt12.c \
../Libraries/seekfree_libraries/zf_gtm_pwm.c \
../Libraries/seekfree_libraries/zf_spi.c \
../Libraries/seekfree_libraries/zf_stm_systick.c \
../Libraries/seekfree_libraries/zf_uart.c \
../Libraries/seekfree_libraries/zf_vadc.c 

OBJS += \
./Libraries/seekfree_libraries/zf_ccu6_pit.o \
./Libraries/seekfree_libraries/zf_eeprom.o \
./Libraries/seekfree_libraries/zf_eru.o \
./Libraries/seekfree_libraries/zf_eru_dma.o \
./Libraries/seekfree_libraries/zf_gpio.o \
./Libraries/seekfree_libraries/zf_gpt12.o \
./Libraries/seekfree_libraries/zf_gtm_pwm.o \
./Libraries/seekfree_libraries/zf_spi.o \
./Libraries/seekfree_libraries/zf_stm_systick.o \
./Libraries/seekfree_libraries/zf_uart.o \
./Libraries/seekfree_libraries/zf_vadc.o 

COMPILED_SRCS += \
./Libraries/seekfree_libraries/zf_ccu6_pit.src \
./Libraries/seekfree_libraries/zf_eeprom.src \
./Libraries/seekfree_libraries/zf_eru.src \
./Libraries/seekfree_libraries/zf_eru_dma.src \
./Libraries/seekfree_libraries/zf_gpio.src \
./Libraries/seekfree_libraries/zf_gpt12.src \
./Libraries/seekfree_libraries/zf_gtm_pwm.src \
./Libraries/seekfree_libraries/zf_spi.src \
./Libraries/seekfree_libraries/zf_stm_systick.src \
./Libraries/seekfree_libraries/zf_uart.src \
./Libraries/seekfree_libraries/zf_vadc.src 

C_DEPS += \
./Libraries/seekfree_libraries/zf_ccu6_pit.d \
./Libraries/seekfree_libraries/zf_eeprom.d \
./Libraries/seekfree_libraries/zf_eru.d \
./Libraries/seekfree_libraries/zf_eru_dma.d \
./Libraries/seekfree_libraries/zf_gpio.d \
./Libraries/seekfree_libraries/zf_gpt12.d \
./Libraries/seekfree_libraries/zf_gtm_pwm.d \
./Libraries/seekfree_libraries/zf_spi.d \
./Libraries/seekfree_libraries/zf_stm_systick.d \
./Libraries/seekfree_libraries/zf_uart.d \
./Libraries/seekfree_libraries/zf_vadc.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/seekfree_libraries/%.src: ../Libraries/seekfree_libraries/%.c Libraries/seekfree_libraries/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_75/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/seekfree_libraries/%.o: ./Libraries/seekfree_libraries/%.src Libraries/seekfree_libraries/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


