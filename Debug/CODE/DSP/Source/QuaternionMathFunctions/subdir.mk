################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.c \
../CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.c \
../CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.c \
../CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.c \
../CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.c \
../CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.c \
../CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.c \
../CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.c \
../CODE/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.c 

OBJS += \
./CODE/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.o \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.o \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.o \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.o \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.o \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.o \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.o \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.o \
./CODE/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.o 

COMPILED_SRCS += \
./CODE/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.src \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.src \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.src \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.src \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.src \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.src \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.src \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.src \
./CODE/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.src 

C_DEPS += \
./CODE/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.d \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion2rotation_f32.d \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_conjugate_f32.d \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_inverse_f32.d \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_norm_f32.d \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_normalize_f32.d \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_f32.d \
./CODE/DSP/Source/QuaternionMathFunctions/arm_quaternion_product_single_f32.d \
./CODE/DSP/Source/QuaternionMathFunctions/arm_rotation2quaternion_f32.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/DSP/Source/QuaternionMathFunctions/%.src: ../CODE/DSP/Source/QuaternionMathFunctions/%.c CODE/DSP/Source/QuaternionMathFunctions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_75/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/DSP/Source/QuaternionMathFunctions/%.o: ./CODE/DSP/Source/QuaternionMathFunctions/%.src CODE/DSP/Source/QuaternionMathFunctions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


