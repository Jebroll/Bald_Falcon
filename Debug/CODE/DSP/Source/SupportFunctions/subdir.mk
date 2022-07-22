################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/DSP/Source/SupportFunctions/SupportFunctions.c \
../CODE/DSP/Source/SupportFunctions/SupportFunctionsF16.c \
../CODE/DSP/Source/SupportFunctions/arm_barycenter_f16.c \
../CODE/DSP/Source/SupportFunctions/arm_barycenter_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_bubble_sort_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_copy_f16.c \
../CODE/DSP/Source/SupportFunctions/arm_copy_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_copy_f64.c \
../CODE/DSP/Source/SupportFunctions/arm_copy_q15.c \
../CODE/DSP/Source/SupportFunctions/arm_copy_q31.c \
../CODE/DSP/Source/SupportFunctions/arm_copy_q7.c \
../CODE/DSP/Source/SupportFunctions/arm_f16_to_float.c \
../CODE/DSP/Source/SupportFunctions/arm_f16_to_q15.c \
../CODE/DSP/Source/SupportFunctions/arm_fill_f16.c \
../CODE/DSP/Source/SupportFunctions/arm_fill_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_fill_f64.c \
../CODE/DSP/Source/SupportFunctions/arm_fill_q15.c \
../CODE/DSP/Source/SupportFunctions/arm_fill_q31.c \
../CODE/DSP/Source/SupportFunctions/arm_fill_q7.c \
../CODE/DSP/Source/SupportFunctions/arm_float_to_f16.c \
../CODE/DSP/Source/SupportFunctions/arm_float_to_q15.c \
../CODE/DSP/Source/SupportFunctions/arm_float_to_q31.c \
../CODE/DSP/Source/SupportFunctions/arm_float_to_q7.c \
../CODE/DSP/Source/SupportFunctions/arm_heap_sort_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_insertion_sort_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_merge_sort_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_q15_to_f16.c \
../CODE/DSP/Source/SupportFunctions/arm_q15_to_float.c \
../CODE/DSP/Source/SupportFunctions/arm_q15_to_q31.c \
../CODE/DSP/Source/SupportFunctions/arm_q15_to_q7.c \
../CODE/DSP/Source/SupportFunctions/arm_q31_to_float.c \
../CODE/DSP/Source/SupportFunctions/arm_q31_to_q15.c \
../CODE/DSP/Source/SupportFunctions/arm_q31_to_q7.c \
../CODE/DSP/Source/SupportFunctions/arm_q7_to_float.c \
../CODE/DSP/Source/SupportFunctions/arm_q7_to_q15.c \
../CODE/DSP/Source/SupportFunctions/arm_q7_to_q31.c \
../CODE/DSP/Source/SupportFunctions/arm_quick_sort_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_selection_sort_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_sort_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_sort_init_f32.c \
../CODE/DSP/Source/SupportFunctions/arm_weighted_sum_f16.c \
../CODE/DSP/Source/SupportFunctions/arm_weighted_sum_f32.c 

OBJS += \
./CODE/DSP/Source/SupportFunctions/SupportFunctions.o \
./CODE/DSP/Source/SupportFunctions/SupportFunctionsF16.o \
./CODE/DSP/Source/SupportFunctions/arm_barycenter_f16.o \
./CODE/DSP/Source/SupportFunctions/arm_barycenter_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_bubble_sort_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_copy_f16.o \
./CODE/DSP/Source/SupportFunctions/arm_copy_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_copy_f64.o \
./CODE/DSP/Source/SupportFunctions/arm_copy_q15.o \
./CODE/DSP/Source/SupportFunctions/arm_copy_q31.o \
./CODE/DSP/Source/SupportFunctions/arm_copy_q7.o \
./CODE/DSP/Source/SupportFunctions/arm_f16_to_float.o \
./CODE/DSP/Source/SupportFunctions/arm_f16_to_q15.o \
./CODE/DSP/Source/SupportFunctions/arm_fill_f16.o \
./CODE/DSP/Source/SupportFunctions/arm_fill_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_fill_f64.o \
./CODE/DSP/Source/SupportFunctions/arm_fill_q15.o \
./CODE/DSP/Source/SupportFunctions/arm_fill_q31.o \
./CODE/DSP/Source/SupportFunctions/arm_fill_q7.o \
./CODE/DSP/Source/SupportFunctions/arm_float_to_f16.o \
./CODE/DSP/Source/SupportFunctions/arm_float_to_q15.o \
./CODE/DSP/Source/SupportFunctions/arm_float_to_q31.o \
./CODE/DSP/Source/SupportFunctions/arm_float_to_q7.o \
./CODE/DSP/Source/SupportFunctions/arm_heap_sort_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_insertion_sort_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_merge_sort_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_f16.o \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_float.o \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_q31.o \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_q7.o \
./CODE/DSP/Source/SupportFunctions/arm_q31_to_float.o \
./CODE/DSP/Source/SupportFunctions/arm_q31_to_q15.o \
./CODE/DSP/Source/SupportFunctions/arm_q31_to_q7.o \
./CODE/DSP/Source/SupportFunctions/arm_q7_to_float.o \
./CODE/DSP/Source/SupportFunctions/arm_q7_to_q15.o \
./CODE/DSP/Source/SupportFunctions/arm_q7_to_q31.o \
./CODE/DSP/Source/SupportFunctions/arm_quick_sort_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_selection_sort_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_sort_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_sort_init_f32.o \
./CODE/DSP/Source/SupportFunctions/arm_weighted_sum_f16.o \
./CODE/DSP/Source/SupportFunctions/arm_weighted_sum_f32.o 

