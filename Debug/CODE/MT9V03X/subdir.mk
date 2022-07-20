################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/MT9V03X/Draw_Line.c \
../CODE/MT9V03X/Fixed_Middle_Line.c \
../CODE/MT9V03X/MY_Common.c \
../CODE/MT9V03X/MY_Imag_Process.c 

OBJS += \
./CODE/MT9V03X/Draw_Line.o \
./CODE/MT9V03X/Fixed_Middle_Line.o \
./CODE/MT9V03X/MY_Common.o \
./CODE/MT9V03X/MY_Imag_Process.o 

COMPILED_SRCS += \
./CODE/MT9V03X/Draw_Line.src \
./CODE/MT9V03X/Fixed_Middle_Line.src \
./CODE/MT9V03X/MY_Common.src \
./CODE/MT9V03X/MY_Imag_Process.src 

C_DEPS += \
./CODE/MT9V03X/Draw_Line.d \
./CODE/MT9V03X/Fixed_Middle_Line.d \
./CODE/MT9V03X/MY_Common.d \
./CODE/MT9V03X/MY_Imag_Process.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/MT9V03X/%.src: ../CODE/MT9V03X/%.c CODE/MT9V03X/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_55/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/MT9V03X/%.o: ./CODE/MT9V03X/%.src CODE/MT9V03X/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


