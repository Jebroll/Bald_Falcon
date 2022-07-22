#ifndef _BUSHLESS_MOTOR_H
#define _BUSHLESS_MOTOR_H

#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"
#include "IfxCcu6.h"
#include "ccu6_pwm.h"
#include "IfxCcu6.h"
#include "clark.h"
#include "park.h"
#include "hall.h"
#include "move_filter.h"
#include "private_common.h"


#define Q_DEAD_PERIOD               1.0         //q轴死区
#define PWM_PIT_NUM                 60*FPWM
#define BUS_VOLTAGE                 12          //母线电压
#define POLEPAIRS                   7           //电机极对数
#define CURRENT_CLOSE_LOOP_ENABLE   0           //电流环控制开关


typedef enum
{
    FORWARD,    //正转
    REVERSE,    //反转
}MOTOR_DIR_enum;

typedef struct
{
    int32 speed;                //当前速度
    int32 last_speed;           //上一时刻速度
    MOTOR_DIR_enum actual_dir;  //当前转子旋转方向
    MOTOR_DIR_enum dir;         //设定的转子旋转方向
}BLmotor_Typedef;

typedef struct
{
    double x;
    double y;
    double z;
}Instrument_Typedef;            //为了减少计算量的中间变量结构体

typedef struct
{
    double ta;                  //基矢量作用时间a
    double tb;                  //基矢量作用时间b
}VectorTime_Typedef;

typedef struct
{
    uint16 AH;                  //A上桥定时器比较值
    uint16 AL;                  //A下桥定时器比较值
    uint16 BH;
    uint16 BL;
    uint16 CH;
    uint16 CL;
}Period_Typedef;

typedef struct
{
    PID_TypeDef d;
    PID_TypeDef q;
}Current_CL_Typedef;            //d、q轴PID参数结构体

typedef struct
{
    BLmotor_Typedef BLmotor;        //电机参数
    ADC_Typedef Adc;                //adc采集
    CLARK_Typedef V_Clark;          //Alpha、Beta输入
    CLARK_Typedef I_Clrak;          //Alpha、Beta反馈
    PARK_Typedef Ref_Park;          //d、q目标值
    PARK_Typedef I_Park;            //d、q返回值
    PARK_Typedef Park_In;           //d、q输入值
    Instrument_Typedef tool;        //SVPWM算法中间量
    VectorTime_Typedef Vector;      //矢量作用时间
    HALL_Typedef hall;              //霍尔传感器数据
    uint8  N;                       //电角度扇区
    double theta;                   //电角度
    Period_Typedef Period;          //各桥定时器比较值
    Current_CL_Typedef Current_CL;  //电流环PID参数
}FOC_Parm_Typedef;
extern FOC_Parm_Typedef FOC;

void Mos_All_High_Open(uint16 periodAH, uint16 periodBH, uint16 periodCH);
void Mos_All_Low_Open(void);
void SVPWM_Algorithm(uint8 Udc, uint16 T);
void Momemtum_Motor_Control(float duty);
void FOC_TEST_PRINTF(void);
void FOC_Init(void);

#endif/*_BUSHLESS_MOTOR_H*/
