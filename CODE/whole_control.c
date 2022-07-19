#include "whole_control.h"

uint8 start_stop_flag = 1;

/**
 * @brief  曲线转弯
 * @note
 * @param  angle:目标角度
 * @retval none
 */
void Smooth_Change_Servo(float angle)
{
    float error = Servo_Param.Head_Angle_Input - angle;
    Servo_Param.Head_Angle_Input -= 0.05*error;
    Servo_Control(Servo_Param.Head_Angle_Input);
}

/**
 * @brief  曲线变速
 * @note
 * @param  speed:目标速度
 * @retval
 */
void Smooth_Change_Speed(float speed)
{
    if (speed <= 0) speed = 0;

    float error = Speed_Param.Speed_Input - speed;
    Speed_Param.Speed_Input -= 0.025*error;
    Speed_Control(Speed_Param.Speed_Input);
}


void Straight_Line_MODE(float error1)//偏左正，偏右负
{
    float Angle_PWM, error;
    static float last_error = 0, llast_error = 0;

    error = error1 - 0;

    Angle_PWM = -1.4 * (error - last_error) +
                -1.7 * (error - 2*last_error + llast_error);

    llast_error = last_error;
    last_error = error;

    Servo_Param.Head_Angle_Setup += Angle_PWM;
}

void Exist_Garage(void)
{
    static uint16 delay_count;

    Total_Image.OUTPUT_ERROR = -14;
    delay_count++;
    if (delay_count >= 350)
    {
        start_stop_flag = 0;
        Total_Image.road_type = road_normal;
    }
}

void Enter_Graage(void)
{
    static uint16 delay_count;

    start_stop_flag = 1;
    delay_count++;
    if (delay_count % 15 == 0)
    {
        Speed_Param.Speed_Setup--;
        Total_Image.OUTPUT_ERROR -= 2;
        if (delay_count >= 300)
        {
            delay_count = 300;
            Speed_Param.Speed_Setup = 0;
        }
    }
}

void Road_Mode_Ctrl(void)
{
    switch(Total_Image.road_type)
    {
        case start:
            Exist_Garage();
            break;
        case stop:
            Enter_Graage();
            break;
    }
}
void Whole_Ctrl(void)
{
    Road_Mode_Ctrl();
    Straight_Line_MODE(Total_Image.OUTPUT_ERROR);
    Smooth_Change_Speed(Speed_Param.Speed_Setup);
    Smooth_Change_Servo(Servo_Param.Head_Angle_Setup);
}
