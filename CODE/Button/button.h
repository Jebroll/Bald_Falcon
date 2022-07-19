#ifndef _BOTTON_H
#define _BOTTON_H

#include "stdio.h"
#include "common.h"
#include "zf_gpio.h"
#include "multi_button.h"

//定义按键引脚
#define KEY1    P22_0
#define KEY2    P22_1
#define KEY3    P22_2
#define KEY4    P22_3

typedef struct
{
    uint8 single_click;
    uint8 double_click;
    uint8 LONG_PRESS_START;
}Button_Flag_Typedef;
extern Button_Flag_Typedef key1_f, key2_f, key3_f, key4_f;

void Buttons_Init(void);


#endif /*_BOTTON_H*/



