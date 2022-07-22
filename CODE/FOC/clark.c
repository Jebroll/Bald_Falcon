#include "clark.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief      克拉克变换
//  @param      void
//  @return     void
//  @since      none
//-------------------------------------------------------------------------------------------------------------------
CLARK_Typedef Clark_Calc(ADC_Typedef adc)
{
    CLARK_Typedef clark;

    clark.Alpha = 1.5 * adc.current_a;
    clark.Beta  = sqrt3 / 2.0 * adc.current_a + sqrt3 * adc.current_b;

    return clark;
}
