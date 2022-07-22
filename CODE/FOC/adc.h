#ifndef _ADC_H
#define _ADC_H

#include "zf_vadc.h"
#include "common.h"
#include "move_filter.h"
#include "SysSe/Math/Ifx_LowPassPt1F32.h"

#define ADC_NUMBER              ADC_2           //定义ADC编号

#define A_PHASE_PORT            ADC2_CH3_A35     //A相电流读取通道
#define B_PHASE_PORT            ADC2_CH4_A36     //B相电流读取通道
//#define C_PHASE_PORT            ADC2_CH5_A37     //C相电流读取通道

#define Joystick_Y              ADC2_CH5_A37
#define Joystick_SW             ADC2_CH6_A38


#define FILTER_ENABLE           0

typedef struct
{
    double voltage_bus;         //母线电流
    double current_a;           //A相电流
    double current_b;           //B相电流
    double current_c;           //C相电流
}ADC_Typedef;



ADC_Typedef Adc_Read(void);
void Adc_Collection_Init(void);

#endif /*_ADC_H*/
