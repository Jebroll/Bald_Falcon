#ifndef __CLARKE_H
#define __CLARKE_H

#include "adc.h"
#include "private_common.h"

typedef struct
{
    double Alpha;                   // 输出，静止坐标系Alpha轴定子电流
    double Beta;                    // 输出，静止坐标系Beta轴定子电流

}CLARK_Typedef;
CLARK_Typedef Clark_Calc(ADC_Typedef adc);

#endif /*__CLARKE_H*/
