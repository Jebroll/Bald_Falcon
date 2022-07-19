/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2022,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_device_imu963ra
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ3184284598)
* @version          查看doc内version文件 版本说明
* @Software         ADS v1.5.2
* @Target core      TC264
* @Taobao           https://seekfree.taobao.com/
* @date             2022-05-04
* @note             接线定义：
*                   ------------------------------------
*                                                   模块管脚            单片机管脚
*                   // 硬件 SPI 引脚
*                   SCL/SPC             查看 zf_device_imu963ra.h 中 IMU963RA_SPC_PIN 宏定义
*                   SDA/DSI             查看 zf_device_imu963ra.h 中 IMU963RA_SDI_PIN 宏定义
*                   SA0/SDO             查看 zf_device_imu963ra.h 中 IMU963RA_SDO_PIN 宏定义
*                   CS                  查看 zf_device_imu963ra.h 中 IMU963RA_CS_PIN  宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                                                   其余引脚悬空
*
*                   // 软件 IIC 引脚
*                   SCL/SPC             查看 SEEKFREE_IIC.h 中 SEEKFREE_SCL 宏定义
*                   SDA/DSI             查看 SEEKFREE_IIC.h 中 SEEKFREE_SDA 宏定义
*                   电源引脚
*                   VCC                 3.3V电源
*                   GND                 电源地
*                                                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _SEEKFREE_IMU963RA_h
#define _SEEKFREE_IMU963RA_h


#include "common.h"

#define IMU963RA_USE_SOFT_IIC                       (0)                   // 默认使用硬件 SPI 方式驱动

#if IMU963RA_USE_SOFT_IIC                                                 // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 IIC 驱动====================================================
#define IMU963RA_SOFT_IIC_DELAY                     (20)                  // 软件 IIC 的时钟延时周期 数值越小 IIC 通信速率越快
//#define IMU963RA_SCL_PIN                          查看 SEEKFREE_IIC.h 中 SEEKFREE_SCL 宏定义
//#define IMU963RA_SDA_PIN                          查看 SEEKFREE_IIC.h 中 SEEKFREE_SDA 宏定义
//====================================================软件 IIC 驱动====================================================
#else       
//====================================================硬件 SPI 驱动====================================================
#define IMU963RA_SPI_SPEED                          (10*1000*1000)         // 硬件 SPI 速率
#define IMU963RA_SPI                                (SPI_0           )     // 硬件 SPI 号
#define IMU963RA_SPC_PIN                            (SPI0_SCLK_P20_11)     // 硬件 SPI SCK 引脚
#define IMU963RA_SDI_PIN                            (SPI0_MOSI_P20_14)     // 硬件 SPI MOSI 引脚
#define IMU963RA_SDO_PIN                            (SPI0_MISO_P20_12)     // 硬件 SPI MISO 引脚
#define IMU963RA_CS_PIN                             (SPI0_CS2_P20_13 )     // 硬件 CS 片选引脚
//====================================================硬件 SPI 驱动====================================================
#endif
       
//#define IMU963RA_TIMEOUT_COUNT                      0x00FF              // IMU963RA 超时计数
        
//================================================定义 IMU963RA 内部地址================================================
#define IMU963RA_DEV_ADDR                           0x6B                // SA0接地：0x6A SA0上拉：0x6B 模块默认上拉
#define IMU963RA_SPI_W                              0x00
#define IMU963RA_SPI_R                              0x80

