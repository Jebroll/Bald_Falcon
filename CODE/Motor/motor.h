#ifndef _MOMENTUM_WHEEL_H
#define _MOMENTUM_WHEEL_H

#include "encoder.h"
#include "zf_gtm_pwm.h"
#include "stdio.h"
#include "private_common.h"

#define Motor_CHA    ATOM0_CH5_P02_5
#define Motor_CHB    ATOM0_CH4_P02_4


#define Motor_PWM_Freq        5000   //PWM的频率
#define Motor_Max_Speed       7200   //最大值为10 000, 即PWM_DUTY_MAX

/**************************驱动轮相关**************************/

typedef struct
{
        PID_TypeDef PID;
        float Speed;                //存放驱动轮当前速度
        float Speed_Setup;          //设置驱动轮的速度
        float Speed_Input;          //输入驱动轮的速度
}Speed_Param_TypeDef;
extern Speed_Param_TypeDef Speed_Param;

void Speed_Control(float target_speed);

/**************************驱动轮相关**************************/


void Motor_Init(void);
void Motor_Stop(void);
void Motor_Control(int duty);


#endif /*_MOMENTUM_WHEEL_H*/
