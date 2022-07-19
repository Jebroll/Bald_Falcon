/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2021,逐飞科技
* All rights reserved.
* 技术讨论QQ群：一群：179029047(已满)  二群：244861897
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file				SEEKFREE_GPS_TAU1201.c
* @company			成都逐飞科技有限公司
* @author			逐飞科技(QQ3184284598)
* @version			查看doc内version文件 版本说明
* @Software			IAR 8.32.4 or MDK 5.28
* @Taobao			https://seekfree.taobao.com/
* @date				2021-12-30
* @note
* 					接线定义：
* 					------------------------------------
* 					模块管脚			单片机管脚
* 					RX					查看 GPS_TAU1201_RX宏定义的引脚
* 					TX                  查看 GPS_TAU1201_TX宏定义的引脚
* 					GND					电源地
* 					VCC				    5V电源
* 					------------------------------------
********************************************************************************************************************/
#ifndef _SEEKFREE_GPS_TAU1201_h
#define _SEEKFREE_GPS_TAU1201_h

#include "common.h"


//--------------------------------------------------------------------------------------------------
//引脚配置
//--------------------------------------------------------------------------------------------------
#define GPS_TAU1201_UART    UART_3
#define GPS_TAU1201_RX      UART3_TX_P15_6    // GPS RX引脚连接到单片机此
#define GPS_TAU1201_TX      UART3_RX_P15_7    // GPS TX串口引脚



#define ANGLE_TO_RAD(X)    (X * PI / 180.0)//角度转换为弧度
#define RAD_TO_ANGLE(X)    (X * 180.0 / PI)//弧度转换为角度
#define PI                  3.1415926535898



typedef struct{
	uint16 year;  
	uint8  month; 
	uint8  day;
	uint8  hour;
	uint8  minute;
	uint8  second;
}gps_time_struct;

typedef struct{
    gps_time_struct    time;        //时间
    
    uint8       state;              //有效状态  1：定位有效  0：定位无效
    
    uint16      latitude_degree;	//度
	uint16      latitude_cent;		//分
	uint16      latitude_second;    //秒
	uint16      longitude_degree;	//度
	uint16      longitude_cent;		//分
	uint16      longitude_second;   //秒
    
    double      latitude;           //经度
    double      longitude;          //纬度
    
    int8 	    ns;                 //纬度半球 N（北半球）或 S（南半球）
    int8 	    ew;                 //经度半球 E（东经）或 W（西经）
    
	float 	    speed;              //速度（公里/每小时）
    float 	    direction;          //地面航向（000.0~359.9 度，以真北方为参考基准）
    
    //下面两个个信息从GNGGA语句中获取
    uint8       satellite_used;     //用于定位的卫星数量
	float 	    height;             //高度   
}gps_info_struct;



extern gps_info_struct gps_tau1201;
extern uint8 gps_tau1201_flag;



double  get_two_points_distance(double lat1, double lng1, double lat2, double lng2);
double  get_two_points_azimuth(double lat1, double lon1, double lat2, double lon2);
void    gps_uart_callback(void);
void    gps_init(void);













#endif  
