#ifndef _ENCODER_H
#define _ENCODER_H

#include "headfile.h"


#define Motor_TIM     GPT12_T6
#define Motor_LSB     GPT12_T6INA_P20_3//GPT12_T5INB_P10_3//记数20.3
#define Motor_Dir     GPT12_T6EUDA_P20_0//GPT12_T5EUDB_P10_1//方向20.0


void Motor_Encoder_Init(void);
float Motor_Speed(void);


#endif /*_ENCODER_H*/


