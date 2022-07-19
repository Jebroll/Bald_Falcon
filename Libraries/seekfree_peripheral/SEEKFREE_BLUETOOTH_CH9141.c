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
#include "zf_stm_systick.h"
#include "zf_gpio.h"
#include "zf_uart.h"
#include "zf_assert.h"
#include "SEEKFREE_BLUETOOTH_CH9141.h"

static  fifo_struct     bluetooth_ch9141_fifo;
static  uint8           bluetooth_ch9141_buffer[BLUETOOTH_CH9141_BUFFER_SIZE];  // 数据存放数组

static          uint8   bluetooth_ch9141_data;

//-------------------------------------------------------------------------------------------------------------------
// @brief       FIFO 初始化 挂载对应缓冲区
// @param       *fifo           FIFO 对象指针
// @param       *buffer_addr    要挂载的缓冲区
// @param       size            缓冲区大小
// @return      fifo_state_enum 操作状态
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
fifo_state_enum fifo_init (fifo_struct *fifo, uint8 *buffer_addr, uint32 size)
{
    if(buffer_addr == NULL)
        return FIFO_BUFFER_NULL;
    fifo->buffer    = buffer_addr;
    fifo->head      = 0;
    fifo->end       = 0;
    fifo->size      = size;
    fifo->max       = size;
    return FIFO_SUCCESS;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       FIFO 头指针位移
// @param       *fifo           FIFO 对象指针
// @param       offset          偏移量
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void fifo_head_offset (fifo_struct *fifo, uint32 offset)
{
    fifo->head += offset;

    while(fifo->max <= fifo->head)                                              // 如果范围超过则减缓冲区大小 直到小于最大缓冲区大小
    {
        fifo->head -= fifo->max;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       FIFO 尾指针位移
// @param       *fifo           FIFO 对象指针
// @param       offset          偏移量
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void fifo_end_offset (fifo_struct *fifo, uint32 offset)
{
    fifo->end += offset;

    while(fifo->max <= fifo->end)                                               // 如果范围超过则减缓冲区大小 直到小于最大缓冲区大小
    {
        fifo->end -= fifo->max;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       FIFO 重置缓冲器
// @param       *fifo           FIFO 对象指针
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void fifo_clear (fifo_struct *fifo)
{
    fifo->head      = 0;
    fifo->end       = 0;
    fifo->size      = fifo->max;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       FIFO 查询当前数据个数
// @param       *fifo           FIFO 对象指针
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint32 fifo_used (fifo_struct *fifo)
{
    return (fifo->max - fifo->size);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       向 FIFO 中写入数据
// @param       *fifo           FIFO 对象指针
// @param       *dat            数据来源缓冲区指针
// @param       length          需要写入的数据长度
// @return      fifo_state_enum 操作状态
// Sample usage:                if(fifo_write_buffer(&fifo,data,32)!=FIFO_SUCCESS) while(1);
//-------------------------------------------------------------------------------------------------------------------
fifo_state_enum fifo_write_buffer (fifo_struct *fifo, uint8 *dat, uint32 length)
{
    uint32 temp_length;

    if(length < fifo->size)                                                     // 剩余空间足够装下本次数据
    {
        temp_length = fifo->max - fifo->head;                                   // 计算头指针距离缓冲区尾还有多少空间

        if(length > temp_length)                                                // 距离缓冲区尾长度不足写入数据 环形缓冲区分段操作
        {
            memcpy(&fifo->buffer[fifo->head], dat, temp_length);                // 拷贝第一段数据
            fifo_head_offset(fifo, temp_length);                                // 头指针偏移
            dat += temp_length;                                                 // 读取缓冲偏移
            memcpy(&fifo->buffer[fifo->head], dat, length - temp_length);       // 拷贝第一段数据
            fifo_head_offset(fifo, length - temp_length);                       // 头指针偏移
        }
        else
        {
            memcpy(&fifo->buffer[fifo->head], dat, length);                     // 一次完整写入
            fifo_head_offset(fifo, length);                                     // 头指针偏移
        }

        fifo->size -= length;                                                   // 缓冲区剩余长度减小
    }
    else
    {
        return FIFO_SPACE_NO_ENOUGH;
    }

    return FIFO_SUCCESS;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       从 FIFO 读取数据
// @param       *fifo           FIFO 对象指针
// @param       *dat            目标缓冲区指针
// @param       *length         读取的数据长度 如果没有这么多数据这里会被修改
// @param       flag            是否变更 FIFO 状态 可选择是否清空读取的数据
// @return      fifo_state_enum 操作状态
// Sample usage:                if(fifo_read_buffer(&fifo,data,32,FIFO_READ_ONLY)!=FIFO_SUCCESS) while(1);
//-------------------------------------------------------------------------------------------------------------------
fifo_state_enum fifo_read_buffer (fifo_struct *fifo, uint8 *dat, uint32 *length, fifo_operation_enum flag)
{
    uint8 data_check = 0;
    uint32 temp_length;

    if(*length > fifo_used(fifo))
    {
        *length = (fifo->max - fifo->size);                                     // 纠正读取的长度
        data_check = 1;                                                         // 标志数据不够
    }

    temp_length = fifo->max - fifo->end;                                        // 计算尾指针距离缓冲区尾还有多少空间
    if(*length <= temp_length)                                                  // 足够一次性读取完毕
    {
        if(NULL != dat)    memcpy(dat, &fifo->buffer[fifo->end], *length);      // 一次性读取完毕
    }
    else
    {
        if(NULL != dat)
        {
            memcpy(dat, &fifo->buffer[fifo->end], temp_length);                 // 拷贝第一段数据
            memcpy(&dat[temp_length], &fifo->buffer[0], *length - temp_length); // 拷贝第二段数据
        }
    }

    if(flag == FIFO_READ_AND_CLEAN)                                             // 如果选择读取并更改 FIFO 状态
    {
        fifo_end_offset(fifo, *length);                                         // 移动 FIFO 头指针
        fifo->size += *length;
    }

    return (data_check?FIFO_DATA_NO_ENOUGH:FIFO_SUCCESS);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      蓝牙转串口模块 串口中断回调函数
//  @param      void
//  @return     void
//  Sample usage:
//  @note       该函数在ISR文件 串口中断程序被调用
//-------------------------------------------------------------------------------------------------------------------
void bluetooth_ch9141_uart_callback (void)
{
    // 读取无线串口的数据 并且置位接收标志
    uart_query(BLUETOOTH_CH9141_INDEX, &bluetooth_ch9141_data);
    fifo_write_buffer(&bluetooth_ch9141_fifo, &bluetooth_ch9141_data, 1);       // 存入 FIFO
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      蓝牙转串口模块初始化
//  @param      mode            蓝牙模式 MASTER_MODE(主机)或者SLAVE_MODE(从机)
// @return      uint8           初始化状态 0-成功 1-失败
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 bluetooth_ch9141_init (void)
{
    wireless_type = WIRELESS_CH9141;
    // 本函数使用的波特率为115200 为蓝牙转串口模块的默认波特率 如需其他波特率请使用上位机修改模块参数
    fifo_init(&bluetooth_ch9141_fifo, bluetooth_ch9141_buffer, BLUETOOTH_CH9141_BUFFER_SIZE);
    gpio_init(BLUETOOTH_CH9141_RTS_PIN, GPI, 1, PULLUP);                   // 初始化流控引脚
    uart_init(BLUETOOTH_CH9141_INDEX, BLUETOOTH_CH9141_BUAD_RATE, BLUETOOTH_CH9141_RX_PIN, BLUETOOTH_CH9141_TX_PIN);
    return 0;
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块 发送函数
//  @param      buff            需要发送的数据地址
//  @param      len             发送长度
//  @return     uint32          剩余未发送的字节数
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint32 bluetooth_ch9141_send_buff (uint8 *buff, uint32 len)
{
    uint16 time_count = 0;
    while(len > 30)
    {
        time_count = 0;
        while(gpio_get(BLUETOOTH_CH9141_RTS_PIN) && time_count++ < BLUETOOTH_CH9141_TIMEOUT_COUNT)  // 如果RTS为低电平，则继续发送数据
            systick_delay_ms(STM0, 1);
        if(time_count >= BLUETOOTH_CH9141_TIMEOUT_COUNT)
            return len;                                                         // 模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
        uart_putbuff(BLUETOOTH_CH9141_INDEX, buff, 30);

        buff += 30;                                                             // 地址偏移
        len -= 30;                                                              // 数量
    }

    time_count = 0;
    while(gpio_get(BLUETOOTH_CH9141_RTS_PIN) && time_count++ < BLUETOOTH_CH9141_TIMEOUT_COUNT)      // 如果RTS为低电平，则继续发送数据
        systick_delay_ms(STM0, 1);
    if(time_count >= BLUETOOTH_CH9141_TIMEOUT_COUNT)
        return len;                                                             // 模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
    uart_putbuff(BLUETOOTH_CH9141_INDEX, buff, len);                            // 发送最后的数据

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块 读取函数
//  @param      buff            存储的数据地址
//  @param      len             长度
//  @return     uint32          实际读取字节数
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint32 bluetooth_ch9141_read_buff (uint8 *buff, uint32 len)
{
    uint32 data_len = len;
    fifo_read_buffer(&bluetooth_ch9141_fifo, buff, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}

