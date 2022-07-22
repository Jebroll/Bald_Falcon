################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/DSP/Source/CommonTables/CommonTables.c \
../CODE/DSP/Source/CommonTables/CommonTablesF16.c \
../CODE/DSP/Source/CommonTables/arm_common_tables.c \
../CODE/DSP/Source/CommonTables/arm_common_tables_f16.c \
../CODE/DSP/Source/CommonTables/arm_const_structs.c \
../CODE/DSP/Source/CommonTables/arm_const_structs_f16.c \
../CODE/DSP/Source/CommonTables/arm_mve_tables.c \
../CODE/DSP/Source/CommonTables/arm_mve_tables_f16.c 

OBJS += \
./CODE/DSP/Source/CommonTables/CommonTables.o \
./CODE/DSP/Source/CommonTables/CommonTablesF16.o \
./CODE/DSP/Source/CommonTables/arm_common_tables.o \
./CODE/DSP/Source/CommonTables/arm_common_tables_f16.o \
./CODE/DSP/Source/CommonTables/arm_const_structs.o \
./CODE/DSP/Source/CommonTables/arm_const_structs_f16.o \
./CODE/DSP/Source/CommonTables/arm_mve_tables.o \
./CODE/DSP/Source/CommonTables/arm_mve_tables_f16.o 

COMPILED_SRCS += \
./CODE/DSP/Source/CommonTables/CommonTables.src \
./CODE/DSP/Source/CommonTables/CommonTablesF16.src \
./CODE/DSP/Source/CommonTables/arm_common_tables.src \
./CODE/DSP/Source/CommonTables/arm_common_tables_f16.src \
./CODE/DSP/Source/CommonTables/arm_const_structs.src \
./CODE/DSP/Source/CommonTables/arm_const_structs_f16.src \
./CODE/DSP/Source/CommonTables/arm_mve_tables.src \
./CODE/DSP/Source/CommonTables/arm_mve_tables_f16.src 

C_DEPS += \
./CODE/DSP/Source/CommonTables/CommonTables.d \
./CODE/DSP/Source/CommonTables/CommonTablesF16.d \
./CODE/DSP/Source/CommonTables/arm_common_tables.d \
./CODE/DSP/Source/CommonTables/arm_common_tables_f16.d \
./CODE/DSP/Source/CommonTables/arm_const_structs.d \
./CODE/DSP/Source/CommonTables/arm_const_structs_f16.d \
./CODE/DSP/Source/CommonTables/arm_mve_tables.d \
./CODE/DSP/Source/CommonTables/arm_mve_tables_f16.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/DSP/Source/CommonTables/%.src: ../CODE/DSP/Source/CommonTables/%.c CODE/DSP/Source/CommonTables/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_75/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/DSP/Source/CommonTables/%.o: ./CODE/DSP/Source/CommonTables/%.src CODE/DSP/Source/CommonTables/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


