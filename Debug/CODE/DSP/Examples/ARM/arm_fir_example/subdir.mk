################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/DSP/Examples/ARM/arm_fir_example/arm_fir_data.c \
../CODE/DSP/Examples/ARM/arm_fir_example/arm_fir_example_f32.c \
../CODE/DSP/Examples/ARM/arm_fir_example/math_helper.c 

OBJS += \
./CODE/DSP/Examples/ARM/arm_fir_example/arm_fir_data.o \
./CODE/DSP/Examples/ARM/arm_fir_example/arm_fir_example_f32.o \
./CODE/DSP/Examples/ARM/arm_fir_example/math_helper.o 

COMPILED_SRCS += \
./CODE/DSP/Examples/ARM/arm_fir_example/arm_fir_data.src \
./CODE/DSP/Examples/ARM/arm_fir_example/arm_fir_example_f32.src \
./CODE/DSP/Examples/ARM/arm_fir_example/math_helper.src 

C_DEPS += \
./CODE/DSP/Examples/ARM/arm_fir_example/arm_fir_data.d \
./CODE/DSP/Examples/ARM/arm_fir_example/arm_fir_example_f32.d \
./CODE/DSP/Examples/ARM/arm_fir_example/math_helper.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/DSP/Examples/ARM/arm_fir_example/%.src: ../CODE/DSP/Examples/ARM/arm_fir_example/%.c CODE/DSP/Examples/ARM/arm_fir_example/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_75/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/DSP/Examples/ARM/arm_fir_example/%.o: ./CODE/DSP/Examples/ARM/arm_fir_example/%.src CODE/DSP/Examples/ARM/arm_fir_example/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


