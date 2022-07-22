#include "brushless_motor.h"

FOC_Parm_Typedef FOC;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      开启所有上桥     关闭所有下桥
//  @param      periodAH:       A上桥PWM占空比
//  @param      periodBH:       B上桥PWM占空比
//  @param      periodCH:       C上桥PWM占空比
//  @return     void
//  @since      采用中心对齐模式，装载值越大，高电平时间越短
//-------------------------------------------------------------------------------------------------------------------
void Mos_All_High_Open(uint16 periodAH, uint16 periodBH, uint16 periodCH)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x3F;//0011 1111                   //用户手册27.8章节自己看

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, periodAH);         //设置比较值
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, periodBH);         //设置比较值
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, periodCH);         //设置比较值
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);                          //使能
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      关闭所有上桥，开启所有下桥，使电机在线圈的自感电动势的作用下自己完成刹车
//  @param      void
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void Mos_All_Low_Open(void)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x2A;//0010 1010                   //用户手册27.8章节自己看

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, 0);   
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, 0);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);                         //使能
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      中间变量计算
//  @param      clark: Alpha & Beta
//  @return     中间变量计算结果
//  @since      x,y,z为中间变量，无实际意义
//-------------------------------------------------------------------------------------------------------------------
Instrument_Typedef Tool_Calc(CLARK_Typedef clark)
{
    Instrument_Typedef tool;

    tool.x =  clark.Beta;
    tool.y =  clark.Alpha * sqrt3 / 2.0 - clark.Beta / 2.0;
    tool.z = -clark.Alpha * sqrt3 / 2.0 - clark.Beta / 2.0;

    return tool;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      电角度扇区判断
//  @param      temp:用于辅助计算的中间变量
//  @return     N = （1~6）
//              3 1 5 4 6 2 3（N值）
//              1 2 3 4 5 6 1（扇区）
//  @since      x,y,z为中间变量，无实际意义
//-------------------------------------------------------------------------------------------------------------------
uint8 Electrical_Sector_Judge(Instrument_Typedef tool)
{
    uint8 N = 0;

    if(tool.x > 0) N = N + 1;
    if(tool.y > 0) N = N + 2;
    if(tool.z > 0) N = N + 4;

    return N;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      每个扇区两基矢量作用时间计算
//  @param      tool:用于辅助计算的中间变量
//  @param      N:判断扇区的N值
//  @param      Udc:母线电压
//  @param      T:PWM周期（装载值）
//  @return     各扇区时间计算结果
//  @since      根据扇区分别计算在各扇区中两基矢量的作用时间
//-------------------------------------------------------------------------------------------------------------------
VectorTime_Typedef Vector_Calc(Instrument_Typedef tool, uint8 N, uint8 Udc, uint16 T)
{
    VectorTime_Typedef vector;

    double temp = sqrt3 * T / Udc;//为了等幅值变换，已乘以2/3

    switch (N)
    {
        case 3://扇区1
            vector.ta =  temp * tool.y;
            vector.tb =  temp * tool.x;
            break;
        case 1://扇区2
            vector.ta = -temp * tool.y;
            vector.tb = -temp * tool.z;
            break;
        case 5://扇区3
            vector.ta =  temp * tool.x;
            vector.tb =  temp * tool.z;
            break;
        case 4://扇区4
            vector.ta = -temp * tool.x;
            vector.tb = -temp * tool.y;
            break;
        case 6://扇区5
            vector.ta =  temp * tool.z;
            vector.tb =  temp * tool.y;
            break;
        case 2://扇区6
            vector.ta = -temp * tool.z;
            vector.tb = -temp * tool.x;
            break;
        default:
            vector.ta = 0;
            vector.tb = 0;
            break;
    }

    return vector;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      每个半桥中上桥PWM占空比计算
//  @param      vector:各扇区时间计算结果
//  @param      N:判断扇区的N值
//  @param      T:PWM周期（装载值）
//  @return     各半桥中上桥的PWM占空比
//  @since      其中value1, value2, value3是根据七段式SVPWM调制法在六个扇区中的分布规律得出
//-------------------------------------------------------------------------------------------------------------------
Period_Typedef PeriodCal(VectorTime_Typedef vector, uint8 N, uint16 T)
{
    Period_Typedef period;
    uint16 value1, value2, value3;
    double Ttemp = vector.ta + vector.tb;

    if(Ttemp > T)
    {
        vector.ta = vector.ta / Ttemp * (double)T;
        vector.tb = vector.tb / Ttemp * (double)T;
    }
    value1 = (uint16)(((double)T - vector.ta - vector.tb) / 4.0);
    value2 = (uint16)(value1 + vector.ta / 2.0);
    value3 = (uint16)(value2 + vector.tb / 2.0);
    switch (N)
    {
        case 3:
            period.AH = value1;
            period.BH = value2;
            period.CH = value3;
            break;
        case 1:
            period.AH = value2;
            period.BH = value1;
            period.CH = value3;
            break;
        case 5:
            period.AH = value3;
            period.BH = value1;
            period.CH = value2;
            break;
        case 4:
            period.AH = value3;
            period.BH = value2;
            period.CH = value1;
            break;
        case 6:
            period.AH = value2;
            period.BH = value3;
            period.CH = value1;
            break;
        case 2:
            period.AH = value1;
            period.BH = value3;
            period.CH = value2;
            break;
        default:
            period.AH = 0;
            period.BH = 0;
            period.CH = 0;
            break;
    }

    return period;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      计算电角度
//  @param      hall:霍尔传感器相关数据
//  @param      speed:转子速度（RPM）
//  @param      dir:转子设定旋转方向
//  @return     电角度
//  @since      由于没有使用编码器，使用的是霍尔传感器，精度不够，所以靠转子速度硬算电角度（不准确）
//-------------------------------------------------------------------------------------------------------------------
double Theta_Calc (HALL_Typedef hall, int32 speed, MOTOR_DIR_enum dir)
{
    static double theta = 0 ;

    if(speed < 0)  speed = -speed;

    if (dir)//反传
    {
        if (hall.value.now != hall.value.last)//如果转子进入了下一个扇区
        {
            switch (hall.value.now)
            {
                case 1: theta  = degrees_180;   break;
                case 2: theta  = degrees_240;   break;
                case 3: theta  = degrees_300;   break;
                case 4: theta  = degrees_0;     break;
                case 5: theta  = degrees_60;    break;
                case 6: theta  = degrees_120;   break;
                default:                        break;
            }
        }
        else
        {                                                   //角度计算说明：
            theta -= speed * pi /600000.0;                  //由于 转子速度是            x(rpm/min)
            if (theta <= 0)     theta = pi_2;               //换算之后为 1/600000 * pi * x(rad/50us)
        }                                                   //控制周期为50us,即20kHz
    }
    else//正转
    {
        if (hall.value.now != hall.value.last)//如果转子进入了下一个扇区
        {
            switch (hall.value.now)
            {
                case 1: theta  = degrees_0;     break;
                case 2: theta  = degrees_60;    break;
                case 3: theta  = degrees_120;   break;
                case 4: theta  = degrees_180;   break;
                case 5: theta  = degrees_240;   break;
                case 6: theta  = degrees_300;   break;
                default:                        break;
            }
        }
        else
        {
            theta += speed * pi /600000.0;                  //同上
            if (theta >= pi_2)  theta = 0;
        }
    }

    return theta;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      正反转状态灯控制
//  @param      dir:正反转枚举
//  @return     none
//  @since      none
//-------------------------------------------------------------------------------------------------------------------
void FOC_Status_Display(MOTOR_DIR_enum dir)
{
    switch (dir)
    {
        case FORWARD:
            Led_Ctrl(2, ON);
            Led_Ctrl(1, OFF);
            break;
        case REVERSE:
            Led_Ctrl(1, ON);
            Led_Ctrl(2, OFF);
            break;
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      判断转子当前旋转方向
//  @param      hall:霍尔传感器相关数据
//  @return     转子当前旋转方向
//  @since      none
//-------------------------------------------------------------------------------------------------------------------
MOTOR_DIR_enum actual_dir_judgement(HALL_Typedef hall)//ps:由于霍尔传感器采用问题，转子速度太高时可以会出现判断失误
{
    MOTOR_DIR_enum actual_dir;

    switch (hall.value_save[1] - hall.value_save[0])//转子的本次扇区状态减去上次扇区状态
    {
        //正传
        case  4: actual_dir = FORWARD; break;
        case  3: actual_dir = FORWARD; break;
        case  2: actual_dir = FORWARD; break;
        case  1: actual_dir = FORWARD; break;
        case -5: actual_dir = FORWARD; break;
        //反转
        case -4: actual_dir = REVERSE; break;
        case -3: actual_dir = REVERSE; break;
        case -2: actual_dir = REVERSE; break;
        case -1: actual_dir = REVERSE; break;
        case  5: actual_dir = REVERSE; break;
    }
    FOC_Status_Display(actual_dir);

    return actual_dir;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      转子旋转速度计算
//  @param      hall:霍尔传感器相关数据
//  @return     转子速度（RPM）
//  @since      none
//-------------------------------------------------------------------------------------------------------------------
int32 calc_speed(HALL_Typedef hall)
{
    //转速计算
    uint8 i;
    int32 speed;
    hall.commutation_time_sum = 0;
    for(i=0; i<6; i++)
    {
        hall.commutation_time_sum += hall.commutation_time_save[i];
    }

    //电机转速计算说明
    //2.commutation_time_sum是统计电机换相6次会进入多少次T12周期中断
        //2.1 T12周期中断周期中断的频率为FPWM  "ps:频率宏定义在ccu6_pwm.h"
        //2.2 函数调用关系ccu6_t12_pwm->Get_Hall_Value->calc_speed
        //2.3 commutation_time为统计换相时间的变量
    //3.通常电机转速我们都用RPM表示，RPM表示每分钟电机的转速
    //3.电机转一圈需要换相的次数等于 电机极对数*6    ps:极对数宏定义在#include "brushless_motor.h"
    //4.因此电机转速等于60*ADC中断频率/电机极对数/commutation_time_sum，这样可以得到电机每分钟的转速

    speed = PWM_PIT_NUM/POLEPAIRS/hall.commutation_time_sum;

    if(REVERSE == FOC.BLmotor.actual_dir)//电机反转的时候需要对速度取反
    {
        speed = -speed;
    }
    move_filter_calc(&speed_filter, speed); //速度滑动滤波

    speed = speed_filter.data_average;      //得到滑动滤波的结果

    return speed;
}
#if CURRENT_CLOSE_LOOP_ENABLE               //电流环开关
//-------------------------------------------------------------------------------------------------------------------
//  @brief      d、q轴PI控制器
//  @param      ref_park:d、q目标值
//  @param      I_park  :d、q实际值
//  @return     d、q输入值
//  @since
//-------------------------------------------------------------------------------------------------------------------
PARK_Typedef Current_Close_Loop(PARK_Typedef ref_park, PARK_Typedef I_park)
{
    PARK_Typedef park_in;
    double error_d, error_q;
    static double error_sum_d = 0, error_sum_q = 0;

    error_d = ref_park.d - I_park.d;
    error_q = ref_park.q - I_park.q;
    error_sum_d += error_d;
    error_sum_q += error_q;

    if (error_sum_d >  2) error_sum_d =  2;     //积分限幅
    if (error_sum_d < -2) error_sum_d = -2;     //积分限幅
    if (error_sum_q >  2) error_sum_d =  2;     //积分限幅
    if (error_sum_q < -2) error_sum_d = -2;     //积分限幅

    park_in.d = FOC.Current_CL.d.kp * error_d + FOC.Current_CL.d.ki * error_sum_d;
    park_in.q = FOC.Current_CL.q.kp * error_q + FOC.Current_CL.q.ki * error_sum_q;

    return park_in;
}
#endif
////-------------------------------------------------------------------------------------------------------------------
////  @brief      svpwm调制算法
////  @param      Udc:母线电压
////  @return     T:PWM最大装载值
////  @since
////-------------------------------------------------------------------------------------------------------------------
void SVPWM_Algorithm(uint8 Udc, uint16 T)
{
    FOC.hall               = Get_Hall_Value();
    FOC.BLmotor.actual_dir = actual_dir_judgement(FOC.hall);
    FOC.BLmotor.speed      = calc_speed(FOC.hall);
    if (abs(FOC.BLmotor.speed - FOC.BLmotor.last_speed) > 220)//用于去除毛刺
    {
        FOC.BLmotor.speed = FOC.BLmotor.last_speed;
    }
    else
    {
        FOC.BLmotor.last_speed = FOC.BLmotor.speed;
    }
    FOC.theta              = Theta_Calc (FOC.hall, FOC.BLmotor.speed, FOC.BLmotor.dir);

#if CURRENT_CLOSE_LOOP_ENABLE
    FOC.Adc     = Adc_Read();
    FOC.I_Clrak = Clark_Calc(FOC.Adc);
    FOC.I_Park  = Park_Calc(FOC.I_Clrak, FOC.theta);
    FOC.Park_In = Current_Close_Loop(FOC.Ref_Park, FOC.I_Park);

    FOC.V_Clark   = Anti_Park_Calc(FOC.Park_In, FOC.theta);//Id,Iq进行帕克逆变换
#else
    FOC.V_Clark   = Anti_Park_Calc(FOC.Ref_Park, FOC.theta);//Id,Iq进行帕克逆变换
#endif
    FOC.tool    = Tool_Calc(FOC.V_Clark);                   //中间变量计算
    FOC.N       = Electrical_Sector_Judge(FOC.tool);        //电角度扇区判断
    FOC.Vector  = Vector_Calc(FOC.tool, FOC.N, Udc, T);     //矢量作用时间计算
    FOC.Period  = PeriodCal(FOC.Vector, FOC.N, T);          //各桥PWM占空比计算

    Mos_All_High_Open(FOC.Period.AH, FOC.Period.BH, FOC.Period.CH);
}
////-------------------------------------------------------------------------------------------------------------------
////  @brief      无刷电机控制API
////  @param      duty:q值大小
////  @return     void
////  @since      调试时放在main.c使用
////-------------------------------------------------------------------------------------------------------------------
void Momemtum_Motor_Control(float duty)
{
    if (duty > 0)
    {
        if (duty >=  4) duty =  4;
        FOC.Ref_Park.q =  duty + Q_DEAD_PERIOD;
        FOC.BLmotor.dir = FORWARD;
    }
    else
    {
        if (duty <= -4) duty = -4;
        FOC.Ref_Park.q = -duty + Q_DEAD_PERIOD;
        FOC.BLmotor.dir = REVERSE;
    }
}
////-------------------------------------------------------------------------------------------------------------------
////  @brief      FOC相关数据打印
////  @param      void
////  @return     void
////  @since      调试时放在main.c使用，不使用时记得关闭
////-------------------------------------------------------------------------------------------------------------------
void FOC_TEST_PRINTF(void)
{
    printf("%f,%f,%f\r\n",FOC.Adc.current_a, FOC.Adc.current_b, FOC.Adc.current_c);
//    printf("%f,%f,%f,%f\r\n",FOC.Ref_Park.d, FOC.Ref_Park.q, FOC.I_Park.d, FOC.I_Park.q);
//    printf("%d\r\n",FOC.hall.value.now);
//    printf("%ld\r\n",FOC.BLmotor.speed);
//    printf("%f\r\n",FOC.theta);
}
////-------------------------------------------------------------------------------------------------------------------
////  @brief      FOC参数初始化
////  @param      void
////  @return     void
////  @since      none
////-------------------------------------------------------------------------------------------------------------------
void FOC_Param_Init(void)
{
    FOC.Ref_Park.d = 0;
    FOC.Ref_Park.q = 0;//1.0
    FOC.BLmotor.dir = FORWARD;

#if CURRENT_CLOSE_LOOP_ENABLE
    FOC.Current_CL.d.kp = 0.53;//0.53
    FOC.Current_CL.d.ki = 0.000037;//0.000037

    FOC.Current_CL.q.kp = 0.26;//0.26
    FOC.Current_CL.q.ki = 0.000037;//0.000037
#endif
}
////-------------------------------------------------------------------------------------------------------------------
////  @brief      FOC初始化
////  @param      void
////  @return     void
////  @since      none
////-------------------------------------------------------------------------------------------------------------------
void FOC_Init(void)
{
#if CURRENT_CLOSE_LOOP_ENABLE
    Adc_Collection_Init();          //adc电流采样初始化
#endif
    FOC_Param_Init();               //FOC参数初始化
    ccu6_pwm_init();                //CCU6 PWM模块初始化
    Hall_Init();                    //霍尔传感器初始化
    move_filter_init(&speed_filter);//滑动滤波初始化

}
