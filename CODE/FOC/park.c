#include "park.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      帕克变换
//  @param      clark:克拉克结构体
//  @param      theta:角度
//  @return     帕克变换计算结果
//  @since
//-------------------------------------------------------------------------------------------------------------------
PARK_Typedef Park_Calc(CLARK_Typedef clark, double theta)
{
    PARK_Typedef park;

    park.d = clark.Alpha * fast_cos_f32(theta) + clark.Beta * fast_sin_f32(theta);
    park.q = clark.Beta * fast_cos_f32(theta) - clark.Alpha * fast_sin_f32(theta);

    return park;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      帕克逆变换
//  @param      park:帕克结构体
//  @param      theta:角度
//  @return     帕克逆变换计算结果
//  @since
//-------------------------------------------------------------------------------------------------------------------
CLARK_Typedef Anti_Park_Calc(PARK_Typedef park, double theta)
{
    CLARK_Typedef clark;

    clark.Alpha = park.d * fast_cos_f32(theta) - park.q * fast_sin_f32(theta);
    clark.Beta  = park.d * fast_sin_f32(theta) + park.q * fast_cos_f32(theta);

    return clark;
}

