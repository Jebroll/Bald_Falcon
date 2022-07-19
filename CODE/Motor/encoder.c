#include "encoder.h"

void Motor_Encoder_Init(void)
{
    gpt12_init(Motor_TIM, Motor_LSB, Motor_Dir);
}



float Motor_Speed(void)
{
    float speed;

    speed = (float)gpt12_get(Motor_TIM);
    gpt12_clear(Motor_TIM);
    return speed;
    //打印采集到的编码器数据，可以先学习printf例程，了解如何使用printf
}