#define IMU963RA_FUNC_CFG_ACCESS 			        0x01
#define IMU963RA_PIN_CTRL 					        0x02
#define IMU963RA_S4S_TPH_L 					        0x04
#define IMU963RA_S4S_TPH_H 					        0x05
#define IMU963RA_S4S_RR 					        0x06
#define IMU963RA_FIFO_CTRL1 				        0x07
#define IMU963RA_FIFO_CTRL2 				        0x08
#define IMU963RA_FIFO_CTRL3 				        0x09
#define IMU963RA_FIFO_CTRL4 				        0x0A
#define IMU963RA_COUNTER_BDR_REG1 			        0x0B
#define IMU963RA_COUNTER_BDR_REG2 			        0x0C
#define IMU963RA_INT1_CTRL 					        0x0D
#define IMU963RA_INT2_CTRL 					        0x0E
#define IMU963RA_WHO_AM_I 					        0x0F
#define IMU963RA_CTRL1_XL 					        0x10
#define IMU963RA_CTRL2_G					        0x11
#define IMU963RA_CTRL3_C					        0x12
#define IMU963RA_CTRL4_C					        0x13
#define IMU963RA_CTRL5_C					        0x14
#define IMU963RA_CTRL6_C					        0x15
#define IMU963RA_CTRL7_G					        0x16
#define IMU963RA_CTRL8_XL 					        0x17
#define IMU963RA_CTRL9_XL 					        0x18
#define IMU963RA_CTRL10_C 					        0x19
#define IMU963RA_ALL_INT_SRC 				        0x1A
#define IMU963RA_WAKE_UP_SRC 				        0x1B
#define IMU963RA_TAP_SRC 					        0x1C
#define IMU963RA_D6D_SRC 					        0x1D
#define IMU963RA_STATUS_REG 				        0x1E
#define IMU963RA_OUT_TEMP_L 				        0x20
#define IMU963RA_OUT_TEMP_H 				        0x21
#define IMU963RA_OUTX_L_G 					        0x22
#define IMU963RA_OUTX_H_G 					        0x23
#define IMU963RA_OUTY_L_G 					        0x24
#define IMU963RA_OUTY_H_G 					        0x25
#define IMU963RA_OUTZ_L_G 					        0x26
#define IMU963RA_OUTZ_H_G 					        0x27
#define IMU963RA_OUTX_L_A 					        0x28
#define IMU963RA_OUTX_H_A 					        0x29
#define IMU963RA_OUTY_L_A 					        0x2A
#define IMU963RA_OUTY_H_A 					        0x2B
#define IMU963RA_OUTZ_L_A 					        0x2C
#define IMU963RA_OUTZ_H_A 					        0x2D
#define IMU963RA_EMB_FUNC_STATUS_MAINPAGE 	        0x35
#define IMU963RA_FSM_STATUS_A_MAINPAGE 		        0x36
#define IMU963RA_FSM_STATUS_B_MAINPAGE 		        0x37
#define IMU963RA_STATUS_MASTER_MAINPAGE 	        0x39
#define IMU963RA_FIFO_STATUS1 				        0x3A
#define IMU963RA_FIFO_STATUS2 				        0x3B
#define IMU963RA_TIMESTAMP0 				        0x40
#define IMU963RA_TIMESTAMP1 				        0x41
#define IMU963RA_TIMESTAMP2 				        0x42
#define IMU963RA_TIMESTAMP3 				        0x43
#define IMU963RA_TAP_CFG0 					        0x56
#define IMU963RA_TAP_CFG1 					        0x57
#define IMU963RA_TAP_CFG2 					        0x58
#define IMU963RA_TAP_THS_6D 				        0x59
#define IMU963RA_INT_DUR2 					        0x5A
#define IMU963RA_WAKE_UP_THS 				        0x5B
#define IMU963RA_WAKE_UP_DUR 				        0x5C
#define IMU963RA_FREE_FALL   				        0x5D
#define IMU963RA_MD1_CFG     				        0x5E
#define IMU963RA_MD2_CFG     				        0x5F
#define IMU963RA_S4S_ST_CMD_CODE 			        0x60
#define IMU963RA_S4S_DT_REG 				        0x61
#define IMU963RA_I3C_BUS_AVB 				        0x62
#define IMU963RA_INTERNAL_FREQ_FINE 		        0x63
#define IMU963RA_INT_OIS   					        0x6F
#define IMU963RA_CTRL1_OIS 					        0x70
#define IMU963RA_CTRL2_OIS 					        0x71
#define IMU963RA_CTRL3_OIS 					        0x72
#define IMU963RA_X_OFS_USR 					        0x73
#define IMU963RA_Y_OFS_USR 					        0x74
#define IMU963RA_Z_OFS_USR 					        0x75
#define IMU963RA_FIFO_DATA_OUT_TAG 			        0x78
#define IMU963RA_FIFO_DATA_OUT_X_L 			        0x79
#define IMU963RA_FIFO_DATA_OUT_X_H 			        0x7A
#define IMU963RA_FIFO_DATA_OUT_Y_L 			        0x7B
#define IMU963RA_FIFO_DATA_OUT_Y_H 			        0x7C
#define IMU963RA_FIFO_DATA_OUT_Z_L 			        0x7D
#define IMU963RA_FIFO_DATA_OUT_Z_H 			        0x7E

