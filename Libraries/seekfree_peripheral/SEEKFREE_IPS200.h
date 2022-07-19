
/*/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		2.0寸IPS屏幕
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.5.2
 * @Target core		TC264
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-05-07
 * @note		
            接线定义：
    ------------------------------------
*                                                           模块管脚                                             单片机管脚
*                   // 双排排针 并口两寸屏 硬件引脚
*                   RD                  查看 SEEKFREE_IPS200.h 中 IPS200_RD_PIN_PARALLEL8     宏定义
*                   WR                  查看 SEEKFREE_IPS200.h 中 IPS200_WR_PIN_PARALLEL8     宏定义
*                   RS                  查看 SEEKFREE_IPS200.h 中 IPS200_RS_PIN_PARALLEL8     宏定义
*                   RST                 查看 SEEKFREE_IPS200.h 中 IPS200_RST_PIN_PARALLEL8    宏定义
*                   CS                  查看 SEEKFREE_IPS200.h 中 IPS200_CS_PIN_PARALLEL8     宏定义
*                   BL                  查看 SEEKFREE_IPS200.h 中 IPS200_BL_PIN_PARALLEL8     宏定义
*                   D0-D7               查看 SEEKFREE_IPS200.h 中 IPS200_Dx_PIN_PARALLEL8     宏定义
*                   // 单排排针 SPI 两寸屏 硬件引脚
*                   SCL                 查看 SEEKFREE_IPS200.h 中 IPS200_SCL_PIN_SPI  宏定义
*                   SDA                 查看 SEEKFREE_IPS200.h 中 IPS200_SDA_PIN_SPI  宏定义
*                   RST                 查看 SEEKFREE_IPS200.h 中 IPS200_RST_PIN_SPI  宏定义
*                   DC                  查看 SEEKFREE_IPS200.h 中 IPS200_DC_PIN_SPI   宏定义
*                   CS                  查看 SEEKFREE_IPS200.h 中 IPS200_CS_PIN_SPI   宏定义
*                   BL                  查看 SEEKFREE_IPS200.h 中 IPS200_BL_PIN_SPI  宏定义
*                                                           电源引脚
*                   VCC                 3.3V电源
*                   GND                 电源地
*                                                           最大分辨率 320 * 240
*   ------------------------------------

 ********************************************************************************************************************/

#ifndef _SEEKFREE_IPS200_H
#define _SEEKFREE_IPS200_H

#include "common.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "zf_stm_systick.h"
#include "zf_gpio.h"
#include "zf_assert.h"
#include "SEEKFREE_PRINTF.h"
#include "zf_spi.h"
#include "SEEKFREE_FUN.h"
#include "SEEKFREE_FONT.h"

     
//-------常用颜色在SEEKFREE_FONT.h文件中定义----------
//#define RED          	    0xF800	//红色
//#define BLUE         	    0x001F  //蓝色
//#define YELLOW       	    0xFFE0	//黄色
//#define GREEN        	    0x07E0	//绿色
//#define WHITE        	    0xFFFF	//白色
//#define BLACK        	    0x0000	//黑色 
//#define GRAY  			0X8430 	//灰色
//#define BROWN 			0XBC40 	//棕色
//#define PURPLE    		0XF81F	//紫色
//#define PINK    		    0XFE19	//粉色


#define IPS200_BGCOLOR      RGB565_WHITE	//背景颜色
#define IPS200_PENCOLOR     RGB565_RED		//画笔颜色

// 如果使用的是单排排针的两寸屏幕 SPI 驱动控制引脚 可以修改
#define IPS200_SPIN             SPI_2           //定义使用的SPI号
#define IPS200_SCL_PIN_SPI      SPI2_SCLK_P15_3 //定义SPI_SCK引脚
#define IPS200_SDA_PIN_SPI      SPI2_MOSI_P15_5 //定义SPI_MOSI引脚
#define IPS200_SDA_IN_PIN_SPI   SPI2_MISO_P15_4 //定义SPI_MISO引脚  IPS没有MISO引脚，但是这里任然需要定义，在spi的初始化时需要使用
#define IPS200_CS_PIN_SPI       SPI2_CS0_P15_2  //定义SPI_CS引脚

// 如果使用的是单排排针的两寸屏幕 SPI 驱动控制引脚 可以修改
#define IPS200_RST_PIN_SPI      P15_1   // 液晶复位引脚定义
#define IPS200_DC_PIN_SPI       P15_0
#define IPS200_BL_PIN_SPI       P15_4


//如果使用的是双排排针的两寸屏幕 并口驱动控制引脚 可以修改
//引脚只能选择B C D这三个端口中的引脚，便于使用快速GPIO以提高显示速度
#define IPS200_RD_PIN_PARALLEL8  		P15_3
#define IPS200_WR_PIN_PARALLEL8  		P15_5
#define IPS200_RS_PIN_PARALLEL8  		P15_1
#define IPS200_RST_PIN_PARALLEL8 		P15_0
#define IPS200_CS_PIN_PARALLEL8  		P15_2
#define IPS200_BL_PIN_PARALLEL8  		P15_4

