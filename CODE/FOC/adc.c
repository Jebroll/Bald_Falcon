#include "adc.h"


#if FILTER_ENABLE
Ifx_LowPassPt1F32 current_filter;
void LowPassFilter_Init(void)//英飞凌一阶低通滤波器初始化
{
    Ifx_LowPassPt1F32_Config current_filter_config;

    current_filter_config.cutOffFrequency   = 700;          //截止频率
    current_filter_config.samplingTime      = 0.00005;      //采样时间
    current_filter_config.gain              = 1;            //增益

    Ifx_LowPassPt1F32_init(&current_filter, &current_filter_config);
}
#endif
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC采集并计算三相电流
//  @param      void
//  @return     三相电流值
//  @since      V = 1.884 + 0.15I  (-10A< I <10A)       需要根据实际情况计算
//-------------------------------------------------------------------------------------------------------------------
ADC_Typedef Adc_Read(void)
{
    ADC_Typedef adc;

    adc.current_a = (float)adc_convert(ADC_NUMBER, A_PHASE_PORT, ADC_12BIT);       //获取A相ADC原始数据
    adc.current_b = (float)adc_convert(ADC_NUMBER, B_PHASE_PORT, ADC_12BIT);       //获取A相ADC原始数据
//    adc.current_c = (double)adc_convert(ADC_NUMBER, C_PHASE_PORT, ADC_12BIT);       //获取A相ADC原始数据

#if FILTER_ENABLE
    #if 0//滑动滤波
        move_filter_double_calc(&current_a_filter, adc.current_a);
        move_filter_double_calc(&current_b_filter, adc.current_b);
        adc.current_a = current_a_filter.data_average;
        adc.current_b = current_b_filter.data_average;
    #else//低通滤波
        adc.current_a = Ifx_LowPassPt1F32_do(&current_filter, adc.current_a);
        adc.current_b = Ifx_LowPassPt1F32_do(&current_filter, adc.current_b);
    #endif
#endif

    adc.current_a = adc.current_a / 4095 * 22.0 - 12.56;                                     //计算A相电流
    adc.current_b = adc.current_b / 4095 * 22.0 - 12.56;                                     //计算B相电流
//    adc.current_c = adc.current_c / 4095 * 22.0 - 12.56;

    adc.current_c = 0 - adc.current_a - adc.current_b;                                      //计算C相电流

    return adc;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC采集引脚初始化
//  @param      void
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void Adc_Collection_Init(void)
{
    adc_init(ADC_NUMBER, A_PHASE_PORT);             //A相
    adc_init(ADC_NUMBER, B_PHASE_PORT);             //B相
//    adc_init(ADC_NUMBER, C_PHASE_PORT);             //C相
#if FILTER_ENABLE
    LowPassFilter_Init();
    move_filter_double_init(&current_a_filter);//滑动滤波初始化
    move_filter_double_init(&current_b_filter);//滑动滤波初始化
#endif
}


