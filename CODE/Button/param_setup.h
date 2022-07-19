#ifndef _PARAM_SETUP_H
#define _PARAM_SETUP_H

#include "gpio.h"
#include "stdio.h"
#include "button.h"
#include "servo.h"
#include "motor.h"
#include "brushless_motor.h"
#include "banlance_algorthm.h"
#include "SEEKFREE_18TFT.h"

void Bicycle_Configuration(void);
extern uint8 Configuration_complete_flag;

#endif /*_PARAM_SETUP_H*/
