#include "servo.h"

Servo_Param_TypeDef Servo_Param;


uint8 Servo_Control(float angle)
{
    uint32 duty;

    Servo_Param.Head_Angle = angle;
    if (angle > Max_Angle || angle < Min_Angle)
    {
        return 0;
    }

    duty = (uint32)(angle/180*1000);
    pwm_duty(ATOM0_CH1_P33_9, duty+250);

    return 1;
}

void Servo_Param_Init(void)
{
    Servo_Param.Head_Angle = Mid_Angle;
    Servo_Param.Head_Angle_Input = Mid_Angle;
    Servo_Param.Head_Angle_Setup = Mid_Angle;
}
void Servo_Init(void)
{
    uint32 duty;

    Servo_Param_Init();
    duty = (uint32)((float)Mid_Angle/180*1000);
    gtm_pwm_init(ATOM0_CH1_P33_9, 50, duty + 250);
}
