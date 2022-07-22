################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/DSP/Source/ControllerFunctions/ControllerFunctions.c \
../CODE/DSP/Source/ControllerFunctions/arm_pid_init_f32.c \
../CODE/DSP/Source/ControllerFunctions/arm_pid_init_q15.c \
../CODE/DSP/Source/ControllerFunctions/arm_pid_init_q31.c \
../CODE/DSP/Source/ControllerFunctions/arm_pid_reset_f32.c \
../CODE/DSP/Source/ControllerFunctions/arm_pid_reset_q15.c \
../CODE/DSP/Source/ControllerFunctions/arm_pid_reset_q31.c \
../CODE/DSP/Source/ControllerFunctions/arm_sin_cos_f32.c \
../CODE/DSP/Source/ControllerFunctions/arm_sin_cos_q31.c 

OBJS += \
./CODE/DSP/Source/ControllerFunctions/ControllerFunctions.o \
./CODE/DSP/Source/ControllerFunctions/arm_pid_init_f32.o \
./CODE/DSP/Source/ControllerFunctions/arm_pid_init_q15.o \
./CODE/DSP/Source/ControllerFunctions/arm_pid_init_q31.o \
./CODE/DSP/Source/ControllerFunctions/arm_pid_reset_f32.o \
./CODE/DSP/Source/ControllerFunctions/arm_pid_reset_q15.o \
./CODE/DSP/Source/ControllerFunctions/arm_pid_reset_q31.o \
./CODE/DSP/Source/ControllerFunctions/arm_sin_cos_f32.o \
./CODE/DSP/Source/ControllerFunctions/arm_sin_cos_q31.o 

COMPILED_SRCS += \
./CODE/DSP/Source/ControllerFunctions/ControllerFunctions.src \
./CODE/DSP/Source/ControllerFunctions/arm_pid_init_f32.src \
./CODE/DSP/Source/ControllerFunctions/arm_pid_init_q15.src \
./CODE/DSP/Source/ControllerFunctions/arm_pid_init_q31.src \
./CODE/DSP/Source/ControllerFunctions/arm_pid_reset_f32.src \
./CODE/DSP/Source/ControllerFunctions/arm_pid_reset_q15.src \
./CODE/DSP/Source/ControllerFunctions/arm_pid_reset_q31.src \
./CODE/DSP/Source/ControllerFunctions/arm_sin_cos_f32.src \
./CODE/DSP/Source/ControllerFunctions/arm_sin_cos_q31.src 

C_DEPS += \
./CODE/DSP/Source/ControllerFunctions/ControllerFunctions.d \
./CODE/DSP/Source/ControllerFunctions/arm_pid_init_f32.d \
./CODE/DSP/Source/ControllerFunctions/arm_pid_init_q15.d \
./CODE/DSP/Source/ControllerFunctions/arm_pid_init_q31.d \
./CODE/DSP/Source/ControllerFunctions/arm_pid_reset_f32.d \
./CODE/DSP/Source/ControllerFunctions/arm_pid_reset_q15.d \
./CODE/DSP/Source/ControllerFunctions/arm_pid_reset_q31.d \
./CODE/DSP/Source/ControllerFunctions/arm_sin_cos_f32.d \
./CODE/DSP/Source/ControllerFunctions/arm_sin_cos_q31.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/DSP/Source/ControllerFunctions/%.src: ../CODE/DSP/Source/ControllerFunctions/%.c CODE/DSP/Source/ControllerFunctions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_75/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/DSP/Source/ControllerFunctions/%.o: ./CODE/DSP/Source/ControllerFunctions/%.src CODE/DSP/Source/ControllerFunctions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


