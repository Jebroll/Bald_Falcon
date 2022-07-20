################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Asc/IfxAsclin_Asc.c 

OBJS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Asc/IfxAsclin_Asc.o 

COMPILED_SRCS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Asc/IfxAsclin_Asc.src 

C_DEPS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Asc/IfxAsclin_Asc.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Asc/%.src: ../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Asc/%.c Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Asc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_55/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Asc/%.o: ./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Asc/%.src Libraries/infineon_libraries/iLLD/TC26B/Tricore/Asclin/Asc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


