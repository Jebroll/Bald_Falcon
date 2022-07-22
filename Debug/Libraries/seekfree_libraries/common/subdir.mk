################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/seekfree_libraries/common/SEEKFREE_PRINTF.c \
../Libraries/seekfree_libraries/common/common.c \
../Libraries/seekfree_libraries/common/zf_assert.c 

OBJS += \
./Libraries/seekfree_libraries/common/SEEKFREE_PRINTF.o \
./Libraries/seekfree_libraries/common/common.o \
./Libraries/seekfree_libraries/common/zf_assert.o 

COMPILED_SRCS += \
./Libraries/seekfree_libraries/common/SEEKFREE_PRINTF.src \
./Libraries/seekfree_libraries/common/common.src \
./Libraries/seekfree_libraries/common/zf_assert.src 

C_DEPS += \
./Libraries/seekfree_libraries/common/SEEKFREE_PRINTF.d \
./Libraries/seekfree_libraries/common/common.d \
./Libraries/seekfree_libraries/common/zf_assert.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/seekfree_libraries/common/%.src: ../Libraries/seekfree_libraries/common/%.c Libraries/seekfree_libraries/common/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_75/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/seekfree_libraries/common/%.o: ./Libraries/seekfree_libraries/common/%.src Libraries/seekfree_libraries/common/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


