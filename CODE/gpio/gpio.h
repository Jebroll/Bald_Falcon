#ifndef _GPIO_H
#define _GPIO_H

#include "zf_gpio.h"
#include "common.h"

#define LED1 P10_3
#define LED2 P10_2
#define LED3 P10_1
#define LED4 P11_12
#define LED5 P21_5
#define LED6 P21_4

#define BUZZER P21_2

typedef enum
{
    OFF,  //¹Ø±Õ
    ON,   //Ê¹ÄÜ
}GPIO_STATUS_enum;


void Led_Ctrl(uint8 num, GPIO_STATUS_enum status);
void Buzzer_Ctrl(GPIO_STATUS_enum status);
void Gpio_Init(void);

#endif /*_GPIO_H*/