COMPILED_SRCS += \
./CODE/DSP/Source/SupportFunctions/SupportFunctions.src \
./CODE/DSP/Source/SupportFunctions/SupportFunctionsF16.src \
./CODE/DSP/Source/SupportFunctions/arm_barycenter_f16.src \
./CODE/DSP/Source/SupportFunctions/arm_barycenter_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_bubble_sort_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_copy_f16.src \
./CODE/DSP/Source/SupportFunctions/arm_copy_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_copy_f64.src \
./CODE/DSP/Source/SupportFunctions/arm_copy_q15.src \
./CODE/DSP/Source/SupportFunctions/arm_copy_q31.src \
./CODE/DSP/Source/SupportFunctions/arm_copy_q7.src \
./CODE/DSP/Source/SupportFunctions/arm_f16_to_float.src \
./CODE/DSP/Source/SupportFunctions/arm_f16_to_q15.src \
./CODE/DSP/Source/SupportFunctions/arm_fill_f16.src \
./CODE/DSP/Source/SupportFunctions/arm_fill_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_fill_f64.src \
./CODE/DSP/Source/SupportFunctions/arm_fill_q15.src \
./CODE/DSP/Source/SupportFunctions/arm_fill_q31.src \
./CODE/DSP/Source/SupportFunctions/arm_fill_q7.src \
./CODE/DSP/Source/SupportFunctions/arm_float_to_f16.src \
./CODE/DSP/Source/SupportFunctions/arm_float_to_q15.src \
./CODE/DSP/Source/SupportFunctions/arm_float_to_q31.src \
./CODE/DSP/Source/SupportFunctions/arm_float_to_q7.src \
./CODE/DSP/Source/SupportFunctions/arm_heap_sort_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_insertion_sort_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_merge_sort_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_f16.src \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_float.src \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_q31.src \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_q7.src \
./CODE/DSP/Source/SupportFunctions/arm_q31_to_float.src \
./CODE/DSP/Source/SupportFunctions/arm_q31_to_q15.src \
./CODE/DSP/Source/SupportFunctions/arm_q31_to_q7.src \
./CODE/DSP/Source/SupportFunctions/arm_q7_to_float.src \
./CODE/DSP/Source/SupportFunctions/arm_q7_to_q15.src \
./CODE/DSP/Source/SupportFunctions/arm_q7_to_q31.src \
./CODE/DSP/Source/SupportFunctions/arm_quick_sort_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_selection_sort_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_sort_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_sort_init_f32.src \
./CODE/DSP/Source/SupportFunctions/arm_weighted_sum_f16.src \
./CODE/DSP/Source/SupportFunctions/arm_weighted_sum_f32.src 

C_DEPS += \
./CODE/DSP/Source/SupportFunctions/SupportFunctions.d \
./CODE/DSP/Source/SupportFunctions/SupportFunctionsF16.d \
./CODE/DSP/Source/SupportFunctions/arm_barycenter_f16.d \
./CODE/DSP/Source/SupportFunctions/arm_barycenter_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_bubble_sort_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_copy_f16.d \
./CODE/DSP/Source/SupportFunctions/arm_copy_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_copy_f64.d \
./CODE/DSP/Source/SupportFunctions/arm_copy_q15.d \
./CODE/DSP/Source/SupportFunctions/arm_copy_q31.d \
./CODE/DSP/Source/SupportFunctions/arm_copy_q7.d \
./CODE/DSP/Source/SupportFunctions/arm_f16_to_float.d \
./CODE/DSP/Source/SupportFunctions/arm_f16_to_q15.d \
./CODE/DSP/Source/SupportFunctions/arm_fill_f16.d \
./CODE/DSP/Source/SupportFunctions/arm_fill_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_fill_f64.d \
./CODE/DSP/Source/SupportFunctions/arm_fill_q15.d \
./CODE/DSP/Source/SupportFunctions/arm_fill_q31.d \
./CODE/DSP/Source/SupportFunctions/arm_fill_q7.d \
./CODE/DSP/Source/SupportFunctions/arm_float_to_f16.d \
./CODE/DSP/Source/SupportFunctions/arm_float_to_q15.d \
./CODE/DSP/Source/SupportFunctions/arm_float_to_q31.d \
./CODE/DSP/Source/SupportFunctions/arm_float_to_q7.d \
./CODE/DSP/Source/SupportFunctions/arm_heap_sort_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_insertion_sort_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_merge_sort_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_f16.d \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_float.d \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_q31.d \
./CODE/DSP/Source/SupportFunctions/arm_q15_to_q7.d \
./CODE/DSP/Source/SupportFunctions/arm_q31_to_float.d \
./CODE/DSP/Source/SupportFunctions/arm_q31_to_q15.d \
./CODE/DSP/Source/SupportFunctions/arm_q31_to_q7.d \
./CODE/DSP/Source/SupportFunctions/arm_q7_to_float.d \
./CODE/DSP/Source/SupportFunctions/arm_q7_to_q15.d \
./CODE/DSP/Source/SupportFunctions/arm_q7_to_q31.d \
./CODE/DSP/Source/SupportFunctions/arm_quick_sort_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_selection_sort_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_sort_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_sort_init_f32.d \
./CODE/DSP/Source/SupportFunctions/arm_weighted_sum_f16.d \
./CODE/DSP/Source/SupportFunctions/arm_weighted_sum_f32.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/DSP/Source/SupportFunctions/%.src: ../CODE/DSP/Source/SupportFunctions/%.c CODE/DSP/Source/SupportFunctions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_75/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/DSP/Source/SupportFunctions/%.o: ./CODE/DSP/Source/SupportFunctions/%.src CODE/DSP/Source/SupportFunctions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


