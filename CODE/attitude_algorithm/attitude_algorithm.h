#ifndef _ATTITUDE_ALGORITHM_H
#define _ATTITUDE_ALGORITHM_H

#include "zf_stm_systick.h"
#include <math.h>
#include "SEEKFREE_ICM20602.h"


typedef struct{
    float q0;
    float q1;
    float q2;
    float q3;
}quaterInfo_t;


typedef struct{
    float pitch;
    float roll;
    float yaw;
}eulerianAngles_t;

typedef struct {
    float Xdata;
    float Ydata;
    float Zdata;
} gyro_param_t;


extern float values[10];
extern eulerianAngles_t eulerAngle;


void IMU_getValues(float * values);
void IMU_quaterToEulerianAngles(void);
void Attitude_Algorithm(void);
void gyroOffset_init(void);
void Attitude_Algorithm_Init(void);
#endif /*_ATTITUDE_ALGORITHM_H*/