//集线器功能相关寄存器 需要将FUNC_CFG_ACCESS的SHUB_REG_ACCESS位设置为1才能正确访问
#define IMU963RA_SENSOR_HUB_1 				        0x02 
#define IMU963RA_SENSOR_HUB_2 				        0x03 
#define IMU963RA_SENSOR_HUB_3 				        0x04 
#define IMU963RA_SENSOR_HUB_4 				        0x05 
#define IMU963RA_SENSOR_HUB_5 				        0x06 
#define IMU963RA_SENSOR_HUB_6 				        0x07 
#define IMU963RA_SENSOR_HUB_7 				        0x08 
#define IMU963RA_SENSOR_HUB_8 				        0x09 
#define IMU963RA_SENSOR_HUB_9 				        0x0A 
#define IMU963RA_SENSOR_HUB_10 				        0x0B 
#define IMU963RA_SENSOR_HUB_11 				        0x0C 
#define IMU963RA_SENSOR_HUB_12 				        0x0D 
#define IMU963RA_SENSOR_HUB_13 				        0x0E 
#define IMU963RA_SENSOR_HUB_14 				        0x0F 
#define IMU963RA_SENSOR_HUB_15 				        0x10 
#define IMU963RA_SENSOR_HUB_16 				        0x11 
#define IMU963RA_SENSOR_HUB_17 				        0x12 
#define IMU963RA_SENSOR_HUB_18 				        0x13 
#define IMU963RA_MASTER_CONFIG 				        0x14 
#define IMU963RA_SLV0_ADD 					        0x15 
#define IMU963RA_SLV0_SUBADD 				        0x16 
#define IMU963RA_SLV0_CONFIG 				        0x17 
#define IMU963RA_SLV1_ADD 					        0x18 
#define IMU963RA_SLV1_SUBADD 				        0x19 
#define IMU963RA_SLV1_CONFIG 				        0x1A 
#define IMU963RA_SLV2_ADD 					        0x1B 
#define IMU963RA_SLV2_SUBADD 				        0x1C 
#define IMU963RA_SLV2_CONFIG 				        0x1D 
#define IMU963RA_SLV3_ADD 					        0x1E 
#define IMU963RA_SLV3_SUBADD 				        0x1F 
#define IMU963RA_SLV3_CONFIG 				        0x20 
#define IMU963RA_DATAWRITE_SLV0 			        0x21 
#define IMU963RA_STATUS_MASTER 				        0x22

#define IMU963RA_MAG_ADDR 			                0x0D            //7位IIC地址
#define IMU963RA_MAG_OUTX_L 			            0x00
#define IMU963RA_MAG_CONTROL1 			            0x09
#define IMU963RA_MAG_CONTROL2 			            0x0A
#define IMU963RA_MAG_FBR 			                0x0B
#define IMU963RA_MAG_CHIP_ID 			            0x0D


extern int16 imu963ra_acc_x,  imu963ra_acc_y,  imu963ra_acc_z;
extern int16 imu963ra_gyro_x, imu963ra_gyro_y, imu963ra_gyro_z;
extern int16 imu963ra_mag_x,  imu963ra_mag_y,  imu963ra_mag_z;

void imu963ra_get_acc (void);
void imu963ra_get_gyro (void);
void imu963ra_get_mag (void);

uint8 imu963ra_init (void);




#endif
