#include "motor.h"

void Motor_Stop(void)
{
    pwm_duty(Motor_CHA, 0);
    pwm_duty(Motor_CHB, 0);
}


void Motor_Control(int duty)
{
    if (duty > +Motor_Max_Speed) duty = +Motor_Max_Speed;
    if (duty < -Motor_Max_Speed) duty = -Motor_Max_Speed;

    if (duty > 0)
    {
        pwm_duty(Motor_CHA, +duty);
        pwm_duty(Motor_CHB, 0);
    }
    else
    {
        pwm_duty(Motor_CHA, 0);
        pwm_duty(Motor_CHB, -duty);
    }
}

/*******************驱动轮闭环控制********************/
Speed_Param_TypeDef Speed_Param;

void Motor_Param_Init(void)
{
    Speed_Param.PID.kp = -35;
    Speed_Param.PID.ki = -21;
    Speed_Param.PID.kd = -75;

    Speed_Param.Speed = 0;             //驱动轮编码器速度
    Speed_Param.Speed_Input = 0;
    Speed_Param.Speed_Setup = 70;      //驱动轮设定速度
    Speed_Param.Normal_Speed = Speed_Param.Speed_Setup;
}

void Speed_Control(float target_speed)
{
    float Speed_PWM, error;
    static float error_sum = 0, last_error = 0;

    if(target_speed > +700) target_speed = +700;
    if(target_speed < -700) target_speed = -700;

    Speed_Param.Speed = -Motor_Speed();

    error = (Speed_Param.Speed - target_speed);
    error_sum += error;

    if(error_sum>+150) error_sum=+150;                                          //积分限幅
    if(error_sum<-150) error_sum=-150;                                          //积分限幅

    Speed_PWM = Speed_Param.PID.kp * error +
                Speed_Param.PID.ki * error_sum +
                Speed_Param.PID.kd * (error - last_error);

    last_error = error;
    Motor_Control((int)Speed_PWM);
//    printf("%.0f, %d, %.0f\r\n",Speed_Param.Speed, (int)target_speed, Speed_PWM);//调试用
//    Motor_Control((int)target_speed);
}

void MOTOR_TEST_PRINTF(void)
{

}

/*******************驱动轮闭环控制********************/
void Motor_Init(void)
{
    Motor_Param_Init();
    Motor_Encoder_Init();

    gtm_pwm_init(Motor_CHA, Motor_PWM_Freq, 0);
    gtm_pwm_init(Motor_CHB, Motor_PWM_Freq, 0);
}
