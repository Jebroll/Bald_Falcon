/*********************************************************************************************************************
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
 * @date       		2022-05-07
 * @note		
             接线定义：
    ------------------------------------------------------------------------
*                                                           模块管脚                                             单片机管脚
*                   // 双排排针 并口两寸屏 硬件引脚
*                   RD                  查看 SEEKFREE_IPS200.h 中 IPS200_RD_PIN_PARALLEL8     宏定义
*                   WR                  查看 SEEKFREE_IPS200.h 中 IPS200_WR_PIN_PARALLEL8     宏定义
*                   RS                  查看 SEEKFREE_IPS200.h 中 IPS200_RS_PIN_PARALLEL8     宏定义
*                   RST                 查看 SEEKFREE_IPS200.h 中 IPS200_RST_PIN_PARALLEL8    宏定义
*                   CS                  查看 SEEKFREE_IPS200.h 中 IPS200_CS_PIN_PARALLEL8     宏定义
*                   BL                  查看 SEEKFREE_IPS200.h 中 IPS200_BL_PIN_PARALLEL8     宏定义
*                   D0-D7               查看 SEEKFREE_IPS200.h 中 IPS200_Dx_PIN_PARALLEL8     宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   // 单排排针 SPI 两寸屏 硬件引脚
*                   SCL                 查看 SEEKFREE_IPS200.h 中 IPS200_SCL_PIN_SPI  宏定义
*                   SDA                 查看 SEEKFREE_IPS200.h 中 IPS200_SDA_PIN_SPI  宏定义
*                   RST                 查看 SEEKFREE_IPS200.h 中 IPS200_RST_PIN_SPI  宏定义
*                   DC                  查看 SEEKFREE_IPS200.h 中 IPS200_DC_PIN_SPI   宏定义
*                   CS                  查看 SEEKFREE_IPS200.h 中 IPS200_CS_PIN_SPI   宏定义
*                   BL                  查看 SEEKFREE_IPS200.h 中 IPS200_BL_PIN_SPI  宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                                                           最大分辨率 320 * 240
*   ------------------------------------------------------------------------

 ********************************************************************************************************************/

#include "SEEKFREE_IPS200.h"

