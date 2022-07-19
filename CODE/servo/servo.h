#ifndef _SERVO_H
#define _SERVO_H


#include "headfile.h"
#include "stdio.h"


/******舵机角度范围*******/
#define Min_Angle 50
#define Mid_Angle 85
#define Max_Angle 120
/******舵机角度范围*******/

typedef struct{
        float Head_Angle;               //存放舵机当前角度
        float Head_Angle_Input;         //输入舵机的角度
        float Head_Angle_Setup;         //设置舵机的角度
}Servo_Param_TypeDef;
extern Servo_Param_TypeDef Servo_Param;

void Servo_Init(void);
uint8 Servo_Control(float angle);


#endif /*_SERVO_H*/
