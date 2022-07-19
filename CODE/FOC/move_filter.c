/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：联系淘宝客服
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file            move_filter
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ3184284598)
 * @version         查看doc内version文件 版本说明
 * @Software        ADS v1.5.2
 * @Target core     TC264D
 * @Taobao          https://seekfree.taobao.com/
 * @date            2021-12-10
 ********************************************************************************************************************/

#include "move_filter.h"

move_filter_struct speed_filter;
move_filter_double_struct current_a_filter;
move_filter_double_struct current_b_filter;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      滑动平均滤波计算
//  @param      void
//  @return     void
//  @since      主要用于对数据滤波，存储目标数据最近的n个数据，并求出平均值
//-------------------------------------------------------------------------------------------------------------------
void move_filter_calc(move_filter_struct *move_filter, int32 new_data)
{
    //加上新的数值 减去最末尾的数值 求得最新的和
    move_filter->data_sum = move_filter->data_sum + new_data - move_filter->data_buffer[move_filter->index];
    //重新求平均值
    move_filter->data_average = move_filter->data_sum / move_filter->buffer_size;

    //将数据写入缓冲区
    move_filter->data_buffer[move_filter->index] = new_data;
    move_filter->index++;
    if(move_filter->buffer_size <= move_filter->index)
    {
        move_filter->index = 0;
    }
}

void move_filter_double_calc(move_filter_double_struct *move_filter, double new_data)
{
    //加上新的数值 减去最末尾的数值 求得最新的和
    move_filter->data_sum = move_filter->data_sum + new_data - move_filter->data_buffer[move_filter->index];
    //重新求平均值
    move_filter->data_average = move_filter->data_sum / move_filter->buffer_size;

    //将数据写入缓冲区
    move_filter->data_buffer[move_filter->index] = new_data;
    move_filter->index++;
    if(move_filter->buffer_size <= move_filter->index)
    {
        move_filter->index = 0;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      滑动平均滤波初始化
//  @param      void
//  @return     void
//  @since      主要用于对数据滤波，存储目标数据最近的n个数据，并求出平均值
//-------------------------------------------------------------------------------------------------------------------
void move_filter_init(move_filter_struct *move_filter)
{
    move_filter->data_average = 0;
    move_filter->data_sum = 0;
    move_filter->index = 0;
    //设置缓冲区大小
    move_filter->buffer_size = MOVE_AVERAGE_SIZE;

    uint8 i;
    for(i=0; i < move_filter->buffer_size; i++)
    {
        move_filter->data_buffer[i] = 0;
    }
}

void move_filter_double_init(move_filter_double_struct *move_filter)
{
    move_filter->data_average = 0;
    move_filter->data_sum = 0;
    move_filter->index = 0;
    //设置缓冲区大小
    move_filter->buffer_size = MOVE_AVERAGE_SIZE;

    uint8 i;
    for(i=0; i < move_filter->buffer_size; i++)
    {
        move_filter->data_buffer[i] = 0;
    }
}






