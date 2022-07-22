#ifndef _WHOLE_CONTROL_H
#define _WHOLE_CONTROL_H

#include "servo.h"
#include "motor.h"
#include "SEEKFREE_18TFT.h"
#include "gpio.h"
#include "banlance_algorthm.h"

extern uint8 start_stop_flag;

void Smooth_Change_Servo(float angle);
void Smooth_Change_Speed(float speed);
void Straight_Line_MODE(float error);
void Exist_Garage(void);
void Enter_Graage(void);
void Whole_Ctrl(void);

#endif /*_WHOLE_CONTROL_H*/