static ips200_type_enum ips200_display_type = IPS200_TYPE_SPI;
static PIN_enum ips_rst_pin = IPS200_RST_PIN_SPI;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      dat     数据
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ips200_w_data(uint8 dat)           //写数据
{
    IPS200_DATAPORT1 = (dat << DATA_START_NUM1) | (IPS200_DATAPORT1 & ~((uint32)(0x0F << DATA_START_NUM1)) );
    IPS200_DATAPORT2 = ((dat>>4) << DATA_START_NUM2) | (IPS200_DATAPORT2 & ~((uint32)(0x0F << DATA_START_NUM2)) );
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      command     命令
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ips200_wr_reg(uint8 command)			//写命令
{
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_DC(0);
        spi_mosi(IPS200_SPIN,IPS200_CS_PIN_SPI,&command,NULL,1,1);
        IPS200_DC(1);
    }
    else
    {
        IPS200_CS(0);
        IPS200_RS(0);
        IPS200_RD(1);
        IPS200_WR(0);
        ips200_w_data(command);
        IPS200_WR(1);
        IPS200_CS(1);
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      dat     8位数据
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ips200_wr_data(uint8 dat)			//向液晶屏写一个8位数据
{
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        spi_mosi(IPS200_SPIN,IPS200_CS_PIN_SPI,&dat,NULL,1,1);
    }
    else
    {
        IPS200_CS(0);
        IPS200_RS(1);
        IPS200_RD(1);
        IPS200_WR(0);
        ips200_w_data(dat);
        IPS200_WR(1);
        IPS200_CS(1);
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      dat     16位数据
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ips200_wr_data16(uint16 dat)		//向液晶屏写一个16位数据
{
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        uint8 dat1[2];
        dat1[0] = dat >> 8;
        dat1[1] = (uint8)dat;
        spi_mosi(IPS200_SPIN,IPS200_CS_PIN_SPI,dat1,NULL,2,1);
    }
    else
    {
        IPS200_CS(0);
        IPS200_RS(1);
        IPS200_RD(1);
        IPS200_WR(0);
        ips200_w_data((uint8)(dat>>8));
        IPS200_WR(1);
        IPS200_WR(0);
        ips200_w_data((uint8)(dat));
        IPS200_WR(1);
        IPS200_CS(1);
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param       com             命令
//  @param       dat             数据
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ips200_w_reg(uint8 com,uint8 dat)		//写寄存器
{
	ips200_wr_reg(com);
	ips200_wr_data(dat);
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief       设置显示区域 内部调用
//  @param       x1              起始x轴坐标
//  @param       y1              起始y轴坐标
//  @param       x2              结束x轴坐标
//  @param       y2              结束y轴坐标
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ips200_address_set(uint16 x1,uint16 y1,uint16 x2,uint16 y2)
{ 
	ips200_wr_reg(0x2a);
	ips200_wr_data16(x1);
	ips200_wr_data16(x2);
	
	ips200_wr_reg(0x2b);
	ips200_wr_data16(y1);
	ips200_wr_data16(y2);
	
	ips200_wr_reg(0x2c);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      2.0寸 IPS液晶初始化
//  @return     type_select     并口或者串口选择
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ips200_init(ips200_type_enum type_select)
{
    if(IPS200_TYPE_SPI == type_select)
    {
        ips200_display_type = IPS200_TYPE_SPI;
        ips_rst_pin = IPS200_RST_PIN_SPI;
        spi_init(IPS200_SPIN, IPS200_SCL_PIN_SPI, IPS200_SDA_PIN_SPI, IPS200_SDA_IN_PIN_SPI, IPS200_CS_PIN_SPI, 0, 30*1000*1000);//硬件SPI初始化

        gpio_init(IPS200_BL_PIN_SPI,GPO,1,PUSHPULL);
        gpio_init(IPS200_DC_PIN_SPI,GPO,0,PUSHPULL);
        gpio_init(ips_rst_pin,GPO,0,PUSHPULL);
    }
    else
    {
        ips200_display_type = IPS200_TYPE_PARALLEL8;
        ips_rst_pin = IPS200_RST_PIN_PARALLEL8;
        gpio_init(IPS200_D0_PIN_PARALLEL8, GPO, 0, PUSHPULL);
        gpio_init(IPS200_D1_PIN_PARALLEL8, GPO, 0, PUSHPULL);
        gpio_init(IPS200_D2_PIN_PARALLEL8, GPO, 0, PUSHPULL);
        gpio_init(IPS200_D3_PIN_PARALLEL8, GPO, 0, PUSHPULL);
        gpio_init(IPS200_D4_PIN_PARALLEL8, GPO, 0, PUSHPULL);
        gpio_init(IPS200_D5_PIN_PARALLEL8, GPO, 0, PUSHPULL);
        gpio_init(IPS200_D6_PIN_PARALLEL8, GPO, 0, PUSHPULL);
        gpio_init(IPS200_D7_PIN_PARALLEL8, GPO, 0, PUSHPULL);

        gpio_init(IPS200_BL_PIN_PARALLEL8, GPO, 0, PUSHPULL);
        gpio_init(IPS200_CS_PIN_PARALLEL8, GPO, 0, PUSHPULL);
        gpio_init(ips_rst_pin, GPO, 0, PUSHPULL);
        gpio_init(IPS200_RS_PIN_PARALLEL8, GPO, 0, PUSHPULL);
        gpio_init(IPS200_WR_PIN_PARALLEL8, GPO, 0, PUSHPULL);
        gpio_init(IPS200_RD_PIN_PARALLEL8, GPO, 0, PUSHPULL);
    }
	IPS200_BL(1);
	IPS200_RST(0);	
	systick_delay_ms(STM0, 5);
	IPS200_RST(1);		
	systick_delay_ms(STM0, 5);
	
	ips200_wr_reg(0x11);
	systick_delay_ms(STM0, 120);
	
	ips200_wr_reg(0x36);			
    if      (IPS200_DISPLAY_DIR==0)    ips200_wr_data(0x00);
    else if (IPS200_DISPLAY_DIR==1)    ips200_wr_data(0xC0);
    else if (IPS200_DISPLAY_DIR==2)    ips200_wr_data(0x70);
    else                            ips200_wr_data(0xA0);
    

	ips200_wr_reg(0x3A);			
	ips200_wr_data(0x05);
	
	ips200_wr_reg(0xB2);			
	ips200_wr_data(0x0C);
	ips200_wr_data(0x0C); 
	ips200_wr_data(0x00); 
	ips200_wr_data(0x33); 
	ips200_wr_data(0x33); 			

	ips200_wr_reg(0xB7);			
	ips200_wr_data(0x35);

	ips200_wr_reg(0xBB);			
	ips200_wr_data(0x29); //32 Vcom=1.35V
															
	ips200_wr_reg(0xC2);			
	ips200_wr_data(0x01);

	ips200_wr_reg(0xC3);			
	ips200_wr_data(0x19); //GVDD=4.8V 
															
	ips200_wr_reg(0xC4);			
	ips200_wr_data(0x20); //VDV, 0x20:0v

	ips200_wr_reg(0xC5);			
	ips200_wr_data(0x1A);//VCOM Offset Set

	ips200_wr_reg(0xC6);			
	ips200_wr_data(0x01F); //0x0F:60Hz        	

	ips200_wr_reg(0xD0);			
	ips200_wr_data(0xA4);
	ips200_wr_data(0xA1); 											  												  																								
				
	ips200_wr_reg(0xE0);     
	ips200_wr_data(0xD0);   
	ips200_wr_data(0x08);   
	ips200_wr_data(0x0E);   
	ips200_wr_data(0x09);   
	ips200_wr_data(0x09);   
	ips200_wr_data(0x05);   
	ips200_wr_data(0x31);   
	ips200_wr_data(0x33);   
	ips200_wr_data(0x48);   
	ips200_wr_data(0x17);   
	ips200_wr_data(0x14);   
	ips200_wr_data(0x15);   
	ips200_wr_data(0x31);   
	ips200_wr_data(0x34);   

	ips200_wr_reg(0xE1);     
	ips200_wr_data(0xD0);   
	ips200_wr_data(0x08);   
	ips200_wr_data(0x0E);   
	ips200_wr_data(0x09);   
	ips200_wr_data(0x09); 
	ips200_wr_data(0x15);   
	ips200_wr_data(0x31);   
	ips200_wr_data(0x33);   
	ips200_wr_data(0x48);   
	ips200_wr_data(0x17);   
	ips200_wr_data(0x14);   
	ips200_wr_data(0x15);   
	ips200_wr_data(0x31);   
	ips200_wr_data(0x34);   

	ips200_wr_reg(0x21);
	
	ips200_wr_reg(0x29);
	ips200_clear(IPS200_BGCOLOR);	//初始化为白屏
} 


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶清屏函数
//  @param      color     		颜色设置
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_clear(YELLOW);// 全屏设置为黄色
//-------------------------------------------------------------------------------------------------------------------
void ips200_clear(uint16 color) 
{ 
	uint16 i,j;  	
	ips200_address_set(0,0,IPS200_X_MAX-1,IPS200_Y_MAX-1);
	for(i=0;i<IPS200_X_MAX;i++)
	{
		for (j=0;j<IPS200_Y_MAX;j++)
		{
			ips200_wr_data16(color);	 			 
		}
	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶画点
//  @param      x     	        坐标x方向的起点
//  @param      y     	        坐标y方向的起点
//  @param      dat       	    需要显示的颜色
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_drawpoint(0,0,RED);  //坐标0,0画一个红色的点
//-------------------------------------------------------------------------------------------------------------------
void ips200_drawpoint(uint16 x,uint16 y,uint16 color)
{
    ips200_address_set(x,y,x,y);
    ips200_wr_data16(color);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符
//  @param      x     	        坐标x方向的起点 参数范围 0 - (IPS200_X_MAX-1)
//  @param      y     	        坐标y方向的起点 参数范围 0 - (IPS200_Y_MAX/16-1)
//  @param      dat       	    需要显示的字符
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_showchar(0,0,'x');//坐标0,0写一个字符x
//-------------------------------------------------------------------------------------------------------------------
void ips200_showchar(uint16 x,uint16 y,const int8 dat)
{
	uint8 i,j;
	uint8 temp;
    
	for(i=0; i<16; i++)
	{
		ips200_address_set(x,y+i,x+7,y+i);
		temp = tft_ascii[(uint16)dat-32][i];//减32因为是取模是从空格开始取得 空格在ascii中序号是32
		for(j=0; j<8; j++)
		{
			if(temp&0x01)	ips200_wr_data16(IPS200_PENCOLOR);
			else			ips200_wr_data16(IPS200_BGCOLOR);
			temp>>=1;
		}
	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符串
//  @param      x     	        坐标x方向的起点  参数范围 0 - (IPS200_X_MAX-1)
//  @param      y     	        坐标y方向的起点  参数范围 0 - (IPS200_Y_MAX/16-1)
//  @param      dat       	    需要显示的字符串
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_showstr(0,0,"seekfree");
//-------------------------------------------------------------------------------------------------------------------
void ips200_showstr(uint16 x,uint16 y,const int8 dat[])
{         
	uint16 j;
	
	j = 0;
	while(dat[j] != '\0')
	{
		ips200_showchar(x+8*j,y*16,dat[j]);
		j++;
	}
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示8位有符号
//  @param      x     	        坐标x方向的起点  参数范围 0 -（IPS200_X_MAX-1）
//  @param      y     	        坐标y方向的起点  参数范围 0 -（IPS200_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int8
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_showint8(0,0,x);//x为int8类型
//-------------------------------------------------------------------------------------------------------------------
void ips200_showint8(uint16 x,uint16 y,int8 dat)
{
	uint8 a[3];
	uint8 i;
	if(dat<0)
	{
		ips200_showchar(x,y*16,'-');
		dat = -dat;
	}
	else	ips200_showchar(x,y*16,' ');
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		ips200_showchar(x+(8*(i+1)),y*16,'0' + a[i]);
		i++;
	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示8位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（IPS200_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（IPS200_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint8
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_showuint8(0,0,x);//x为uint8类型
//-------------------------------------------------------------------------------------------------------------------
void ips200_showuint8(uint16 x,uint16 y,uint8 dat)
{
	uint8 a[3];
	uint8 i;
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		ips200_showchar(x+(8*i),y*16,'0' + a[i]);
		i++;
	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示16位有符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（IPS200_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（IPS200_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int16
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_showint16(0,0,x);//x为int16类型
//-------------------------------------------------------------------------------------------------------------------
void ips200_showint16(uint16 x,uint16 y,int16 dat)
{
	uint8 a[5];
	uint8 i;
	if(dat<0)
	{
		ips200_showchar(x,y*16,'-');
		dat = -dat;
	}
	else	ips200_showchar(x,y*16,' ');

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		ips200_showchar(x+(8*(i+1)),y*16,'0' + a[i]);
		i++;
	}
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示16位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（IPS200_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（IPS200_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint16
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_showuint16(0,0,x);//x为uint16类型
//-------------------------------------------------------------------------------------------------------------------
void ips200_showuint16(uint16 x,uint16 y,uint16 dat)
{
	uint8 a[5];
	uint8 i;

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		ips200_showchar(x+(8*i),y*16,'0' + a[i]);
		i++;
	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示32位有符号(去除整数部分无效的0)
//  @param      x     	        坐标x方向的起点 参数范围 0 -（IPS200_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（IPS200_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint32
//  @param      num       	    需要显示的位数 最高10位  不包含正负号
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_showint32(0,0,x,3);//x可以为int32 uint16 int16 uint8 int8类型
//  Sample usage:               负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void ips200_showint32(uint16 x,uint16 y,int dat,uint8 num)
{
    int8    buff[34];
    uint32   length;
    
    if(10<num)      num = 10;
    
	
    num++;
    if(0>dat)   length = zf_sprintf(&buff[0],"%d",dat);//负数
    else
    {
        buff[0] = ' ';
        length = zf_sprintf(&buff[1],"%d",dat);
        length++;
    }
    while(length < num)
    {
        buff[length] = ' ';
        length++;
    }
    buff[num] = '\0';

    ips200_showstr(x, y, buff);	//显示数字
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示浮点数(去除整数部分无效的0)
//  @param      x     	        坐标x方向的起点 参数范围 0 -（IPS200_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（IPS200_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型float或double
//  @param      num       	    整数位显示长度   最高10位  
//  @param      pointnum        小数位显示长度   最高6位
//  @return     void
//  @since      v1.0
//  Sample usage:               ips_showfloat(0,0,x,2,3);//显示浮点数   整数显示2位   小数显示三位
//  @note                       特别注意当发现小数部分显示的值与你写入的值不一样的时候，
//                              可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
//                              有关问题的详情，请自行百度学习   浮点数精度丢失问题。
//                              负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void ips200_showfloat(uint16 x,uint16 y,double dat,int8 num,int8 pointnum)
{
    uint32   length;
	int8    buff[34];
	int8    start,end,point;

	if(6<pointnum)  pointnum = 6;
    if(10<num)      num = 10;
        
    if(0>dat)   length = zf_sprintf( &buff[0],"%f",dat);//负数
    else
    {
        length = zf_sprintf( &buff[1],"%f",dat);
        length++;
    }
    point = (int8)(length - 7);         //计算小数点位置
    start = point - num - 1;    //计算起始位
    end = point + pointnum + 1; //计算结束位
    while(0>start)//整数位不够  末尾应该填充空格
    {
        buff[end] = ' ';
        end++;
        start++;
    }
    
    if(0>dat)   buff[start] = '-';
    else        buff[start] = ' ';
    
    buff[end] = '\0';

    ips200_showstr(x, y, buff);	//显示数字
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示8位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（IPS200_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（IPS200_Y_MAX/16-1）
//  @param      w       	    图像宽度
//  @param      l       	    图像高度
//  @param      *p       	    图像数组地址
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_showimage(0,0,10,20,&image);//图像起点(0,0)。宽10，高20。
//-------------------------------------------------------------------------------------------------------------------
void ips200_showimage(uint16 x,uint16 y,uint16 w,uint16 l,const unsigned char *p)
{
  int i;
  unsigned char picH,picL;
  ips200_address_set(x,y,x+w-1,y+l-1);
  for(i=0;i<w*l;i++)
  {
    picL=*(p+i*2);
    picH=*(p+i*2+1);
    ips200_wr_data16(picH<<8|picL);  
  }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      总钻风(灰度摄像头)液晶显示函数
//  @param      *p     			图像数组地址
//  @param      width     	    图像宽度
//  @param      height     	    图像高度
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_displayimage032(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H)//显示灰度摄像头 图像
//  @note       图像的宽度如果超过液晶的宽度，则自动进行缩放显示。这样可以显示全视野
//-------------------------------------------------------------------------------------------------------------------
void ips200_displayimage032(uint8 *p, uint16 width, uint16 height) 
{
    uint32 i,j;
                
    uint16 color = 0;
	uint16 temp = 0;
	
    uint16 coord_x = 0;
    uint16 coord_y = 0;
    
    coord_x = width>IPS200_X_MAX?IPS200_X_MAX:width;
    coord_y = height>IPS200_Y_MAX?IPS200_Y_MAX:height;
    ips200_address_set(0,0,coord_x-1,coord_y-1);
    
    for(j=0;j<coord_y;j++)
    {
        for(i=0;i<coord_x;i++)
        {
            temp = *(p+j*width+i*width/coord_x);//读取像素点
            color=(0x001f&((temp)>>3))<<11;
            color=color|(((0x003f)&((temp)>>2))<<5);
            color=color|(0x001f&((temp)>>3));
            ips200_wr_data16(color); 
        }
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      总钻风(灰度摄像头)液晶缩放显示函数
//  @param      *p     			图像数组地址
//  @param      width     	    图像宽度
//  @param      height     	    图像高度
//  @param      dis_width       图像显示宽度  0 -（IPS200_X_MAX-1）
//  @param      dis_height      图像显示高度  0 -（IPS200_Y_MAX-1）
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_displayimage032_zoom(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, MT9V03X_CSI_W, MT9V03X_CSI_H)//显示灰度摄像头 图像
//  @note       图像的宽度如果超过液晶的宽度，则自动进行缩放显示。这样可以显示全视野
//-------------------------------------------------------------------------------------------------------------------
void ips200_displayimage032_zoom(uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    uint32 i,j;
                
    uint16 color = 0;
	uint16 temp = 0;

    ips200_address_set(0,0,dis_width-1,dis_height-1);//设置显示区域 
    
    for(j=0;j<dis_height;j++)
    {
        for(i=0;i<dis_width;i++)
        {
            temp = *(p+(j*height/dis_height)*width+i*width/dis_width);//读取像素点
            color=(0x001f&((temp)>>3))<<11;
            color=color|(((0x003f)&((temp)>>2))<<5);
            color=color|(0x001f&((temp)>>3));
            ips200_wr_data16(color); 
        }
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      总钻风(灰度摄像头)液晶缩放显示函数
//  @param      *p     			图像数组地址
//  @param      width     	    图像宽度
//  @param      height     	    图像高度
//  @param      start_x         设置显示起点的x轴坐标
//  @param      start_y     	设置显示起点的y轴坐标
//  @param      dis_width       图像显示宽度  1 -（TFT_X_MAX）
//  @param      dis_height      图像显示高度  1 -（TFT_Y_MAX）
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_displayimage032_zoom1(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, 0, 0, MT9V03X_CSI_W, MT9V03X_CSI_H)//显示灰度摄像头 图像
//-------------------------------------------------------------------------------------------------------------------
void ips200_displayimage032_zoom1(uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height)
{
    uint32 i,j;
                
    uint16 color = 0;
	uint16 temp = 0;

	//检查设置的参数是否超过屏幕的分辨率
	if((start_x+dis_width)>IPS200_X_MAX)	ZF_ASSERT(0);
	if((start_y+dis_height)>IPS200_Y_MAX)	ZF_ASSERT(0);

    ips200_address_set(start_x,start_y,start_x+dis_width-1,start_y+dis_height-1);//设置显示区域 
    
    for(j=0;j<dis_height;j++)
    {
        for(i=0;i<dis_width;i++)
        {
            temp = *(p+(j*height/dis_height)*width+i*width/dis_width);//读取像素点
            color=(0x001f&((temp)>>3))<<11;
            color=color|(((0x003f)&((temp)>>2))<<5);
            color=color|(0x001f&((temp)>>3));
            ips200_wr_data16(color); 
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      凌瞳(彩色摄像头)液晶缩放显示函数
//  @param      *p     			图像数组地址
//  @param      width     	    图像宽度
//  @param      height     	    图像高度
//  @param      dis_width       图像显示宽度  0 -（TFT_X_MAX-1）
//  @param      dis_height      图像显示高度  0 -（TFT_Y_MAX-1）
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_displayimage8660_zoom(scc8660_csi_image[0], SCC8660_CSI_PIC_W, SCC8660_CSI_PIC_H, 320, 240);//显示彩色摄像头 图像
//  @note       此函数仅支持摄像头数据格式(SCC8660_DATA_FORMAT)设置为0时，显示彩色图像
//              图像的宽度如果超过液晶的宽度，则自动进行缩放显示。这样可以显示全视野
//-------------------------------------------------------------------------------------------------------------------
void ips200_displayimage8660_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    uint32 i,j;
    uint16 color = 0;

    ips200_address_set(0,0,dis_width-1,dis_height-1);//设置显示区域 
    
    for(j=0;j<dis_height;j++)
    {
        for(i=0;i<dis_width;i++)
        {
            color = *(p+(j*height/dis_height)*width+i*width/dis_width);//读取像素点
            color = ((color&0xff)<<8) | (color>>8);
            ips200_wr_data16(color); 
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      凌瞳(彩色摄像头)液晶缩放显示函数
//  @param      *p     			图像数组地址
//  @param      width     	    图像宽度
//  @param      height     	    图像高度
//  @param      start_x         设置显示起点的x轴坐标
//  @param      start_y     	设置显示起点的y轴坐标
//  @param      dis_width       图像显示宽度  1 -（TFT_X_MAX）
//  @param      dis_height      图像显示高度  1 -（TFT_Y_MAX）
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_displayimage8660_zoom1(scc8660_csi_image[0], SCC8660_CSI_PIC_W, SCC8660_CSI_PIC_H, 0, 0, 320, 240);
//-------------------------------------------------------------------------------------------------------------------
void ips200_displayimage8660_zoom1(uint16 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height)
{
    uint32 i,j;
                
    uint16 color = 0;

	//检查设置的参数是否超过屏幕的分辨率
	if((start_x+dis_width)>IPS200_X_MAX)	ZF_ASSERT(0);
	if((start_y+dis_height)>IPS200_Y_MAX)	ZF_ASSERT(0);

    ips200_address_set(start_x,start_y,start_x+dis_width-1,start_y+dis_height-1);//设置显示区域 
    
	for(j=0;j<dis_height;j++)
    {
        for(i=0;i<dis_width;i++)
        {
            color = *(p+(j*height/dis_height)*width+i*width/dis_width);//读取像素点
            color = ((color&0xff)<<8) | (color>>8);
            ips200_wr_data16(color); 
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      凌瞳(彩色摄像头)液晶缩放显示函数(显示灰度)
//  @param      *p     			图像数组地址
//  @param      width     	    图像宽度
//  @param      height     	    图像高度
//  @param      dis_width       图像显示宽度  0 -（TFT_X_MAX-1）
//  @param      dis_height      图像显示高度  0 -（TFT_Y_MAX-1）
//  @return     void
//  @since      v1.0
//  Sample usage:               ips200_displayimage8660_grayscale_zoom(scc8660_csi_image[0], SCC8660_CSI_PIC_W, SCC8660_CSI_PIC_H, 320, 240)//显示彩色摄像头图像   显示Y分量
//  @note       此函数仅支持摄像头数据格式(SCC8660_DATA_FORMAT)设置为2时，提取Y分量显示灰度图像
//              图像的宽度如果超过液晶的宽度，则自动进行缩放显示。这样可以显示全视野
//-------------------------------------------------------------------------------------------------------------------
void ips200_displayimage8660_grayscale_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    uint32 i,j;
    uint16 color = 0;
    uint16 temp = 0;
    
    ips200_address_set(0,0,dis_width-1,dis_height-1);//设置显示区域 
    
    for(j=0;j<dis_height;j++)
    {
        for(i=0;i<dis_width;i++)
        {
            temp = *(p+(j*height/dis_height)*width+i*width/dis_width);//读取像素点
            temp = temp&0xff;
            color=(0x001f&((temp)>>3))<<11;
            color=color|(((0x003f)&((temp)>>2))<<5);
            color=color|(0x001f&((temp)>>3));
            ips200_wr_data16(color); 
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      小钻风(二值化摄像头)液晶显示函数
//  @param      *p     			图像数组地址
//  @param      width     	    图像宽度
//  @param      height     	    图像高度
//  @return     void
//  @since      v1.0
//  @note      	图像分辨率需要设置在120(高)*160(宽)以下       
//-------------------------------------------------------------------------------------------------------------------
void ips200_displayimage7725(uint8 *p, uint16 width, uint16 height) 
{
    int i,j; 
	
    uint16 temp = 0;
    ips200_address_set(0,0,width-1,height-1);
	for(i=0;i<height * (width/8);i++)
    {
        temp = *p;
        p++;
        for(j=0; j<8; j++)
        {
            if( (temp<<j)&0x80 )	ips200_wr_data16(RGB565_WHITE);
            else					ips200_wr_data16(RGB565_BLACK);
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      汉字显示
//  @param      x       横坐标 0-（IPS200_X_MAX-1）
//  @param      y       纵坐标 0-（IPS200_Y_MAX-1）
//  @param      size    取模的时候设置的汉字字体大小，也就是一个汉字占用的点阵长宽为多少个点，取模的时候需要长宽是一样的。
//  @param      *p      需要显示的汉字数组
//  @param      number  需要显示多少位
//  @param      color   显示颜色
//  @return     void
//  @since      v1.0
//  Sample usage:		ips200_display_chinese(0,0,16,chinese_test[0],4,RED);//显示font文件里面的 示例
//  @Note       使用PCtoLCD2002软件取模		    阴码、逐行式、顺向   16*16
//-------------------------------------------------------------------------------------------------------------------
void ips200_display_chinese(uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, uint16 color)
{
    int i, j, k; 
    uint8 temp, temp1, temp2;
    const uint8 *p_data;
    
    temp2 = size/8;
    
    ips200_address_set(x,y,number*size-1+x,y+size-1);
    
    for(i=0;i<size;i++)
    {
        temp1 = number;
        p_data = p+i*temp2;
        while(temp1--)
        {
            for(k=0;k<temp2;k++)
            {
                for(j=8;j>0;j--)
                {
                    temp = (*p_data>>(j-1)) & 0x01;
                    if(temp)    ips200_wr_data16(color);
                    else        ips200_wr_data16(IPS200_BGCOLOR);
                }
                p_data++;
            }
            p_data = p_data - temp2 + temp2*size;
        }   
    }
}
