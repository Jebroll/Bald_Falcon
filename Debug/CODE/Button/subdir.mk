################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/Button/button.c \
../CODE/Button/multi_button.c \
../CODE/Button/param_setup.c 

OBJS += \
./CODE/Button/button.o \
./CODE/Button/multi_button.o \
./CODE/Button/param_setup.o 

COMPILED_SRCS += \
./CODE/Button/button.src \
./CODE/Button/multi_button.src \
./CODE/Button/param_setup.src 

C_DEPS += \
./CODE/Button/button.d \
./CODE/Button/multi_button.d \
./CODE/Button/param_setup.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/Button/%.src: ../CODE/Button/%.c CODE/Button/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_55/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/Button/%.o: ./CODE/Button/%.src CODE/Button/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


