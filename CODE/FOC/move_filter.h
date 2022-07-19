#ifndef _MOVE_FILTER_H
#define _MOVE_FILTER_H

#include "common.h"

#define MOVE_AVERAGE_SIZE   32  //定义缓冲区大小


typedef struct
{
    uint8 index;            //下标
    uint8 buffer_size;      //buffer大小
    int32 data_buffer[MOVE_AVERAGE_SIZE];  //缓冲区
    int32 data_sum;         //数据和
    int32 data_average;     //数据平均值
}move_filter_struct;

extern move_filter_struct speed_filter;

void move_filter_init(move_filter_struct *move_average);
void move_filter_calc(move_filter_struct *move_average, int32 new_data);


typedef struct
{
    uint8 index;            //下标
    uint8 buffer_size;      //buffer大小
    double data_buffer[MOVE_AVERAGE_SIZE];  //缓冲区
    double data_sum;         //数据和
    double data_average;     //数据平均值
}move_filter_double_struct;

extern move_filter_double_struct current_a_filter;
extern move_filter_double_struct current_b_filter;

void move_filter_double_init(move_filter_double_struct *move_average);
void move_filter_double_calc(move_filter_double_struct *move_average, double new_data);



#endif /* CODE_MOVE_FILTER_H_ */
