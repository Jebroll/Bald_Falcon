################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/FOC/adc.c \
../CODE/FOC/brushless_motor.c \
../CODE/FOC/ccu6_pwm.c \
../CODE/FOC/clark.c \
../CODE/FOC/fast_sin_cos_f32.c \
../CODE/FOC/hall.c \
../CODE/FOC/move_filter.c \
../CODE/FOC/park.c 

OBJS += \
./CODE/FOC/adc.o \
./CODE/FOC/brushless_motor.o \
./CODE/FOC/ccu6_pwm.o \
./CODE/FOC/clark.o \
./CODE/FOC/fast_sin_cos_f32.o \
./CODE/FOC/hall.o \
./CODE/FOC/move_filter.o \
./CODE/FOC/park.o 

COMPILED_SRCS += \
./CODE/FOC/adc.src \
./CODE/FOC/brushless_motor.src \
./CODE/FOC/ccu6_pwm.src \
./CODE/FOC/clark.src \
./CODE/FOC/fast_sin_cos_f32.src \
./CODE/FOC/hall.src \
./CODE/FOC/move_filter.src \
./CODE/FOC/park.src 

C_DEPS += \
./CODE/FOC/adc.d \
./CODE/FOC/brushless_motor.d \
./CODE/FOC/ccu6_pwm.d \
./CODE/FOC/clark.d \
./CODE/FOC/fast_sin_cos_f32.d \
./CODE/FOC/hall.d \
./CODE/FOC/move_filter.d \
./CODE/FOC/park.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/FOC/%.src: ../CODE/FOC/%.c CODE/FOC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_55/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/FOC/%.o: ./CODE/FOC/%.src CODE/FOC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