//并口驱动数据引脚 可以修改 如果你的屏幕是双排排针 这里的引脚用得到
//D0-D3四个数据引脚必须连续 例如C0-C3,C1-C4等等，
//D4-D7四个数据引脚必须连续 例如B0-B3,B1-B4等等。
//可以连接到不同端口的意思就是屏幕的D0-D3与C1-C4连接，D4-D7与B2-B5连接。
//切换引脚后注意修改IPS200_DATA_PORT1和IPS200_DATA_PORT2宏定义
#define IPS200_D0_PIN_PARALLEL8       P11_9
#define IPS200_D1_PIN_PARALLEL8       P11_10
#define IPS200_D2_PIN_PARALLEL8       P11_11
#define IPS200_D3_PIN_PARALLEL8       P11_12
#define IPS200_D4_PIN_PARALLEL8       P13_0
#define IPS200_D5_PIN_PARALLEL8       P13_1
#define IPS200_D6_PIN_PARALLEL8       P13_2
#define IPS200_D7_PIN_PARALLEL8       P13_3

//定义数据端口所在PORT，切换引脚后务必根据引脚所在PORT进行更改
#define IPS200_DATA_PORT1    3       //0：P00端口  1：P02端口  2：P10端口  3：P11端口  4：P13端口  5：P14端口  6：P15端口  7：P20端口  8：P21端口  9：P22端口  10：P23端口  11：P32端口  12：P33端口

#define IPS200_DATAPORT1    (((Ifx_P *)IfxPort_cfg_indexMap[IPS200_DATA_PORT1].module)->OUT.U)      //宏定义数据口GPIO的输出寄存器
#define DATA_START_NUM1     (IPS200_D0_PIN_PARALLEL8&0x1f)  //宏定义数据引脚的起始编号


#define IPS200_DATA_PORT2    4       //0：P00端口  1：P02端口  2：P10端口  3：P11端口  4：P13端口  5：P14端口  6：P15端口  7：P20端口  8：P21端口  9：P22端口  10：P23端口  11：P32端口  12：P33端口
                            
#define IPS200_DATAPORT2    (((Ifx_P *)IfxPort_cfg_indexMap[IPS200_DATA_PORT2].module)->OUT.U)      //宏定义数据口GPIO的输出寄存器
#define DATA_START_NUM2     (IPS200_D4_PIN_PARALLEL8&0x1f)  //宏定义数据引脚的起始编号




#define IPS200_BL(x)		gpio_set(IPS200_BL_PIN_PARALLEL8,x)
#define IPS200_CS(x)       	gpio_set(IPS200_CS_PIN_PARALLEL8,x)
#define IPS200_RD(x)       	gpio_set(IPS200_RD_PIN_PARALLEL8,x)
#define IPS200_WR(x)       	gpio_set(IPS200_WR_PIN_PARALLEL8,x)
#define IPS200_RS(x)       	gpio_set(IPS200_RS_PIN_PARALLEL8,x)
#define IPS200_RST(x)      	gpio_set(ips_rst_pin,x)

#define IPS200_DC(x)        gpio_set(IPS200_DC_PIN_SPI,x)

#define IPS200_W 240
#define IPS200_H 320

typedef enum
{
    IPS200_TYPE_SPI,                                                            // SPI 驱动
    IPS200_TYPE_PARALLEL8,                                                      // 并口驱动
}ips200_type_enum;

//定义显示方向
//0 竖屏模式
//1 竖屏模式  旋转180°
//2 横屏模式
//3 横屏模式  旋转180°
#define IPS200_DISPLAY_DIR 0

#if (0==IPS200_DISPLAY_DIR || 1==IPS200_DISPLAY_DIR)
#define	IPS200_X_MAX	IPS200_W	//液晶X方宽度
#define IPS200_Y_MAX	IPS200_H   //液晶Y方宽度
     
#elif (2==IPS200_DISPLAY_DIR || 3==IPS200_DISPLAY_DIR)
#define	IPS200_X_MAX	IPS200_H	//液晶X方宽度
#define IPS200_Y_MAX	IPS200_W   //液晶Y方宽度
     
#else
#error "IPS200_DISPLAY_DIR 定义错误"
     
#endif


void ips200_init(ips200_type_enum type_select); //初始化硬件
void ips200_w_data(uint8 dat);
void ips200_wr_reg(uint8 com);
void ips200_wr_data(uint8 dat);
void ips200_wr_data16(uint16 dat);
void ips200_w_reg(uint8 com,uint8 dat);
void ips200_address_set(uint16 x1,uint16 y1,uint16 x2,uint16 y2);
void ips200_clear(uint16 color);
void ips200_drawpoint(uint16 x,uint16 y,uint16 color);
void ips200_showchar(uint16 x,uint16 y,const int8 dat);
void ips200_showstr(uint16 x,uint16 y,const int8 dat[]);


void ips200_showint8(uint16 x,uint16 y,int8 dat);
void ips200_showuint8(uint16 x,uint16 y,uint8 dat);
void ips200_showint16(uint16 x,uint16 y,int16 dat);
void ips200_showuint16(uint16 x,uint16 y,uint16 dat);
void ips200_showint32(uint16 x,uint16 y,int dat,uint8 num);
void ips200_showfloat(uint16 x,uint16 y,double dat,int8 num,int8 pointnum);
void ips200_showimage(uint16 x,uint16 y,uint16 w,uint16 l,const unsigned char *p);

void ips200_displayimage032(uint8 *p, uint16 width, uint16 height);
void ips200_displayimage032_zoom(uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage032_zoom1(uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_zoom1(uint16 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_grayscale_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage7725(uint8 *p, uint16 width, uint16 height);
void ips200_display_chinese(uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, uint16 color);

#endif

