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
    Servo_Param.Head_Angle_Input -= 0.048*error;
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
    Total_Image.OUTPUT_ERROR = -14;
    systick_delay_ms(STM0, 500);
    systick_delay_ms(STM0, 500);
    systick_delay_ms(STM0, 200);
    Led_Ctrl(4, ON);
    start_stop_flag = 0;//摄像头开启
    Total_Image.road_type = road_normal;
}

void Enter_Graage(void)
{
    Buzzer_Ctrl(ON);
    start_stop_flag = 1;//摄像头关闭

    Speed_Param.Speed_Setup = 60;

    for(uint16 i = 30; i > 0; i--)
    {
        systick_delay_ms(STM0,40);
        Speed_Param.Speed_Setup -= 1;
        Total_Image.OUTPUT_ERROR --;
    }
    systick_delay_ms(STM0,500);
    Configuration_complete_flag = 0;
    Motor_Stop();
    Buzzer_Ctrl(OFF);
    while(1)
    {
        Momentum_Motor_Flag = 0;
        Mos_All_Low_Open();
    }
//    delay_count++;
//    if (delay_count % 14 == 0)
//    {
//        Speed_Param.Speed_Setup -= 12;
//        Total_Image.OUTPUT_ERROR -= 3;
//        if (delay_count >= 300)
//        {
//            Speed_Param.Speed_Setup = 0;
//            Configuration_complete_flag = 0;
//            Motor_Stop();
//            while(1);
//        }
//    }
}

void Road_Mode_Ctrl(void)
{
    if (Total_Image.podao_status == 1)
    {
        Speed_Param.Speed_Setup = 65;
    }
    else
    {
        switch(Total_Image.crossing_road_status)
        {
            case second_crossing_exit:
                Speed_Param.Speed_Setup = 63;
                Speed_Param.Normal_Speed = Speed_Param.Speed_Setup;
                break;
            default:
                break;
        }
        switch(Total_Image.round_road_status)
        {
            case round_road_finishs:
                Speed_Param.Speed_Setup = 70;
                Speed_Param.Normal_Speed = Speed_Param.Speed_Setup;
                break;
            default:
                break;
        }
        switch(Total_Image.three_way_status)
        {
            case enter_right_three_way:
                Speed_Param.Speed_Setup = 58;
                Speed_Param.Normal_Speed = Speed_Param.Speed_Setup;
                break;
            case exit_right_three_way:
                Speed_Param.Speed_Setup = 65;
                Speed_Param.Normal_Speed = Speed_Param.Speed_Setup;
                break;
        }
    }
}
void Whole_Ctrl(void)
{
    Road_Mode_Ctrl();
    Straight_Line_MODE(Total_Image.OUTPUT_ERROR);
    Smooth_Change_Speed(Speed_Param.Speed_Setup);
    Smooth_Change_Servo(Servo_Param.Head_Angle_Setup);
}
