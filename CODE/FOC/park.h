#ifndef __PARK_H
#define __PARK_H

#include "clark.h"
#include "fast_sin_cos_f32.h"

typedef struct
{
    double d;              // 输出，旋转坐标系下的D坐标值电流
    double q;              // 输出，旋转坐标系下的Q坐标值电流
} PARK_Typedef;

PARK_Typedef Park_Calc(CLARK_Typedef clark, double theta);
CLARK_Typedef Anti_Park_Calc(PARK_Typedef park, double theta);

#endif /*__PARK_H*/
