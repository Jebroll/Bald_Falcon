#ifndef _PRIVATE_COMMON_H
#define _PRIVATE_COMMON_H
#include "PLATFORM_TYPES.H"

typedef struct
{
        uint8 last;
        uint8 now;
        uint8 next;
        uint8 test;
}Uint8_Status_Typedef;

typedef struct{
        float kp;
        float ki;
        float kd;
}PID_TypeDef;

#define sqrt3       (double)1.732050807568877
#define pi          (double)3.141592653589793
#define pi_2        (double)6.283185307179586

#define degrees_0   (double)0
#define degrees_15  (double)0.261799387799149
#define degrees_30  (double)0.523598775598299
#define degrees_45  (double)0.785398163397448
#define degrees_60  (double)1.047197551196598
#define degrees_75  (double)1.308996938995747
#define degrees_90  (double)1.570796326794896
#define degrees_105 (double)1.832595714594046
#define degrees_120 (double)2.094395102393195
#define degrees_135 (double)2.356194490192345
#define degrees_150 (double)2.617993877991495
#define degrees_165 (double)2.879793265790643
#define degrees_180 (double)pi
#define degrees_195 (double)3.403392041388943
#define degrees_210 (double)3.665191429188092
#define degrees_225 (double)3.926990816987241
#define degrees_240 (double)4.188790204786391
#define degrees_255 (double)4.450589592585540
#define degrees_270 (double)4.712388980384690
#define degrees_285 (double)4.974188368183839
#define degrees_300 (double)5.235987755982989
#define degrees_315 (double)5.4977871437821382
#define degrees_330 (double)5.7595865315812876
#define degrees_345 (double)6.0213859193804370
#define degrees_360 (double)pi_2

#endif  /*_PRIVATE_COMMON_H*/
