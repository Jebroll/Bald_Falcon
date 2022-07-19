/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		无线转串口模块
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 * @note		
					接线定义：
					------------------------------------ 
					    无线转串口       单片机                        
    					RX              查看SEEKFREE_WIRELESS.h文件中的WIRELESS_UART_TX宏定义
    					TX              查看SEEKFREE_WIRELESS.h文件中的WIRELESS_UART_RX宏定义
    					RTS             查看SEEKFREE_WIRELESS.h文件中的RTS_PIN宏定义
    					CMD             悬空或者上拉
					------------------------------------ 
 ********************************************************************************************************************/


#include "zf_stm_systick.h"
#include "zf_gpio.h"
#include "zf_uart.h"
#include "SEEKFREE_WIRELESS.h"


uint8 wireless_send_buffer[WIRELESS_BUFFER_SIZE];
uint32 wireless_rx_index = 0;

vuint8 wireless_auto_baud_num;
vuint8 wireless_auto_baud_flag = 0;
vuint8 wireless_auto_baud_data[3] = {0x00, 0x01, 0x03};
uint8 wireless_rx_buffer;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块 串口中断函数
//  @param      void
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数在ISR文件 串口2中断程序被调用
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_callback(void)
{
    //读取收到的所有数据
	while(uart_query(WIRELESS_UART, &wireless_rx_buffer));
    if(wireless_auto_baud_flag == 1 && (wireless_auto_baud_num<3))
    {
        wireless_auto_baud_data[wireless_auto_baud_num] = wireless_rx_buffer;
        wireless_auto_baud_num++;
        if(3 == wireless_auto_baud_num)
        {
            wireless_auto_baud_flag = 2;
        }
    }
    else
    {
        wireless_send_buffer[wireless_rx_index++] = wireless_rx_buffer;
        if(wireless_rx_index == WIRELESS_BUFFER_SIZE)
            wireless_rx_index=0;
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块初始化
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void seekfree_wireless_init(void)
{
    //本函数使用的波特率为115200，为无线转串口模块的默认波特率，如需其他波特率请自行配置模块并修改串口的波特率
    wireless_type = WIRELESS_SI24R1;
    gpio_init(RTS_PIN, GPI, 0, PULLDOWN);//初始化流控引脚
#if(0 == WIRELESS_AUTO_UART_BAUD)
    uart_init (WIRELESS_UART, WIRELESS_UART_BAUD, WIRELESS_UART_TX, WIRELESS_UART_RX);	//初始换串口
#elif(1 == WIRELESS_AUTO_UART_BAUD)//开启自动波特率
    boolean temp_isr;
    gpio_init(RTS_PIN, GPI, 0, PULLDOWN);//初始化流控引脚
    uint8 rts_init_status;
    rts_init_status = gpio_get(RTS_PIN);

    temp_isr = areInterruptsEnabled();
    enableInterrupts();
    gpio_init(RTS_PIN, GPO, rts_init_status, PUSHPULL);//初始化流控引脚

    uart_init (WIRELESS_UART, WIRELESS_UART_BAUD, WIRELESS_UART_TX, WIRELESS_UART_RX);  //初始换串口

    systick_delay_ms(STM0, 5);  //模块上电之后需要延时等待
    gpio_set(RTS_PIN, !rts_init_status);   //RTS引脚拉高，进入自动波特率模式
    systick_delay_ms(STM0, 100);   //RTS拉高之后必须延时20ms
    gpio_toggle(RTS_PIN);    //RTS引脚取反
    //gpio_set(RTS_PIN, 0);   //RTS拉低

    wireless_auto_baud_flag = 1;
    
    //发送特定数据 用于模块自动判断波特率
    uart_putchar(WIRELESS_UART, wireless_auto_baud_data[0]);
    uart_putchar(WIRELESS_UART, wireless_auto_baud_data[1]);
    uart_putchar(WIRELESS_UART, wireless_auto_baud_data[2]);

    systick_delay_ms(STM0, 20);
    //检验自动波特率是否完成
    if(2 != wireless_auto_baud_flag)
    {
        //如果程序进入到此语句内，说明自动波特率失败了
        systick_delay_ms(STM0, 500);
        while(1);
    }

    //检验自动波特率是否正确
    if(0xa5 != wireless_auto_baud_data[0] &&
       0xff != wireless_auto_baud_data[1] &&
       0xff != wireless_auto_baud_data[2] )
    {
        //如果程序进入到此语句内，说明自动波特率失败了
        systick_delay_ms(STM0, 500);
        while(1);
    }

    gpio_init(RTS_PIN, GPI, 0, PUSHPULL);//初始化流控引脚
    systick_delay_ms(STM0, 10);//延时等待 模块准备就绪
    restoreInterrupts(temp_isr);
#endif

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块 发送函数
//  @param      buff        需要发送的数据地址
//  @param      len         发送长度
//  @return     uint32      剩余未发送的字节数   
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
uint32 seekfree_wireless_send_buff(uint8 *buff, uint32 len)
{
    while(len>30)
    {
//        if(gpio_get(RTS_PIN))
//        {
//            return len;//模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
//        }
        while(gpio_get(RTS_PIN));  //如果RTS为低电平，则继续发送数据
        uart_putbuff(WIRELESS_UART,buff,30);

        buff += 30; //地址偏移
        len -= 30;//数量
    }
    
//    if(gpio_get(RTS_PIN))
//    {
//        return len;//模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
//    }
    while(gpio_get(RTS_PIN));  //如果RTS为低电平，则继续发送数据
    uart_putbuff(WIRELESS_UART,buff,len);//发送最后的数据
    
    return 0;
}
