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
* 					RX					查看 GPS_TAU1201_TX宏定义的引脚
* 					TX                  查看 GPS_TAU1201_TX宏定义的引脚
* 					GND					电源地
* 					VCC					5V电源
* 					------------------------------------
********************************************************************************************************************/

#include "zf_stm_systick.h"
#include "zf_uart.h"
#include "math.h"
#include "SEEKFREE_GPS_TAU1201.h"
#include <string.h>



gps_info_struct gps_tau1201;
uint8 gps_tau1201_buffer[100];
uint8 gps_tau1201_num;      //当前接收字符数量
uint8 gps_tau1201_flag;     //1：采集完成 0：没有采集完成


//-------------------------------------------------------------------------------------------------------------------
// @brief		获取指定,后面的索引
// @param		num             第几个逗号
// @param		*str            字符串           
// @return		uint8           返回索引       
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
uint8 get_parameter_index(uint8 num, char *str)
{
	uint8 i, j = 0;
    int8* temp;
    uint8 len = 0, len1;
    
    temp = strchr(str, '\n');
    if(NULL != temp)
    {
        len = (uint8)((uint32)temp - (uint32)str + 1);
    }

	for(i = 0;i < len;i ++)
	{
		if(str[i] == ',')
        {
            j++;
        }
		if(j == num)
        {
            len1 =  i + 1;	
            break;
        }
	}

	return len1;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		给定字符串转换为int
// @param		*s              字符串
// @return		double          返回数值           
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
int str_to_int(char *buf)
{
	int return_value = 0;
	int dat;
	char *str = buf;
	while(*str != '\0')
	{
        dat = *str - '0';
        return_value = return_value * 10 + dat;
		str ++;
	}
	return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		给定字符串第一个,之前的数据转换为int
// @param		*s              字符串
// @return		float           返回数值           
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
int get_int_number(char *s)
{
	char buf[10];
	uint8 i;
	int return_value;
	i = get_parameter_index(1, s);
	i = i - 1;
	strncpy(buf, s, i);
	buf[i] = 0;
	return_value = str_to_int(buf);
	return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		给定字符串转换为double	
// @param		*s              字符串
// @return		double          返回数值           
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
double str_to_double(char *buf)
{
	double return_value = 0;
	double dat;
	int integer = 1;
	char *str = buf;
    int8 negative_flag = 1;
	int i;
    if('-' == *str)
    {
        negative_flag = -1;
        str++;
    }
        
	while(*str != '\0')
	{
        dat = *str - '0';
        if('.' == *str)
        {
            integer = 0;
			i = 1;
        }
        else
        {
            if( integer == 1 )
            {
                return_value = return_value * 10 + dat;
            }
            else
            {
                return_value = return_value + dat / (10 * i);
                i = i * 10 ;
            }
        }
		str ++;
	}
	return return_value*negative_flag;
}
												
//-------------------------------------------------------------------------------------------------------------------
// @brief		给定字符串第一个,之前的数据转换为float
// @param		*s              字符串
// @return		float           返回数值           
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
float get_float_number(char *s)
{
    uint8 i;
	char buf[10];
	float return_value;
    
	i=get_parameter_index(1, s);
	i = i - 1;
	strncpy(buf, s, i);
	buf[i] = 0;
	return_value = (float)str_to_double(buf);
	return return_value;	
}


												
//-------------------------------------------------------------------------------------------------------------------
// @brief		给定字符串第一个,之前的数据转换为double	
// @param		*s              字符串
// @return		double          返回数值           
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
double get_double_number(char *s)
{
    uint8 i;
	char buf[10];
	double return_value;
    
	i = get_parameter_index(1, s);
	i = i - 1;
	strncpy(buf, s, i);
	buf[i] = 0;
	return_value = str_to_double(buf);
	return return_value;
}



//-------------------------------------------------------------------------------------------------------------------
// @brief		世界时间转换为北京时间	
// @param		*time           保存的时间
// @return		void           
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void utc_to_btc(gps_time_struct *time)
{
    uint8 day_num;
    
    time->hour = time->hour + 8;
	if(time->hour > 23)
	{
		time->hour -= 24;
		time->day += 1;

        if(2 == time->month)
        {
            day_num = 28;
            if((time->year%4 == 0 && time->year%100 != 0) || time->year%400 == 0)//判断是否为闰年 
            {
                day_num ++;//闰月 2月为29天
            }
        }
        else
        {
            day_num = 31;//1 3 5 7 8 10 12这些月份为31天
            if(4  == time->month || 6  == time->month || 9  == time->month || 11 == time->month )
            {
                day_num = 30;
            }
        }
        
        if(time->day > day_num)
        {
            time->day = 1;
            time->month++;
            if(time->month > 12)
            {
                time->month -= 12;
                time->year ++;
            }
        }
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		RMC语句解析
// @param		*line	        接收到的语句信息		
// @param		*gps            保存解析后的数据
// @return		uint8           1：解析成功 0：数据有问题不能解析
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
uint8 gps_gnrmc_parse(char *line, gps_info_struct *gps)
{
	uint8 state, temp;
    
    double  latitude; //经度
    double  longitude;//纬度
    
	float lati_cent_tmp, lati_second_tmp;
	float long_cent_tmp, long_second_tmp;
	float speed_tmp;
	char *buf = line;
    uint8 return_value = 0;

	state = buf[get_parameter_index(2, buf)];

    gps->state = 0;
    if (state == 'A')  //如果数据有效，则解析数据
    {
        return_value = 1;
        gps->state = 1;
        gps -> ns       = buf[get_parameter_index(4, buf)];
        gps -> ew       = buf[get_parameter_index(6, buf)];

        latitude   = get_double_number(&buf[get_parameter_index(3, buf)]);
        longitude  = get_double_number(&buf[get_parameter_index( 5, buf)]);

        gps->latitude_degree  = (int)latitude / 100;   //纬度转换为度分秒
        lati_cent_tmp         = (latitude - gps->latitude_degree * 100);
        gps->latitude_cent    = (int)lati_cent_tmp;
        lati_second_tmp       = (lati_cent_tmp - gps->latitude_cent) * 10000;
        gps->latitude_second  = (int)lati_second_tmp;

        gps->longitude_degree = (int)longitude / 100;	//经度转换为度分秒
        long_cent_tmp         = (longitude - gps->longitude_degree * 100);
        gps->longitude_cent   = (int)long_cent_tmp;
        long_second_tmp       = (long_cent_tmp - gps->longitude_cent) * 10000;
        gps->longitude_second = (int)long_second_tmp;
        
        gps->latitude = gps->latitude_degree + (double)gps->latitude_cent/60 + (double)gps->latitude_second/600000;
        gps->longitude = gps->longitude_degree + (double)gps->longitude_cent/60 + (double)gps->longitude_second/600000;

        speed_tmp      = get_float_number(&buf[get_parameter_index(7, buf)]);   //速度(海里/小时)
        gps->speed     = speed_tmp * 1.85f;                                     //转换为公里/小时
        gps->direction = get_float_number(&buf[get_parameter_index(8, buf)]);   //角度			
    }
    //在定位没有生效前也是有时间数据的，可以直接解析
    gps->time.hour    = (buf[7] - '0') * 10 + (buf[8] - '0');		        //时间
    gps->time.minute  = (buf[9] - '0') * 10 + (buf[10] - '0');
    gps->time.second  = (buf[11] - '0') * 10 + (buf[12] - '0');
    temp = get_parameter_index(9, buf);
    gps->time.day     = (buf[temp + 0] - '0') * 10 + (buf[temp + 1] - '0');   //日期
    gps->time.month   = (buf[temp + 2] - '0') * 10 + (buf[temp + 3] - '0');
    gps->time.year    = (buf[temp + 4] - '0') * 10 + (buf[temp + 5] - '0')+2000;

    utc_to_btc(&gps->time);
	
	
	return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		GGA语句解析
// @param		*line	        接收到的语句信息		
// @param		*gps            保存解析后的数据
// @return		uint8           1：解析成功 0：数据有问题不能解析
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
uint8 gps_gngga_parse(char *line, gps_info_struct *gps)
{
	uint8 state;
	char *buf = line;
    uint8 return_value = 0;

	state = buf[get_parameter_index(2, buf)];

    if (state != ',')
    {
        gps->satellite_used = (uint8)get_int_number(&buf[get_parameter_index(7, buf)]);
        gps->height         = get_float_number(&buf[get_parameter_index(9, buf)]) + get_float_number(&buf[get_parameter_index(11, buf)]);  //高度 = 海拔高度 + 地球椭球面相对大地水准面的高度 
        return_value = 1;
    }
	
	return return_value;
}


//-------------------------------------------------------------------------------------------------------------------
// @brief		计算从第一个点到第二个点的距离
// @param		latitude1		第一个点的纬度
// @param		longitude1		第一个点的经度
// @param		latitude2		第二个点的纬度
// @param		longitude2		第二个点的经度
// @return		double          返回两点距离
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
double get_two_points_distance(double latitude1, double longitude1, double latitude2, double longitude2)
{  
    const double EARTH_RADIUS = 6378137;//地球半径(单位：m)
    double rad_latitude1;
    double rad_latitude2;
    double rad_longitude1;
    double rad_longitude2;
    double distance;
    double a;
    double b;
    
    rad_latitude1 = ANGLE_TO_RAD(latitude1);//根据角度计算弧度
    rad_latitude2 = ANGLE_TO_RAD(latitude2);
    rad_longitude1 = ANGLE_TO_RAD(longitude1);
    rad_longitude2 = ANGLE_TO_RAD(longitude2);

    a = rad_latitude1 - rad_latitude2;
    b = rad_longitude1 - rad_longitude2;

    distance = 2 * asin(sqrt(pow(sin(a/2),2) + cos(rad_latitude1)*cos(rad_latitude2)*pow(sin(b/2),2)));//google maps里面实现的算法
    distance = distance * EARTH_RADIUS;  

    return distance;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		计算从第一个点到第二个点的方位角
// @param		latitude1		第一个点的纬度
// @param		longitude1		第一个点的经度
// @param		latitude2		第二个点的纬度
// @param		longitude2		第二个点的经度
// @return		double          返回方位角（0至360）
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
double get_two_points_azimuth(double latitude1, double longitude1, double latitude2, double longitude2)
{
    latitude1 = ANGLE_TO_RAD(latitude1);
    latitude2 = ANGLE_TO_RAD(latitude2);
    longitude1 = ANGLE_TO_RAD(longitude1);
    longitude2 = ANGLE_TO_RAD(longitude2);

    double x = sin(longitude2 - longitude1) * cos(latitude2);
    double y = cos(latitude1) * sin(latitude2) - sin(latitude1) * cos(latitude2) * cos(longitude2 - longitude1);
    double angle = RAD_TO_ANGLE(atan2(x,y));
    return angle>0?angle:angle+360;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		解析GPS数据
// @param		void			
// @return		void          
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void gps_data_parse(void)
{
    if(0 == strncmp((char *)&gps_tau1201_buffer[3], "RMC", 3))
    {
        gps_gnrmc_parse((char *)gps_tau1201_buffer, &gps_tau1201);
    }
    
    else if(0 == strncmp((char *)&gps_tau1201_buffer[3], "GGA", 3))
    {
        gps_gngga_parse((char *)gps_tau1201_buffer, &gps_tau1201);
    }
}


//-------------------------------------------------------------------------------------------------------------------
// @brief		GPS串口回调函数
// @param		void			
// @return		void          
// @since		v1.0
// Sample usage:				此函数需要在串口接收中断内进行调用
//-------------------------------------------------------------------------------------------------------------------
void gps_uart_callback(void)
{
    uint8 dat;
    
    uart_query(GPS_TAU1201_UART, &dat);
    if('$' == dat || ('$' != gps_tau1201_buffer[0]))//帧头校验
    {
        gps_tau1201_num = 0;
    }
    gps_tau1201_buffer[gps_tau1201_num++] = dat;
    
    if('\n' == dat)
    {
        //收到一个语句
        gps_tau1201_buffer[gps_tau1201_num] = 0; //在末尾添加\0
        gps_data_parse();           //开始解析数据
        gps_tau1201_flag = 1;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		GPS初始化
// @param		void			
// @return		void          
// @since		v1.0
// Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void gps_init(void)
{
    const uint8 set_rate[]      = {0xF1, 0xD9, 0x06, 0x42, 0x14, 0x00, 0x00, 0x0A, 0x05, 0x00, 0x64, 0x00, 0x00, 0x00, 0x60, 0xEA, 0x00, 0x00, 0xD0, 0x07, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 0xB8, 0xED};
    const uint8 open_gga[]      = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x00, 0x01, 0xFB, 0x10};
    const uint8 open_rmc[]      = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x05, 0x01, 0x00, 0x1A};
    
    const uint8 close_gll[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x01, 0x00, 0xFB, 0x11};
    const uint8 close_gsa[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x02, 0x00, 0xFC, 0x13};
    const uint8 close_grs[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x03, 0x00, 0xFD, 0x15};
    const uint8 close_gsv[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x04, 0x00, 0xFE, 0x17};
    const uint8 close_vtg[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x06, 0x00, 0x00, 0x1B};
    const uint8 close_zda[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x07, 0x00, 0x01, 0x1D};
    const uint8 close_gst[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x08, 0x00, 0x02, 0x1F};
    const uint8 close_txt[]     = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x40, 0x00, 0x3A, 0x8F};
    const uint8 close_txt_ant[] = {0xF1, 0xD9, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x20, 0x00, 0x1A, 0x4F};

    gps_type = GPS_TAU1201;

    enableInterrupts();
    systick_delay_ms(STM0, 500);//等待GPS启动后开始初始化
    uart_init(GPS_TAU1201_UART, 115200, GPS_TAU1201_RX, GPS_TAU1201_TX);

    uart_putbuff(GPS_TAU1201_UART, (uint8 *)set_rate, sizeof(set_rate));//设置GPS更新速率为10hz，如果不调用此语句则默认为1hz
    systick_delay_ms(STM0, 200);

    uart_putbuff(GPS_TAU1201_UART, (uint8 *)open_rmc, sizeof(open_rmc));//开启rmc语句
    systick_delay_ms(STM0, 50);
    uart_putbuff(GPS_TAU1201_UART, (uint8 *)open_gga, sizeof(open_gga));//开启gga语句
    systick_delay_ms(STM0, 50);
    uart_putbuff(GPS_TAU1201_UART, (uint8 *)close_gll, sizeof(close_gll));
    systick_delay_ms(STM0, 50);
    uart_putbuff(GPS_TAU1201_UART, (uint8 *)close_gsa, sizeof(close_gsa));
    systick_delay_ms(STM0, 50);
    uart_putbuff(GPS_TAU1201_UART, (uint8 *)close_grs, sizeof(close_grs));
    systick_delay_ms(STM0, 50);
    uart_putbuff(GPS_TAU1201_UART, (uint8 *)close_gsv, sizeof(close_gsv));
    systick_delay_ms(STM0, 50);
    uart_putbuff(GPS_TAU1201_UART, (uint8 *)close_vtg, sizeof(close_vtg));
    systick_delay_ms(STM0, 50);
    uart_putbuff(GPS_TAU1201_UART, (uint8 *)close_zda, sizeof(close_zda));
    systick_delay_ms(STM0, 50);
    uart_putbuff(GPS_TAU1201_UART, (uint8 *)close_gst, sizeof(close_gst));
    systick_delay_ms(STM0, 50);
    uart_putbuff(GPS_TAU1201_UART, (uint8 *)close_txt, sizeof(close_txt));
    systick_delay_ms(STM0, 50);
    uart_putbuff(GPS_TAU1201_UART, (uint8 *)close_txt_ant, sizeof(close_txt_ant));
    systick_delay_ms(STM0, 50);
    disableInterrupts();
}
