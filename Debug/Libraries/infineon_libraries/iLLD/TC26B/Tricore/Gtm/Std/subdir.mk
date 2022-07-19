################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm.c \
../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Atom.c \
../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Cmu.c \
../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Dpll.c \
../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tbu.c \
../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tim.c \
../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tom.c 

OBJS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm.o \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Atom.o \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Cmu.o \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Dpll.o \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tbu.o \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tim.o \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tom.o 

COMPILED_SRCS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm.src \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Atom.src \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Cmu.src \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Dpll.src \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tbu.src \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tim.src \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tom.src 

C_DEPS += \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm.d \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Atom.d \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Cmu.d \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Dpll.d \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tbu.d \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tim.d \
./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/IfxGtm_Tom.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/%.src: ../Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/%.c Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/%.o: ./Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/%.src Libraries/infineon_libraries/iLLD/TC26B/Tricore/Gtm/Std/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


