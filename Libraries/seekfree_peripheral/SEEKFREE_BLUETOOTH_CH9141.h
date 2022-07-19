/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		逐飞科技蓝牙转串口模块
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.33
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2021-08-27
 * @note		
					接线定义：
					------------------------------------ 
					    蓝牙转串口      单片机                        
    					RX              查看SEEKFREE_BLUETOOTH_CH9141.h文件中的BLUETOOTH_CH9141_UART_TX宏定义
    					TX              查看SEEKFREE_BLUETOOTH_CH9141.h文件中的BLUETOOTH_CH9141_UART_RX宏定义
    					RTS             查看SEEKFREE_BLUETOOTH_CH9141.h文件中的BLUETOOTH_CH9141_RTS_PIN宏定义
                        CTS             悬空
    					CMD             悬空或者上拉
					------------------------------------ 
 ********************************************************************************************************************/
 
#ifndef SEEKFREE_BLUETOOTH_CH9141_H
#define SEEKFREE_BLUETOOTH_CH9141_H

#include "common.h"

typedef struct
{
    uint8     *buffer;                                                          // 缓存指针
    uint32    head;                                                             // 缓存头指针 总是指向空的缓存
    uint32    end;                                                              // 缓存尾指针 总是指向非空缓存（缓存全空除外）
    uint32    size;                                                             // 缓存剩余大小
    uint32    max;                                                              // 缓存总大小
}fifo_struct;

typedef enum
{
    FIFO_SUCCESS,

    FIFO_BUFFER_NULL,
    FIFO_SPACE_NO_ENOUGH,
    FIFO_DATA_NO_ENOUGH,
}fifo_state_enum;

typedef enum
{
    FIFO_READ_AND_CLEAN,
    FIFO_READ_ONLY,
}fifo_operation_enum;

fifo_state_enum fifo_init           (fifo_struct *fifo, uint8 *buffer_addr, uint32 size);
void            fifo_head_offset    (fifo_struct *fifo, uint32 offset);
void            fifo_end_offset     (fifo_struct *fifo, uint32 offset);
void            fifo_clear          (fifo_struct *fifo);
uint32          fifo_used           (fifo_struct *fifo);

fifo_state_enum fifo_read_buffer    (fifo_struct *fifo, uint8 *dat, uint32 *length, fifo_operation_enum flag);
fifo_state_enum fifo_write_buffer   (fifo_struct *fifo, uint8 *dat, uint32 length);



#define BLUETOOTH_CH9141_INDEX              UART_2                              // 蓝牙模块 1 对应使用的串口号
#define BLUETOOTH_CH9141_BUAD_RATE          115200                              // 蓝牙模块 1 对应使用的串口波特率
#define BLUETOOTH_CH9141_TX_PIN             UART2_RX_P10_6                         // 蓝牙模块 1 对应模块的 TX 要接到单片机的 RX
#define BLUETOOTH_CH9141_RX_PIN             UART2_TX_P10_5                        // 蓝牙模块 1 对应模块的 RX 要接到单片机的 TX
#define BLUETOOTH_CH9141_RTS_PIN            P10_2                                 // 蓝牙模块 1 对应模块的 RTS 引脚

#define BLUETOOTH_CH9141_BUFFER_SIZE        64
#define BLUETOOTH_CH9141_TIMEOUT_COUNT      500



void        bluetooth_ch9141_uart_callback      (void);

uint8       bluetooth_ch9141_init               (void);

uint32      bluetooth_ch9141_send_buff          (uint8 *buff, uint32 len);
uint32      bluetooth_ch9141_read_buff          (uint8 *buff, uint32 len);









#endif
