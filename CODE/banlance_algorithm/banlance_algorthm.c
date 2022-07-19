#include "banlance_algorthm.h"

/*******************动量轮相关变量及参数********************/
Balance_Param_TypeDef Balance_Param;

void Balance_Param_Init(void)
{
    Balance_Param.Angle_PID.kp = 0.95;//0.8
    Balance_Param.Angle_PID.ki = 0.009;//0.02
    Balance_Param.Angle_PID.kd = 0.0055;//0.007

    Balance_Param.Velocity_PID.kp = -0.0018;//-0.2
    Balance_Param.Velocity_PID.ki = -0.0009;//-0.07
    Balance_Param.Velocity_PID.kd = 0;

    Balance_Param.Balance_Angle.left = -1.31;
    Balance_Param.Balance_Angle.mid = 0.5 ;
    Balance_Param.Balance_Angle.right = 2.6;

    Balance_Param.Speed_Correction.left = 0.013;
    Balance_Param.Speed_Correction.right = 0.013;
}
uint8 Momentum_Motor_Flag = 1;  //动量轮启停标志
float Dynamic_Balance_Angle;     //动态平衡角度
float Vetical_PWM = 0, Velocity_PWM = 0;//动量轮PWM中间量
float Momentum_Motor_Duty = 0;  //动量轮PWM最终量

float Momentum_Speed;
/*******************动量轮相关变量及参数********************/



/**********************动量轮控制函数***********************/
float Middle_Angle_Counting(float head_angle, float bicycle_speed)
{
    float La, Lb, Ra, Rb;           //左右平衡角度线性函数系数
    La = (Balance_Param.Balance_Angle.left - Balance_Param.Balance_Angle.mid)/(Max_Angle - Mid_Angle);
    Lb = (Balance_Param.Balance_Angle.left - Max_Angle * La);

    Ra = (Balance_Param.Balance_Angle.right - Balance_Param.Balance_Angle.mid)/(Min_Angle - Mid_Angle);
    Rb = (Balance_Param.Balance_Angle.right - Min_Angle * Ra);

    float Middle_Angle_Output;
    uint8 angle_flag = 1, speed_flag = 1;
    if (bicycle_speed <= 10)     speed_flag = 0;
    if (head_angle >= Mid_Angle) angle_flag = 0;//是否向左

    switch(speed_flag*10 + angle_flag)
    {
        case 00:
            Middle_Angle_Output = La*head_angle + Lb;
            break;
        case 01:
            Middle_Angle_Output = Ra*head_angle + Rb;
            break;
        case 10:
//            Middle_Angle_Output = -(La*head_angle + Lb);
//            Middle_Angle_Output *= bicycle_speed*Balance_Param.Speed_Correction.left;
            Middle_Angle_Output = La*head_angle + Lb;
            Middle_Angle_Output += bicycle_speed*Balance_Param.Speed_Correction.left;
            break;
        case 11:
//            Middle_Angle_Output = -(Ra*head_angle + Rb);
//            Middle_Angle_Output = bicycle_speed*Balance_Param.Speed_Correction.right;
            Middle_Angle_Output = Ra*head_angle + Rb;
            Middle_Angle_Output -= bicycle_speed*Balance_Param.Speed_Correction.right;
            break;
    }
    return Middle_Angle_Output;
}
////-------------------------------------------------------------------------------------------------------------------
////  @brief      角度环
////  @param      target_angle:目标角度
////  @param      current:当前角度
////  @param      gyro_x:角加速度
////  @return     void
////  @since
////-------------------------------------------------------------------------------------------------------------------
float Vertical(float target_angle, float current_angle, float gyro_x)
{
    float Vetical_PWM;
    static float error;

    error += current_angle - target_angle;

    if(error>+30) error=+30;                                          //积分限幅
    if(error<-30) error=-30;                                          //积分限幅

    Vetical_PWM = Balance_Param.Angle_PID.kp * (current_angle - target_angle) +
                  Balance_Param.Angle_PID.ki * error +
                  Balance_Param.Angle_PID.kd * (gyro_x);

    return Vetical_PWM;
}
////-------------------------------------------------------------------------------------------------------------------
////  @brief      速度环
////  @param      encoder:转子速度
////  @return
////  @since
////-------------------------------------------------------------------------------------------------------------------
float Velocity(float encoder)
{
    static float Encoder, Encoder_Integral;
    float Velocity_PWM, Encoder_Least;

    Encoder_Least = encoder;                                                  //速度滤波
    Encoder *= 0.7;                                                           //一阶低通滤波器
    Encoder += Encoder_Least*0.3;                                             //一阶低通滤波器
    Encoder_Integral += Encoder;                                              //积分出位移

    if(Encoder_Integral > +200) Encoder_Integral = +200;                    //积分限幅
    if(Encoder_Integral < -200) Encoder_Integral = -200;                    //积分限幅

    Velocity_PWM = Balance_Param.Velocity_PID.kp * Encoder +
                   Balance_Param.Velocity_PID.ki/100 * Encoder_Integral;//获取最终数值

    if(Momentum_Motor_Flag == 0) Encoder_Integral=0, Encoder=0, Velocity_PWM=0;                //停止时参数清零

    return Velocity_PWM;
}

////-------------------------------------------------------------------------------------------------------------------
////  @brief      平衡总控制
////  @param      void
////  @return     void
////  @since      执行周期:5ms
////-------------------------------------------------------------------------------------------------------------------
void Balance_Control(void)
{
    Momentum_Speed = (float)FOC.BLmotor.speed;
    Dynamic_Balance_Angle = Middle_Angle_Counting(Servo_Param.Head_Angle, Speed_Param.Speed);

    Vetical_PWM  = Vertical(Dynamic_Balance_Angle, eulerAngle.roll, icm_gyro_x);
    Velocity_PWM = Velocity(Momentum_Speed);

    Momentum_Motor_Duty = (Vetical_PWM - Velocity_PWM);

    if(eulerAngle.roll > Dynamic_Balance_Angle + 12 || eulerAngle.roll < Dynamic_Balance_Angle - 12)//摔倒判断，保护电机、电池
    {
        Momentum_Motor_Flag = 0;
    }else
    {
        Momentum_Motor_Flag = 1;
    }
    if(Momentum_Motor_Flag == 0)                       // 停车
    {
        Momentum_Motor_Duty = 0;                      // 电机关闭
//        Integration = 0;                     // 积分参数归零
    }

    Momemtum_Motor_Control(Momentum_Motor_Duty);
}
////-------------------------------------------------------------------------------------------------------------------
////  @brief      平衡相关数据打印
////  @param      void
////  @return     void
////  @since      调试时放在main.c使用
////-------------------------------------------------------------------------------------------------------------------
void BANLANCE_TEST_PRINTF(void)
{
//    printf("%d\r\n", hall_value_now);
//    printf("%.2f, %.2f\r\n", Head_Angle, Dynamic_Middle_Angle);//调试用
    printf("%.2f,%f,%f,%f\r\n",eulerAngle.roll, Dynamic_Balance_Angle, Momentum_Speed, Momentum_Motor_Duty);//调试用
}


void Banlance_Algorithm_Init(void)
{
    Balance_Param_Init();
}
