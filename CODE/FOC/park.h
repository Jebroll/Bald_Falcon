#ifndef __PARK_H
#define __PARK_H

#include "clark.h"
#include "fast_sin_cos_f32.h"

typedef struct
{
    double d;
    double q;
} PARK_Typedef;

PARK_Typedef Park_Calc(CLARK_Typedef clark, double theta);
CLARK_Typedef Anti_Park_Calc(PARK_Typedef park, double theta);

#endif /*__PARK_H*/
