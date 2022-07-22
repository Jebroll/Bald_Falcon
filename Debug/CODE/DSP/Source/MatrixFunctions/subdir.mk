################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/DSP/Source/MatrixFunctions/MatrixFunctions.c \
../CODE/DSP/Source/MatrixFunctions/MatrixFunctionsF16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_add_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_add_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_add_q15.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_add_q31.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_init_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_init_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_init_q15.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_init_q31.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f64.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q15.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q31.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q7.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_scale_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_scale_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_scale_q15.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_scale_q31.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f64.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_sub_q15.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_sub_q31.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f64.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q15.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q31.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q7.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.c \
../CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.c 

OBJS += \
./CODE/DSP/Source/MatrixFunctions/MatrixFunctions.o \
./CODE/DSP/Source/MatrixFunctions/MatrixFunctionsF16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_q15.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_q31.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_q15.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_q31.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f64.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q15.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q31.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q7.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_q15.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_q31.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f64.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_q15.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_q31.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f64.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q15.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q31.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q7.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.o \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.o 

COMPILED_SRCS += \
./CODE/DSP/Source/MatrixFunctions/MatrixFunctions.src \
./CODE/DSP/Source/MatrixFunctions/MatrixFunctionsF16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_q15.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_q31.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_q15.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_q31.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f64.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q15.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q31.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q7.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_q15.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_q31.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f64.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_q15.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_q31.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f64.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q15.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q31.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q7.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.src \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.src 

C_DEPS += \
./CODE/DSP/Source/MatrixFunctions/MatrixFunctions.d \
./CODE/DSP/Source/MatrixFunctions/MatrixFunctionsF16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_q15.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_add_q31.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cholesky_f64.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q15.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_mult_q31.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q15.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_cmplx_trans_q31.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_q15.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_init_q31.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_inverse_f64.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_ldlt_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_ldlt_f64.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_f64.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q15.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_fast_q31.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_opt_q31.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q15.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q31.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_mult_q7.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_q15.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_scale_q31.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_lower_triangular_f64.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_solve_upper_triangular_f64.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_f64.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_q15.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_sub_q31.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_f64.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q15.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q31.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_trans_q7.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f16.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_f32.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q15.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q31.d \
./CODE/DSP/Source/MatrixFunctions/arm_mat_vec_mult_q7.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/DSP/Source/MatrixFunctions/%.src: ../CODE/DSP/Source/MatrixFunctions/%.c CODE/DSP/Source/MatrixFunctions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/FreeScale/ADS/work_space/Bald_Falcon_75/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/DSP/Source/MatrixFunctions/%.o: ./CODE/DSP/Source/MatrixFunctions/%.src CODE/DSP/Source/MatrixFunctions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


